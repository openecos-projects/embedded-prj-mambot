#ifndef __SSD1306_H__
#define __SSD1306_H__

#include "ssd1306_type.h"
#include "emo_data.h"

/**
 * @brief 初始化SSD1306 OLED显示屏
 *
 * @param config 指向ssd1306_config_t结构体的指针
 */
void ssd1306_init(ssd1306_config_t* config);

/**
 * @brief 清空显示缓冲区
 */
void ssd1306_clear(void);

/**
 * @brief 将显示缓冲区内容刷新到屏幕
 */
void ssd1306_display(void);

/**
 * @brief 设置显示对比度
 *
 * @param contrast 对比度值 (0-255)
 */
void ssd1306_set_contrast(uint8_t contrast);

/**
 * @brief 设置显示反色模式
 *
 * @param invert 0:正常显示, 1:反色显示
 */
void ssd1306_invert(uint8_t invert);

/**
 * @brief 开启/关闭显示
 *
 * @param on 0:关闭显示, 1:开启显示
 */
void ssd1306_display_on(uint8_t on);

/**
 * @brief 设置单个像素点
 *
 * @param x X坐标 (0 ~ width-1)
 * @param y Y坐标 (0 ~ height-1)
 * @param color 像素颜色 (SSD1306_COLOR_BLACK 或 SSD1306_COLOR_WHITE)
 */
void ssd1306_set_pixel(uint8_t x, uint8_t y, ssd1306_color_t color);

/**
 * @brief 获取单个像素点的颜色
 *
 * @param x X坐标
 * @param y Y坐标
 * @return ssd1306_color_t 像素颜色
 */
ssd1306_color_t ssd1306_get_pixel(uint8_t x, uint8_t y);

/**
 * @brief 画直线 (Bresenham算法)
 *
 * @param x0 起点X坐标
 * @param y0 起点Y坐标
 * @param x1 终点X坐标
 * @param y1 终点Y坐标
 */
void ssd1306_draw_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);

/**
 * @brief 画水平线
 *
 * @param x 起点X坐标
 * @param y Y坐标
 * @param w 线宽度
 */
void ssd1306_draw_hline(uint8_t x, uint8_t y, uint8_t w);

/**
 * @brief 画垂直线
 *
 * @param x X坐标
 * @param y 起点Y坐标
 * @param h 线高度
 */
void ssd1306_draw_vline(uint8_t x, uint8_t y, uint8_t h);

/**
 * @brief 画矩形边框
 *
 * @param x 左上角X坐标
 * @param y 左上角Y坐标
 * @param w 宽度
 * @param h 高度
 */
void ssd1306_draw_rect(uint8_t x, uint8_t y, uint8_t w, uint8_t h);

/**
 * @brief 画填充矩形
 *
 * @param x 左上角X坐标
 * @param y 左上角Y坐标
 * @param w 宽度
 * @param h 高度
 */
void ssd1306_fill_rect(uint8_t x, uint8_t y, uint8_t w, uint8_t h);

/**
 * @brief 在指定位置绘制单个字符 (5x7字体)
 *
 * @param x X坐标
 * @param y Y坐标
 * @param c 要显示的ASCII字符
 */
void ssd1306_draw_char(uint8_t x, uint8_t y, char c);

/**
 * @brief 在指定位置绘制字符串
 *
 * @param x X坐标
 * @param y Y坐标
 * @param str 要显示的字符串
 */
void ssd1306_draw_string(uint8_t x, uint8_t y, const char* str);

/**
 * @brief 填充整个屏幕为指定颜色
 *
 * @param color 填充颜色
 */
void ssd1306_fill(ssd1306_color_t color);

/**
 * @brief 画圆边框 (中点圆算法)
 *
 * @param x0 圆心X坐标
 * @param y0 圆心Y坐标
 * @param r 半径
 */
void ssd1306_draw_circle(uint8_t x0, uint8_t y0, uint8_t r);

/**
 * @brief 画实心圆
 *
 * @param x0 圆心X坐标
 * @param y0 圆心Y坐标
 * @param r 半径
 */
void ssd1306_fill_circle(uint8_t x0, uint8_t y0, uint8_t r);

// ============================================================================
// 位图绘制API
// ============================================================================

/**
 * @brief 绘制XBM格式位图
 */
void ssd1306_draw_xbm(uint8_t x, uint8_t y, uint8_t w, uint8_t h,
                      const uint8_t* data, ssd1306_draw_mode_t mode);

/**
 * @brief 清除指定矩形区域
 */
void ssd1306_clear_area(uint8_t x, uint8_t y, uint8_t w, uint8_t h);

void ssd1306_show_emo(uint8_t index);

#endif