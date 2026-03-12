#include <stdint.h>
#include "string.h"
#include "stdio.h"
#include "generated/autoconf.h"

extern uint32_t app_start;
extern uint32_t app_end;

#define APP_ENTRY CONFIG_LINK_ADDRESS

void main() {
    sys_uart_init();

    uint32_t *src = (uint32_t *)&app_start;
    uint32_t *dest = (uint32_t *)APP_ENTRY;
    uint32_t *end = (uint32_t *)&app_end;
    // 计算总字节数
    uint32_t total = (uint32_t)((uintptr_t)&app_end - (uintptr_t)&app_start);
    uint32_t copied = 0;
    uint32_t percent = 0;
    uint32_t last_percent = 0;
    uint32_t *pre = src;
    
    // 打印起始进度
    // sys_putstr("Loading:");
    sys_putchar('L');
    sys_putchar('O');
    sys_putchar('A');
    sys_putchar('D');
    sys_putchar('I');
    sys_putchar('N');
    sys_putchar('G');
    sys_putchar(':');
    sys_putchar(' ');

    uint32_t step = (uint32_t)(&app_end - &app_start) / 128;
    // Copy payload to RAM
    while (src < end) {
        *dest++ = *src++;
        copied += sizeof(uint32_t);
        if ((uint32_t)(src - pre) >= step){
            sys_putchar('#');
            pre = src;
        }
    }
    sys_putchar('\r');
    sys_putchar('\n');
    

    // Flush instruction cache (using fence.i instruction)
    asm volatile("fence.i");
    
    // Jump to app
    void (*app_entry)() = (void (*)())APP_ENTRY;
    app_entry();
    
}
