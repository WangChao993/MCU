#include "signal_slot.h"
#include <stddef.h>

/* 单个槽的结构 */
typedef struct {
    slot_func_t func;
    void *user_data;
} slot_t;

/* 信号的结构：包含槽数组及当前有效槽数量 */
typedef struct {
    slot_t slots[MAX_SLOTS_PER_SIGNAL];
    uint8_t count;
} signal_t;

/* 全局信号表，静态分配，自动零初始化 */
static signal_t signals[MAX_SIGNALS];

void signal_init(void)
{
    for (int i = 0; i < MAX_SIGNALS; i++) {
        signals[i].count = 0;
        /* 可选：将func指针置NULL，便于调试 */
        for (int j = 0; j < MAX_SLOTS_PER_SIGNAL; j++) {
            signals[i].slots[j].func = NULL;
            signals[i].slots[j].user_data = NULL;
        }
    }
}

int signal_connect(int sig_id, slot_func_t func, void *user_data)
{
    if (sig_id < 0 || sig_id >= MAX_SIGNALS) {
        return -1;
    }
    if (func == NULL) {
        return -2;
    }
    signal_t *sig = &signals[sig_id];
    if (sig->count >= MAX_SLOTS_PER_SIGNAL) {
        return -2; /* 槽已满 */
    }
    /* 添加新槽 */
    sig->slots[sig->count].func = func;
    sig->slots[sig->count].user_data = user_data;
    sig->count++;
    return 0;
}

int signal_disconnect(int sig_id, slot_func_t func, void *user_data)
{
    if (sig_id < 0 || sig_id >= MAX_SIGNALS) {
        return -1;
    }
    if (func == NULL) {
        return 0;
    }
    signal_t *sig = &signals[sig_id];
    int removed = 0;
    /* 遍历数组，删除所有匹配的槽 */
    for (int i = 0; i < sig->count; ) {
        if (sig->slots[i].func == func && sig->slots[i].user_data == user_data) {
            /* 将后面的槽前移 */
            for (int j = i; j < sig->count - 1; j++) {
                sig->slots[j] = sig->slots[j + 1];
            }
            sig->count--;
            removed++;
            /* 继续检查当前位置（原下一个槽已前移） */
        } else {
            i++;
        }
    }
    return removed;
}

int signal_disconnect_all(int sig_id)
{
    if (sig_id < 0 || sig_id >= MAX_SIGNALS) {
        return -1;
    }
    signal_t *sig = &signals[sig_id];
    int removed = sig->count;
    sig->count = 0;
    return removed;
}

void signal_emit(int sig_id, void *emit_arg)
{
    if (sig_id < 0 || sig_id >= MAX_SIGNALS) {
        return;
    }
    signal_t *sig = &signals[sig_id];
    /* 注意：遍历过程中不应修改当前信号的连接列表，否则可能导致未定义行为。
       用户需保证在槽函数内不对同一信号执行 connect/disconnect 操作。 */
    for (int i = 0; i < sig->count; i++) {
        slot_t *slot = &sig->slots[i];
        if (slot->func != NULL) {
            slot->func(slot->user_data, emit_arg);
        }
    }
}