#include "fsm.h"
#include <stdio.h>   // 仅为演示输出，实际MCU中替换为硬件操作

/* 用户定义的状态和事件 */
enum
{
    STATE_OFF = 0,
    STATE_ON,
    STATE_BLINK
};

enum
{
    EVENT_BUTTON = 0,
    EVENT_TIMEOUT
};

/* 上下文，例如指向硬件寄存器或设备结构体 */
typedef struct
{
    int led_id;
    /* 其他外设相关数据 */
} led_ctx_t;

/* 动作函数 */
static void led_turn_on(void *ctx)
{
    led_ctx_t *led = (led_ctx_t *)ctx;
    printf("LED %d ON\n", led->led_id);
    /* 实际硬件操作：GPIO_SetPin(...) */
}

static void led_turn_off(void *ctx)
{
    led_ctx_t *led = (led_ctx_t *)ctx;
    printf("LED %d OFF\n", led->led_id);
}

static void led_start_blink(void *ctx)
{
    led_ctx_t *led = (led_ctx_t *)ctx;
    printf("LED %d start blinking\n", led->led_id);
    /* 启动定时器 */
}

/* 进入/退出回调（可选） */
static void on_state_exit(fsm_t *fsm, fsm_state_t state)
{
    (void)fsm;
    printf("Leaving state %d\n", state);
    /* 例如：退出闪烁状态时停止定时器 */
}

static void on_state_enter(fsm_t *fsm, fsm_state_t state)
{
    (void)fsm;
    printf("Entering state %d\n", state);
}

/* 转换表（务必用 const，常驻 Flash） */
static const fsm_transition_t led_transitions[] =
{
    /* 当前状态     事件           下一状态       动作函数 */
    { STATE_OFF,     EVENT_BUTTON,  STATE_ON,      led_turn_on      },
    { STATE_ON,      EVENT_BUTTON,  STATE_OFF,     led_turn_off     },
    { STATE_ON,      EVENT_TIMEOUT, STATE_BLINK,   led_start_blink  },
    { STATE_BLINK,   EVENT_BUTTON,  STATE_OFF,     led_turn_off     },
    /* 通配规则：任何未处理事件都回到 OFF，并关闭 LED */
    { FSM_STATE_ANY, FSM_EVENT_ANY, STATE_OFF,     led_turn_off     },
};

int fsm_demo_main(void)
{
    led_ctx_t led = { .led_id = 1 };
    fsm_t fsm;

    /* 初始化状态机，初始为 OFF */
    fsm_init(&fsm, STATE_OFF, led_transitions,
             sizeof(led_transitions) / sizeof(led_transitions[0]),
             &led);

    /* 注册回调（可选） */
    fsm.on_state_exit  = on_state_exit;
    fsm.on_state_enter = on_state_enter;

    /* 模拟事件序列 */
    fsm_dispatch(&fsm, EVENT_BUTTON);   // OFF -> ON
    fsm_dispatch(&fsm, EVENT_TIMEOUT);  // ON  -> BLINK
    fsm_dispatch(&fsm, EVENT_BUTTON);   // BLINK -> OFF

    return 0;
}
