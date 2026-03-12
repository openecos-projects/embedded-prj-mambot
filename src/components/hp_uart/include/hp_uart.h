#ifndef __HP_UART_H__
#define __HP_UART_H__

#include <stdint.h>

void hp_uart_init(uint32_t baudrate);
void hp_uart_send(char c);
void hp_uart_send_str(char* str);
void hp_uart_recv(char* c);
void hp_uart_recv_str(char* str);
#endif