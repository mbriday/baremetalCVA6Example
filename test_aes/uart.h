#pragma once

#include <stdint.h>

void print_uart(const char* str);
void print_uart_int(uint32_t addr);
void print_uart_addr(uint64_t addr);
void print_uart_byte(uint8_t byte);