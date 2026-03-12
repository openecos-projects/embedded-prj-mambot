#ifndef __SSD1306_TYPE_H__
#define __SSD1306_TYPE_H__

#include <stdint.h>

/**
 * @brief SSD1306 OLED配置结构体
 */
typedef struct {
    uint8_t i2c_addr;   // I2C地址 (通常为0x3C或0x3D)
    uint8_t width;      // 屏幕宽度 (128)
    uint8_t height;     // 屏幕高度 (64或32)
} ssd1306_config_t;

/**
 * @brief 像素颜色定义
 */
typedef enum {
    SSD1306_COLOR_BLACK = 0,  // 像素关闭
    SSD1306_COLOR_WHITE = 1,  // 像素点亮
} ssd1306_color_t;

/**
 * @brief 位图绘制模式
 */
typedef enum {
    SSD1306_DRAW_NORMAL = 0,     // 正常绘制
    SSD1306_DRAW_TRANSPARENT,    // 透明模式
    SSD1306_DRAW_INVERT,         // 反色绘制
    SSD1306_DRAW_XOR,            // 异或绘制
} ssd1306_draw_mode_t;

// SSD1306 I2C控制字节定义
#define SSD1306_CTRL_CMD        0x00
#define SSD1306_CTRL_CMD_CONT   0x80
#define SSD1306_CTRL_DATA       0x40
#define SSD1306_CTRL_DATA_CONT  0xC0

// SSD1306 常用命令定义
#define SSD1306_CMD_DISPLAY_OFF         0xAE
#define SSD1306_CMD_DISPLAY_ON          0xAF
#define SSD1306_CMD_SET_DISP_CLK_DIV    0xD5
#define SSD1306_CMD_SET_MUX_RATIO       0xA8
#define SSD1306_CMD_SET_DISP_OFFSET     0xD3
#define SSD1306_CMD_SET_START_LINE      0x40
#define SSD1306_CMD_CHARGE_PUMP         0x8D
#define SSD1306_CMD_MEM_ADDR_MODE       0x20
#define SSD1306_CMD_SEG_REMAP           0xA0
#define SSD1306_CMD_COM_SCAN_DIR        0xC0
#define SSD1306_CMD_SET_COM_PINS        0xDA
#define SSD1306_CMD_SET_CONTRAST        0x81
#define SSD1306_CMD_SET_PRECHARGE       0xD9
#define SSD1306_CMD_SET_VCOM_DESEL      0xDB
#define SSD1306_CMD_ENTIRE_DISP_ON      0xA4
#define SSD1306_CMD_SET_NORMAL_DISP     0xA6
#define SSD1306_CMD_SET_INVERSE_DISP    0xA7
#define SSD1306_CMD_SET_COL_ADDR        0x21
#define SSD1306_CMD_SET_PAGE_ADDR       0x22

#endif // __SSD1306_TYPE_H__
