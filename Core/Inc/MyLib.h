#ifndef MYLIB_H
#define MYLIB_H



#include "stm32g4xx_hal.h"
#include "main.h"
#include <stdint.h>
#include "stdio.h"
#include "string.h"
#include "math.h"

#define DEBUG_UART hlpuart1


extern uint32_t DEBUG_TICK_COUNT;
/**
 * @brief 通用越界处理函数，可对无符号 32 位整数进行越界检查与调整
 *
 * 该函数接收一个指向无符号 32 位整数的指针、一个调整值以及上下限范围，
 * 依据调整值对指针所指的变量进行相应调整，并保证调整后的结果处于指定的上下限范围内。
 *
 * @param value 指向需要进行越界检查和调整的无符号 32 位整数的指针。
 *        函数会直接修改该指针所指向的变量的值，使其符合上下限要求。
 * @param delta 对 *value 进行调整的值，该值可以是正数或者负数。
 *        若为正数，则表示对 *value 进行加法操作；若为负数，则表示进行减法操作。
 * @param lower_limit 调整结果允许的下限值，取值范围为 0 到 UINT32_MAX（无符号 32 位整数的最大值）。
 *        当调整后的结果小于此值时，函数会将 *value 设置为此下限值，以确保不越界。
 * @param upper_limit 调整结果允许的上限值，取值范围同样为 0 到 UINT32_MAX。
 *        当调整后的结果大于此值时，函数会将 *value 设置为此上限值，防止结果超出范围。
 *
 * @return 此函数没有返回值，而是直接修改传入指针所指向的变量的值。
 *
 * @note
 * 1. 输入参数中 lower_limit 应小于等于 upper_limit，否则可能导致不符合预期的结果。
 * 2. 由于函数直接修改指针所指向的变量，调用时需确保指针有效，避免空指针异常。
 */
void handle_overflow(uint32_t *value, int32_t delta, uint32_t lower_limit, uint32_t upper_limit);



void DEBUG_Start_Tick(void);

uint32_t DEBUG_Stop_Tick(void);    

// //STM32CubeIDE
// #ifdef __GNUC__
// int __io_putchar(int ch);
// #endif


// //keil MDK
// #ifdef __CC_ARM
// int fputc(int ch, FILE *f);
// #endif

#endif // MYLIB_H
