#include "sg90.h"
#include "main.h"
#include "ssd1306.h"
#include "hp_uart.h"

void main(void){
    sys_uart_init();

    init_sg90();

    action_test_which_is_which2();
    
    ssd1306_config_t oled_cfg = {
        .i2c_addr = 0x3C,   // 常见I2C地址
        .width = 128,
        .height = 64,
    };
    ssd1306_init(&oled_cfg);
    
    hp_uart_init(115200);

    ssd1306_show_emo(0); // show logo
    delay_s(1);
    ssd1306_show_emo(6);
    set_all_sg90_degree(90, 90, 90, 90);

    char uart_rev = 0;
    while(1){
        hp_uart_recv(&uart_rev);
        printf("uart_rev: %x\n", uart_rev);

        switch(uart_rev){
            case 0xaa: // handshake
                ssd1306_show_emo(5);
                for(int i = 0; i < 5; i ++) {
                    set_all_sg90_degree(10, 90, 90, 90);
                    delay_ms(200);
                    set_all_sg90_degree(60, 90, 90, 90);
                    delay_ms(200);
                }
                for(int i = 0; i < 5; i ++) {
                    set_all_sg90_degree(90, 10, 90, 90);
                    delay_ms(200);
                    set_all_sg90_degree(90, 60, 90, 90);
                    delay_ms(200);
                }
                set_all_sg90_degree(90, 90, 90, 90);
            break;
            case 0xab: // standup
                ssd1306_show_emo(6);
                set_all_sg90_degree(90, 90, 90, 90);
            break;
            case 0xac: // stepforward
                ssd1306_show_emo(2);
                set_all_sg90_degree(90, 90, 90, 90);
                delay_ms(200);
                for (int i = 0; i < 5; i ++) {
                    set_all_sg90_degree(
                        deg_pos_neg(40), // front_right
                        deg_pos_neg(0), // front_left
                        deg_pos_neg(40), // back_left
                        deg_pos_neg(0)); // back_right
                    delay_ms(200);
                    set_all_sg90_degree(
                        deg_pos_neg(40), // front_right
                        deg_pos_neg(-40), // front_left
                        deg_pos_neg(40), // back_left
                        deg_pos_neg(-40)); // back_right
                    delay_ms(200);
                    set_all_sg90_degree(
                        deg_pos_neg(0), // front_right
                        deg_pos_neg(-40), // front_left
                        deg_pos_neg(0), // back_left
                        deg_pos_neg(-40)); // back_right
                    delay_ms(200);
                    set_all_sg90_degree(
                        deg_pos_neg(0), // front_right
                        deg_pos_neg(0), // front_left
                        deg_pos_neg(0), // back_left
                        deg_pos_neg(0)); // back_right
                    delay_ms(200);
                    }
            break;
            case 0xad: // stepbackward
                ssd1306_show_emo(7);
                set_all_sg90_degree(90, 90, 90, 90);
                delay_ms(200);
                for (int i = 0; i < 5; i ++) {
                    set_all_sg90_degree(
                        deg_pos_neg(-40), // front_right
                        deg_pos_neg(0), // front_left
                        deg_pos_neg(-40), // back_left
                        deg_pos_neg(0)); // back_right
                    delay_ms(200);
                    set_all_sg90_degree(
                        deg_pos_neg(-40), // front_right
                        deg_pos_neg(40), // front_left
                        deg_pos_neg(-40), // back_left
                        deg_pos_neg(40)); // back_right
                    delay_ms(200);
                    set_all_sg90_degree(
                        deg_pos_neg(0), // front_right
                        deg_pos_neg(40), // front_left
                        deg_pos_neg(0), // back_left
                        deg_pos_neg(40)); // back_right
                    delay_ms(200);
                    set_all_sg90_degree(
                        deg_pos_neg(0), // front_right
                        deg_pos_neg(0), // front_left
                        deg_pos_neg(0), // back_left
                        deg_pos_neg(0)); // back_right
                    delay_ms(200);
                }
            break;
            case 0xbb: // turnleft
                ssd1306_clear();
                ssd1306_fill_rect(36, 12, 20, 32);
                ssd1306_fill_rect(88, 16, 16, 24);
                ssd1306_display();
                set_all_sg90_degree(90, 90, 90, 90);
                delay_ms(200);
                for (int i = 0; i < 5; i ++) {
                    set_all_sg90_degree(
                        deg_pos_neg(0), // front_right
                        deg_pos_neg(-40), // front_left
                        deg_pos_neg(0), // back_left
                        deg_pos_neg(40)); // back_right
                    delay_ms(200);
                    set_all_sg90_degree(
                        deg_pos_neg(-40), // front_right
                        deg_pos_neg(-40), // front_left
                        deg_pos_neg(40), // back_left
                        deg_pos_neg(40)); // back_right
                    delay_ms(200);
                    set_all_sg90_degree(
                        deg_pos_neg(-40), // front_right
                        deg_pos_neg(0), // front_left
                        deg_pos_neg(40), // back_left
                        deg_pos_neg(0)); // back_right
                    delay_ms(200);
                    set_all_sg90_degree(
                        deg_pos_neg(0), // front_right
                        deg_pos_neg(0), // front_left
                        deg_pos_neg(0), // back_left
                        deg_pos_neg(0)); // back_right
                    delay_ms(200);
                }
            break;
            case 0xbc: // turnright
                ssd1306_clear();
                ssd1306_fill_rect(24, 16, 16, 24);
                ssd1306_fill_rect(72, 12, 20, 32);
                ssd1306_display();
                set_all_sg90_degree(90, 90, 90, 90);
                delay_ms(200);
                for (int i = 0; i < 5; i ++) {
                    set_all_sg90_degree(
                        deg_pos_neg(0), // front_right
                        deg_pos_neg(40), // front_left
                        deg_pos_neg(0), // back_left
                        deg_pos_neg(-40)); // back_right
                    delay_ms(200);
                    set_all_sg90_degree(
                        deg_pos_neg(40), // front_right
                        deg_pos_neg(40), // front_left
                        deg_pos_neg(-40), // back_left
                        deg_pos_neg(-40)); // back_right
                    delay_ms(200);
                    set_all_sg90_degree(
                        deg_pos_neg(40), // front_right
                        deg_pos_neg(0), // front_left
                        deg_pos_neg(-40), // back_left
                        deg_pos_neg(0)); // back_right
                    delay_ms(200);
                    set_all_sg90_degree(
                        deg_pos_neg(0), // front_right
                        deg_pos_neg(0), // front_left
                        deg_pos_neg(0), // back_left
                        deg_pos_neg(0)); // back_right
                    delay_ms(200);
                }
            break;
            case 0xbd: // laydown
                ssd1306_show_emo(1);
                action_laydown();
            break;
            case 0xbf: // rap
                for(int i = 0; i < 5; i ++) {
                    set_all_sg90_degree(
                        deg_pos_neg(-70), // front_right
                        deg_pos_neg(-70), // front_left
                        deg_pos_neg(-70), // back_left
                        deg_pos_neg(-70)); // back_right
                    delay_ms(400);
                    set_all_sg90_degree(
                        deg_pos_neg(70), // front_right
                        deg_pos_neg(70), // front_left
                        deg_pos_neg(70), // back_left
                        deg_pos_neg(70)); // back_right
                    delay_ms(400);
                }
                set_all_sg90_degree(90, 90, 90, 90);
            break;
            default:
            break;
        }
    }
}