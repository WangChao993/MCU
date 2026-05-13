#include "fsm.h"

/**
 * @brief 在转换表中查找第一个匹配当前状态和事件的条目
 * @return 匹配条目指针，未找到返回 NULL
 */
static const fsm_transition_t *find_transition(const fsm_t *fsm, fsm_event_t event)
{
    for (int i = 0; i < fsm->num_transitions; ++i)
    {
        const fsm_transition_t *t = &fsm->transitions[i];
        if ((t->current_state == fsm->current_state || t->current_state == FSM_STATE_ANY) &&
            (t->event == event || t->event == FSM_EVENT_ANY))
        {
            return t;
        }
    }
    return NULL;
}

void fsm_init(fsm_t *fsm,
              fsm_state_t initial_state,
              const fsm_transition_t *transitions,
              int num,
              void *context)
{
    fsm->current_state   = initial_state;
    fsm->transitions     = transitions;
    fsm->num_transitions = num;
    fsm->context         = context;
    fsm->on_state_exit   = NULL;
    fsm->on_state_enter  = NULL;
}

void fsm_dispatch(fsm_t *fsm, fsm_event_t event)
{
    const fsm_transition_t *t = find_transition(fsm, event);
    if (t)
    {
        fsm_state_t old_state = fsm->current_state;

        /* 1. 离开旧状态 */
        if (fsm->on_state_exit)
        {
            fsm->on_state_exit(fsm, old_state);
        }

        /* 2. 执行转换动作（如果有） */
        if (t->action)
        {
            t->action(fsm->context);
        }

        /* 3. 更新状态 */
        fsm->current_state = t->next_state;

        /* 4. 进入新状态 */
        if (fsm->on_state_enter)
        {
            fsm->on_state_enter(fsm, fsm->current_state);
        }
    }
    /* else: 事件无匹配，静默忽略（可在此记录日志或触发错误处理） */
}

void fsm_reset_state(fsm_t *fsm, fsm_state_t state)
{
    fsm->current_state = state;
}
