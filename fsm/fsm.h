#ifndef FSM_H
#define FSM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
/* 状态和事件类型，用户可自行 typedef 为其他整数类型 */
typedef int fsm_state_t;
typedef int fsm_event_t;

/* 通配值：匹配任意状态或任意事件（请勿将其用作有效状态/事件） */
#define FSM_STATE_ANY  ((fsm_state_t)-1)
#define FSM_EVENT_ANY  ((fsm_event_t)-1)

/**
 * @brief 状态转换表中的一条记录
 */
typedef struct {
    fsm_state_t current_state;  /**< 当前状态（可用 FSM_STATE_ANY 通配） */
    fsm_event_t event;          /**< 触发事件（可用 FSM_EVENT_ANY 通配） */
    fsm_state_t next_state;     /**< 目标状态 */
    void (*action)(void *ctx);  /**< 转换动作，参数为用户上下文 */
} fsm_transition_t;

/* 前向声明 */
struct fsm_s;

/**
 * @brief 状态进入/退出回调类型
 * @param fsm 状态机指针
 * @param state 当前离开或进入的状态
 */
typedef void (*fsm_state_callback_t)(struct fsm_s *fsm, fsm_state_t state);

/**
 * @brief 有限状态机控制块
 */
typedef struct fsm_s {
    fsm_state_t         current_state;      /**< 当前状态 */
    const fsm_transition_t *transitions;    /**< 转换表指针（常量数组） */
    int                 num_transitions;    /**< 转换表条目数 */
    void               *context;            /**< 用户上下文，会传给 action */

    fsm_state_callback_t on_state_exit;     /**< 离开状态回调（可为 NULL） */
    fsm_state_callback_t on_state_enter;    /**< 进入状态回调（可为 NULL） */
} fsm_t;

/**
 * @brief 初始化状态机
 * @param fsm         状态机指针
 * @param initial_state 初始状态
 * @param transitions 转换表数组（静态分配）
 * @param num         转换表条目数
 * @param context     用户上下文指针
 */
void fsm_init(fsm_t *fsm,
              fsm_state_t initial_state,
              const fsm_transition_t *transitions,
              int num,
              void *context);

/**
 * @brief 向状态机投递事件并执行相应转换
 * @param fsm   状态机指针
 * @param event 事件值
 * @note 如果找到匹配的转换，依次执行：on_state_exit → action → on_state_enter
 *       未找到匹配时不做任何操作（可扩展）
 */
void fsm_dispatch(fsm_t *fsm, fsm_event_t event);

/**
 * @brief 强制设置状态（不触发任何回调）
 * @param fsm   状态机指针
 * @param state 新状态
 */
void fsm_reset_state(fsm_t *fsm, fsm_state_t state);

/**
 * @brief 获取当前状态
 */
static inline fsm_state_t fsm_get_state(const fsm_t *fsm)
{
    return fsm->current_state;
}

#ifdef __cplusplus
}
#endif

#endif /* FSM_H */
