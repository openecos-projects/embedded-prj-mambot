#include "ssd1306.h"
#include "font5x7.h"
#include "emo_data.h"
#include "i2c.h"
#include "timer.h"
#include <string.h>
#include <stdio.h>  // 调试用

// 显示缓冲区 (128 x 64 / 8 = 1024 bytes)
static uint8_t ssd1306_buffer[128 * 64 / 8];

// 设备配置指针
static ssd1306_config_t ssd1306_cfg;

// 发送单个命令
static void ssd1306_write_cmd(uint8_t cmd) {
    i2c_write_nbyte(ssd1306_cfg.i2c_addr, SSD1306_CTRL_CMD, I2C_REG_8, &cmd, 1);
}

// 发送数据块
static void ssd1306_write_data(uint8_t* data, uint16_t len) {
    // I2C传输可能有长度限制，分批发送
    const uint16_t chunk_size = 16;
    for (uint16_t i = 0; i < len; i += chunk_size) {
        uint16_t send_len = (len - i > chunk_size) ? chunk_size : (len - i);
        i2c_write_nbyte(ssd1306_cfg.i2c_addr, SSD1306_CTRL_DATA, I2C_REG_8, &data[i], send_len);
    }
}

void ssd1306_init(ssd1306_config_t* config) {
    // 保存配置
    ssd1306_cfg.i2c_addr = config->i2c_addr;
    ssd1306_cfg.width = config->width;
    ssd1306_cfg.height = config->height;

    // 初始化I2C
    i2c_config_t i2c_cfg = {.pscr = 0x0F};
    i2c_init(&i2c_cfg);

    // 等待电源稳定
    delay_ms(100);

    // SSD1306初始化序列
    ssd1306_write_cmd(SSD1306_CMD_DISPLAY_OFF);          // 关闭显示

    ssd1306_write_cmd(SSD1306_CMD_SET_DISP_CLK_DIV);     // 设置显示时钟分频
    ssd1306_write_cmd(0x80);                              // 默认分频值

    ssd1306_write_cmd(SSD1306_CMD_SET_MUX_RATIO);        // 设置多路复用率
    ssd1306_write_cmd(ssd1306_cfg.height - 1);            // 根据屏幕高度设置

    ssd1306_write_cmd(SSD1306_CMD_SET_DISP_OFFSET);      // 设置显示偏移
    ssd1306_write_cmd(0x00);                              // 无偏移

    ssd1306_write_cmd(SSD1306_CMD_SET_START_LINE | 0x00); // 设置显示起始行

    ssd1306_write_cmd(SSD1306_CMD_CHARGE_PUMP);          // 电荷泵设置
    ssd1306_write_cmd(0x14);                              // 启用内部DC-DC

    ssd1306_write_cmd(SSD1306_CMD_MEM_ADDR_MODE);        // 设置内存地址模式
    ssd1306_write_cmd(0x00);                              // 水平寻址模式

    ssd1306_write_cmd(SSD1306_CMD_SEG_REMAP | 0x01);     // 段重映射 (左右翻转)

    ssd1306_write_cmd(SSD1306_CMD_COM_SCAN_DIR | 0x08);  // COM扫描方向 (上下翻转)

    ssd1306_write_cmd(SSD1306_CMD_SET_COM_PINS);         // COM引脚配置
    if (ssd1306_cfg.height == 64) {
        ssd1306_write_cmd(0x12);                          // 128x64
    } else if (ssd1306_cfg.height == 32) {
        ssd1306_write_cmd(0x02);                          // 128x32
    } else {
        ssd1306_write_cmd(0x12);                          // 默认
    }

    ssd1306_write_cmd(SSD1306_CMD_SET_CONTRAST);         // 设置对比度
    ssd1306_write_cmd(0xCF);                              // 默认对比度

    ssd1306_write_cmd(SSD1306_CMD_SET_PRECHARGE);        // 设置预充电周期
    ssd1306_write_cmd(0xF1);

    ssd1306_write_cmd(SSD1306_CMD_SET_VCOM_DESEL);       // 设置VCOMH电压
    ssd1306_write_cmd(0x40);

    ssd1306_write_cmd(SSD1306_CMD_ENTIRE_DISP_ON);       // 关闭全屏点亮
    ssd1306_write_cmd(SSD1306_CMD_SET_NORMAL_DISP);      // 正常显示模式

    ssd1306_write_cmd(SSD1306_CMD_DISPLAY_ON);           // 开启显示

    // 清空缓冲区并刷新
    ssd1306_clear();
    ssd1306_display();
}

void ssd1306_clear(void) {
    memset(ssd1306_buffer, 0, sizeof(ssd1306_buffer));
}

void ssd1306_fill(ssd1306_color_t color) {
    memset(ssd1306_buffer, color ? 0xFF : 0x00, sizeof(ssd1306_buffer));
}

void ssd1306_display(void) {
    // 设置列地址范围
    ssd1306_write_cmd(SSD1306_CMD_SET_COL_ADDR);
    ssd1306_write_cmd(0);                                 // 起始列
    ssd1306_write_cmd(ssd1306_cfg.width - 1);             // 结束列

    // 设置页地址范围
    ssd1306_write_cmd(SSD1306_CMD_SET_PAGE_ADDR);
    ssd1306_write_cmd(0);                                 // 起始页
    ssd1306_write_cmd((ssd1306_cfg.height / 8) - 1);      // 结束页

    // 发送显示数据
    uint16_t buf_size = ssd1306_cfg.width * ssd1306_cfg.height / 8;
    ssd1306_write_data(ssd1306_buffer, buf_size);
}

void ssd1306_set_contrast(uint8_t contrast) {
    ssd1306_write_cmd(SSD1306_CMD_SET_CONTRAST);
    ssd1306_write_cmd(contrast);
}

void ssd1306_invert(uint8_t invert) {
    if (invert) {
        ssd1306_write_cmd(SSD1306_CMD_SET_INVERSE_DISP);
    } else {
        ssd1306_write_cmd(SSD1306_CMD_SET_NORMAL_DISP);
    }
}

void ssd1306_display_on(uint8_t on) {
    if (on) {
        ssd1306_write_cmd(SSD1306_CMD_DISPLAY_ON);
    } else {
        ssd1306_write_cmd(SSD1306_CMD_DISPLAY_OFF);
    }
}

void ssd1306_set_pixel(uint8_t x, uint8_t y, ssd1306_color_t color) {
    if (x >= ssd1306_cfg.width || y >= ssd1306_cfg.height) {
        return;
    }

    // 计算缓冲区位置
    // 每8行为一页，一个字节存储垂直方向8个像素
    uint16_t idx = x + (y / 8) * ssd1306_cfg.width;
    uint8_t bit = y & 7;

    if (color == SSD1306_COLOR_WHITE) {
        ssd1306_buffer[idx] |= (1 << bit);
    } else {
        ssd1306_buffer[idx] &= ~(1 << bit);
    }
}

ssd1306_color_t ssd1306_get_pixel(uint8_t x, uint8_t y) {
    if (x >= ssd1306_cfg.width || y >= ssd1306_cfg.height) {
        return SSD1306_COLOR_BLACK;
    }

    uint16_t idx = x + (y / 8) * ssd1306_cfg.width;
    uint8_t bit = y & 7;

    return (ssd1306_buffer[idx] & (1 << bit)) ? SSD1306_COLOR_WHITE : SSD1306_COLOR_BLACK;
}

void ssd1306_draw_hline(uint8_t x, uint8_t y, uint8_t w) {
    for (uint8_t i = 0; i < w; i++) {
        ssd1306_set_pixel(x + i, y, SSD1306_COLOR_WHITE);
    }
}

void ssd1306_draw_vline(uint8_t x, uint8_t y, uint8_t h) {
    for (uint8_t i = 0; i < h; i++) {
        ssd1306_set_pixel(x, y + i, SSD1306_COLOR_WHITE);
    }
}

void ssd1306_draw_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
    // Bresenham直线算法
    int16_t dx = (x1 > x0) ? (x1 - x0) : (x0 - x1);
    int16_t dy = (y1 > y0) ? (y1 - y0) : (y0 - y1);
    int16_t sx = (x0 < x1) ? 1 : -1;
    int16_t sy = (y0 < y1) ? 1 : -1;
    int16_t err = dx - dy;
    int16_t e2;

    while (1) {
        ssd1306_set_pixel(x0, y0, SSD1306_COLOR_WHITE);

        if (x0 == x1 && y0 == y1) {
            break;
        }

        e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void ssd1306_draw_rect(uint8_t x, uint8_t y, uint8_t w, uint8_t h) {
    ssd1306_draw_hline(x, y, w);              // 上边
    ssd1306_draw_hline(x, y + h - 1, w);      // 下边
    ssd1306_draw_vline(x, y, h);              // 左边
    ssd1306_draw_vline(x + w - 1, y, h);      // 右边
}

void ssd1306_fill_rect(uint8_t x, uint8_t y, uint8_t w, uint8_t h) {
    for (uint8_t i = 0; i < w; i++) {
        for (uint8_t j = 0; j < h; j++) {
            ssd1306_set_pixel(x + i, y + j, SSD1306_COLOR_WHITE);
        }
    }
}

void ssd1306_draw_char(uint8_t x, uint8_t y, char c) {
    // 检查字符是否在有效范围内
    if (c < FONT5X7_FIRST_CHAR || c > FONT5X7_LAST_CHAR) {
        return;
    }

    // 计算字符在字库中的索引
    uint16_t idx = (c - FONT5X7_FIRST_CHAR) * FONT5X7_WIDTH;

    // 绘制字符 (5列 x 7行)
    for (uint8_t col = 0; col < FONT5X7_WIDTH; col++) {
        uint8_t line = font5x7[idx + col];
        for (uint8_t row = 0; row < FONT5X7_HEIGHT; row++) {
            if (line & (1 << row)) {
                ssd1306_set_pixel(x + col, y + row, SSD1306_COLOR_WHITE);
            }
        }
    }
}

void ssd1306_draw_string(uint8_t x, uint8_t y, const char* str) {
    uint8_t cur_x = x;

    while (*str) {
        // 检查是否超出屏幕宽度
        if (cur_x + FONT5X7_WIDTH > ssd1306_cfg.width) {
            break;
        }

        ssd1306_draw_char(cur_x, y, *str);
        cur_x += FONT5X7_WIDTH + 1;  // 字符宽度 + 1像素间距
        str++;
    }
}

void ssd1306_draw_circle(uint8_t x0, uint8_t y0, uint8_t r) {
    int16_t x = r;
    int16_t y = 0;
    int16_t err = 1 - r;

    while (x >= y) {
        // 利用圆的8对称性，每次画8个点
        ssd1306_set_pixel(x0 + x, y0 + y, SSD1306_COLOR_WHITE);
        ssd1306_set_pixel(x0 - x, y0 + y, SSD1306_COLOR_WHITE);
        ssd1306_set_pixel(x0 + x, y0 - y, SSD1306_COLOR_WHITE);
        ssd1306_set_pixel(x0 - x, y0 - y, SSD1306_COLOR_WHITE);
        ssd1306_set_pixel(x0 + y, y0 + x, SSD1306_COLOR_WHITE);
        ssd1306_set_pixel(x0 - y, y0 + x, SSD1306_COLOR_WHITE);
        ssd1306_set_pixel(x0 + y, y0 - x, SSD1306_COLOR_WHITE);
        ssd1306_set_pixel(x0 - y, y0 - x, SSD1306_COLOR_WHITE);

        y++;
        if (err < 0) {
            err += 2 * y + 1;
        } else {
            x--;
            err += 2 * (y - x) + 1;
        }
    }
}

void ssd1306_fill_circle(uint8_t x0, uint8_t y0, uint8_t r) {
    int16_t x = r;
    int16_t y = 0;
    int16_t err = 1 - r;

    while (x >= y) {
        // 用水平线填充圆
        ssd1306_draw_hline(x0 - x, y0 + y, 2 * x + 1);
        ssd1306_draw_hline(x0 - x, y0 - y, 2 * x + 1);
        ssd1306_draw_hline(x0 - y, y0 + x, 2 * y + 1);
        ssd1306_draw_hline(x0 - y, y0 - x, 2 * y + 1);

        y++;
        if (err < 0) {
            err += 2 * y + 1;
        } else {
            x--;
            err += 2 * (y - x) + 1;
        }
    }
}

// ============================================================================
// 位图绘制实现
// ============================================================================

void ssd1306_draw_xbm(uint8_t x, uint8_t y, uint8_t w, uint8_t h,
                      const uint8_t* data, ssd1306_draw_mode_t mode) {
    if (data == NULL) return;

    uint8_t bytes_per_row = (w + 7) / 8;

    for (uint8_t row = 0; row < h; row++) {
        for (uint8_t col = 0; col < w; col++) {
            uint16_t byte_idx = (uint16_t)row * bytes_per_row + (col / 8);

            uint8_t bit_idx = col % 8;
            uint8_t pixel = (data[byte_idx] >> bit_idx) & 0x01;

            uint8_t sx = x + col;
            uint8_t sy = y + row;

            switch (mode) {
                case SSD1306_DRAW_NORMAL:
                    ssd1306_set_pixel(sx, sy, pixel ? SSD1306_COLOR_WHITE : SSD1306_COLOR_BLACK);
                    break;
                case SSD1306_DRAW_TRANSPARENT:
                    if (pixel) ssd1306_set_pixel(sx, sy, SSD1306_COLOR_WHITE);
                    break;
                case SSD1306_DRAW_INVERT:
                    ssd1306_set_pixel(sx, sy, pixel ? SSD1306_COLOR_BLACK : SSD1306_COLOR_WHITE);
                    break;
                case SSD1306_DRAW_XOR:
                    if (pixel) {
                        ssd1306_color_t cur = ssd1306_get_pixel(sx, sy);
                        ssd1306_set_pixel(sx, sy, cur == SSD1306_COLOR_WHITE ? SSD1306_COLOR_BLACK : SSD1306_COLOR_WHITE);
                    }
                    break;
            }
        }
    }
}

void ssd1306_clear_area(uint8_t x, uint8_t y, uint8_t w, uint8_t h) {
    for (uint8_t i = 0; i < w; i++) {
        for (uint8_t j = 0; j < h; j++) {
            ssd1306_set_pixel(x + i, y + j, SSD1306_COLOR_BLACK);
        }
    }
}

// ============================================================================
// 表情库实现 (128x64 全屏表情)
// ============================================================================

void ssd1306_show_emo(uint8_t index) {
    if (index >= EMO_COUNT) return;
    ssd1306_clear();
    ssd1306_draw_xbm(0, 0, 128, 64, emo_list[index], SSD1306_DRAW_NORMAL);
    ssd1306_display();
}

void ssd1306_show_emo_mode(uint8_t index, ssd1306_draw_mode_t mode) {
    if (index >= EMO_COUNT) return;
    ssd1306_clear();
    ssd1306_draw_xbm(0, 0, 128, 64, emo_list[index], mode);
    ssd1306_display();
}
