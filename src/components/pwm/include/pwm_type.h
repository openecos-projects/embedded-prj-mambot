#ifndef __PWM_TYPE_H__
#define __PWM_TYPE_H__

#include <stdint.h>

typedef struct {
    uint32_t pscr;
    uint32_t cmp;
} pwm_config_t;

typedef enum {
    PWM_CH0 = 0,
    PWM_CH1 = 1,
    PWM_CH2 = 2,
    PWM_CH3 = 3,
} pwm_channel_t;

#endif