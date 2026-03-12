#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>



typedef struct {
    uint32_t tick_h;
    uint32_t tick_l;
} sys_tick_t;
void delay_us(uint32_t val);
void delay_ms(uint32_t val);
void delay_s(uint32_t val);
void sys_tick_init(void);
uint32_t get_sys_tick(void);
#endif