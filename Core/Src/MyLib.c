#include "mylib.h"

extern UART_HandleTypeDef DEBUG_UART;



uint32_t DEBUG_TICK_COUNT,stop_ticks,start_ticks;


/**
 * @brief 开始计时，记录当前 SysTick 的计数值
 *
 * 此函数会读取 SysTick 定时器的当前计数值，
 * 并将其存储在全局变量 start_ticks 中，作为计时的起始点。
 * 后续可以通过调用 DEBUG_Stop_Tick 函数来停止计时并计算经过的 tick 数。
 *
 * @note 该函数依赖于 SysTick 定时器的正常工作，确保 SysTick 已正确配置和初始化。
 *       同时，start_ticks 应为全局变量，以便在 DEBUG_Stop_Tick 函数中可以访问。
 */
void DEBUG_Start_Tick(void) {
    start_ticks=SysTick->VAL;
}

/**
 * @brief 停止计时并计算经过的 tick 数
 *
 * 此函数会读取 SysTick 定时器的当前计数值，
 * 结合之前调用 DEBUG_Start_Tick 函数记录的起始 tick 数，
 * 计算出从开始计时到当前时刻所经过的 tick 数。
 * 计算结果会存储在全局变量 DEBUG_TICK_COUNT 中，
 * 同时作为函数的返回值返回。
 *
 * @return 返回从开始计时到当前时刻所经过的 tick 数
 *
 * @note 调用此函数前必须先调用 DEBUG_Start_Tick 函数，否则计算结果将不准确。
 *       该函数依赖于 SysTick 定时器的正常工作，确保 SysTick 已正确配置和初始化。
 *       start_ticks 和 DEBUG_TICK_COUNT 应为全局变量。
 */uint32_t DEBUG_Stop_Tick(void) {
    stop_ticks = SysTick->VAL;
    DEBUG_TICK_COUNT=start_ticks - stop_ticks;
    return DEBUG_TICK_COUNT;
}    

void handle_overflow(uint32_t *value, int32_t delta, uint32_t lower_limit, uint32_t upper_limit) {
    if (delta >= 0) {
        // 当 delta 为正数，做加法操作，需要检查是否会超过上限
        if (upper_limit - *value < (uint32_t)delta) {
            // 如果加上 delta 会超过上限，将 value 设置为上限
            *value = upper_limit;
        } else {
            // 否则正常加上 delta
            *value += (uint32_t)delta;
        }
    } else {
        // 当 delta 为负数，做减法操作，需要检查是否会低于下限
        uint32_t abs_delta = (uint32_t)(-delta);
        if (*value < lower_limit + abs_delta) {
            // 如果减去 delta 的绝对值会低于下限，将 value 设置为下限
            *value = lower_limit;
        } else {
            // 否则正常减去 delta 的绝对值
            *value -= abs_delta;
        }
    }
}



// keil should use microlib


// #ifdef __GNUC__
// int __io_putchar(int ch)
// {
//     HAL_UART_Transmit(&hlpuart1, (uint8_t*)&ch, 1, HAL_MAX_DELAY);
//     return ch;
// }
// #endif


// #ifdef __CC_ARM
// int fputc(int ch, FILE *f)
// {
//     /* 发送一个字节数据到串口 USARTx */
//     HAL_UART_Transmit(&hlpuart1, (uint8_t*)&ch, 1, HAL_MAX_DELAY);
//     return (ch);
// }
// #endif
