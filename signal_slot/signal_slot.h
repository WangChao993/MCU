#ifndef SIGNAL_SLOT_H
#define SIGNAL_SLOT_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* 用户可配置项：最大信号数量及每个信号的最大槽数量 */
#ifndef MAX_SIGNALS
#define MAX_SIGNALS         10
#endif

#ifndef MAX_SLOTS_PER_SIGNAL
#define MAX_SLOTS_PER_SIGNAL    5
#endif

/* 槽函数类型：user_data为连接时绑定的用户数据，emit_arg为发射信号时传入的参数 */
typedef void (*slot_func_t)(void *user_data, void *emit_arg);

/**
 * @brief 初始化信号槽框架（将所有信号槽清空）
 */
void signal_init(void);

/**
 * @brief 连接信号与槽
 * @param sig_id    信号ID（0 ~ MAX_SIGNALS-1）
 * @param func      槽函数指针
 * @param user_data 与槽绑定的用户数据，槽函数调用时作为第一个参数传入
 * @return 0:成功, -1:信号ID无效, -2:该信号的槽已满
 */
int signal_connect(int sig_id, slot_func_t func, void *user_data);

/**
 * @brief 断开信号与指定槽的连接（删除所有匹配项）
 * @param sig_id    信号ID
 * @param func      槽函数指针
 * @param user_data 用户数据（必须与连接时完全相同）
 * @return 删除的槽数量，-1表示信号ID无效
 */
int signal_disconnect(int sig_id, slot_func_t func, void *user_data);

/**
 * @brief 断开信号的所有槽
 * @param sig_id    信号ID
 * @return 删除的槽数量，-1表示信号ID无效
 */
int signal_disconnect_all(int sig_id);

/**
 * @brief 发射信号，调用所有连接的槽
 * @param sig_id    信号ID
 * @param emit_arg  发射时传递的参数，将作为第二个参数传入槽函数
 */
void signal_emit(int sig_id, void *emit_arg);

#ifdef __cplusplus
}
#endif

#endif /* SIGNAL_SLOT_H */