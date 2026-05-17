#include "signal_slot.h"
#include <stdio.h>

/* 定义信号ID */
enum {
    SIG_BUTTON_PRESSED,
    SIG_TIMER_TICK,
    SIG_MAX
};

/* 槽函数示例1：带用户数据的LED控制 */
typedef struct {
    int led_pin;
    int blink_count;
} led_ctx_t;

void on_button_pressed(void *user_data, void *emit_arg)
{
    led_ctx_t *led = (led_ctx_t *)user_data;
    int press_count = (int)(intptr_t)emit_arg;  /* 发射时传递的按压次数 */
    printf("LED Pin %d: Button pressed %d times, blink count %d\n",
           led->led_pin, press_count, led->blink_count);
}

/* 槽函数示例2：无用户数据，只打印时间戳 */
void on_timer_tick(void *user_data, void *emit_arg)
{
    int tick = (int)(intptr_t)emit_arg;
    printf("Timer tick: %d\n", tick);
}

int main(void)
{
    /* 初始化信号槽框架 */
    signal_init();

    /* 准备用户数据 */
    led_ctx_t led1 = { .led_pin = 13, .blink_count = 3 };
    led_ctx_t led2 = { .led_pin = 14, .blink_count = 5 };

    /* 连接按钮按下信号的两个槽 */
    signal_connect(SIG_BUTTON_PRESSED, on_button_pressed, &led1);
    signal_connect(SIG_BUTTON_PRESSED, on_button_pressed, &led2);

    /* 连接定时器滴答信号 */
    signal_connect(SIG_TIMER_TICK, on_timer_tick, NULL);

    /* 发射信号 */
    signal_emit(SIG_BUTTON_PRESSED, (void *)(intptr_t)2);   /* 假设按钮被按下2次 */
    signal_emit(SIG_TIMER_TICK,   (void *)(intptr_t)100);

    /* 断开所有槽并重新连接测试 */
    signal_disconnect_all(SIG_BUTTON_PRESSED);
    signal_emit(SIG_BUTTON_PRESSED, (void *)(intptr_t)5);   /* 无输出 */

    return 0;
}