#include "sg90.h"
#include "pwm.h"
#include "timer.h"
#include "gpio.h"
#include <stdio.h>

SG90_channel_t front_right = SG90_CH0;
SG90_channel_t front_left = SG90_CH1;
SG90_channel_t back_left = SG90_CH2;
SG90_channel_t back_right = SG90_CH3;

void set_sg90_degree(SG90_channel_t sg90_channel, int degree) {
    int cmp_value = 0;
    if(sg90_channel == SG90_CH1 || sg90_channel == SG90_CH2) {
        cmp_value = (180 - degree) * 2000 / 180 + 17500;
    } else {
        cmp_value = degree * 2000 / 180 + 17500;
    }

    SG90_channel_t real_channel;
    switch(sg90_channel) {
        case SG90_CH0:
            real_channel = SG90_CH0;
            break;
        case SG90_CH1:
            real_channel = SG90_CH2;
            break;
        case SG90_CH2:
            real_channel = SG90_CH1;
            break;
        case SG90_CH3:
            real_channel = SG90_CH3;
            break;
        default:
            return;
    }

    // cmp_value = degree * 2000 / 180 + 17500;
    pwm_set_compare(real_channel, cmp_value);
}

void set_all_sg90_degree(int fr, int fl, int bl, int br) {
    set_sg90_degree(front_right, fr);
    set_sg90_degree(front_left, fl);
    set_sg90_degree(back_left, bl);
    set_sg90_degree(back_right, br);
}

void init_sg90(void) {
    pwm_config_t pwm_config = {
        .pscr = 72 - 1,
        .cmp = 20000 - 1, // 72M / 72 / 20000 = 50Hz
    };
    pwm_init(&pwm_config);
    // set_all_sg90_degree(0, 0, 0, 0);
}

void action_laydown() {
    set_all_sg90_degree(40, 40, 140, 140); 
}

void action_test_which_is_which() {
    set_all_sg90_degree(90, 0, 0, 0);
    delay_s(1);
    set_all_sg90_degree(0, 90, 0, 0);
    delay_s(1);
    set_all_sg90_degree(0, 0, 90, 0);
    delay_s(1);
    set_all_sg90_degree(0, 0, 0, 90);
    delay_s(1);
}

void action_test_which_is_which2() {
    set_all_sg90_degree(0, 0, 0, 0);
    set_sg90_degree(front_left, 90);
    delay_s(1);
    set_sg90_degree(front_right, 90);
    delay_s(1);
    set_sg90_degree(back_left, 90);
    delay_s(1);
    set_sg90_degree(back_right, 90);
    delay_s(1);
}

int deg_pos_neg(int deg) {
    return 90 - deg;
}
