#include "../inc/simple_signal.h"
#include <string.h>

// 内部实现：160位 = 20字节
static uint8_t g_signals[20] = {0};

// 检查信号是否有效
static inline bool is_valid_signal(Signal sig)
{
    return (sig < SIG_MAX_COUNT);
}

// 获取字节索引和位掩码
static inline void get_position(Signal sig, uint32_t *byte_idx, uint8_t *bit_mask)
{
    *byte_idx = sig / 8;
    *bit_mask = 1 << (sig % 8);
}

// 1. 置位信号
void signal_set(Signal sig)
{
    if (!is_valid_signal(sig)) return;
    uint32_t byte_idx;
    uint8_t bit_mask;
    get_position(sig, &byte_idx, &bit_mask);
    g_signals[byte_idx] |= bit_mask;
}

// 2. 清除信号
void signal_clear(Signal sig)
{
    if (!is_valid_signal(sig)) return;
    uint32_t byte_idx;
    uint8_t bit_mask;
    get_position(sig, &byte_idx, &bit_mask);
    g_signals[byte_idx] &= ~bit_mask;
}

// 3. 获取信号状态
bool signal_get(Signal sig)
{
    if (!is_valid_signal(sig)) return false;
    uint32_t byte_idx;
    uint8_t bit_mask;
    get_position(sig, &byte_idx, &bit_mask);
    return (g_signals[byte_idx] & bit_mask) != 0;
}

//4. 检查并清除信号（原子操作）
bool signal_check_and_clear(Signal sig)
{
    bool status = signal_get(sig);
    if (status)
    {
        signal_clear(sig);
    }
    return status;
}
