#ifndef OBSERVER_H
#define OBSERVER_H

#include <stdint.h>
#include <string.h>

#include "observer_topic_type.h"
// 通用配置
#define MAX_OBSERVERS_PER_MANAGER 6

// 通用函数指针类型
typedef void (*ObserverCallback)(void* data, uint16_t length, uint16_t type);

// ==================== 高效版本（预定义ID）====================
// 适合性能要求高、管理器固定的场景
#define MANAGER_ID(A) 	MANAGER_ID_##A
// 预定义管理器ID
typedef enum {
    MANAGER_ID(debug) = 0,
    MANAGER_ID(device),
	MANAGER_ID(uart),
    MANAGER_ID(hardware),//硬件 
	MANAGER_ID(storage),	
    MANAGER_COUNT  // 管理器总数
} ManagerID;

// 高效版本函数声明
int     observer_eff_init(void);
uint8_t observer_eff_register(ManagerID id, ObserverCallback callback);
void    observer_eff_notify(ManagerID id, void* data, uint16_t length, uint16_t type);
void    observer_eff_print_all(void);
void    observer_eff_print_manager(ManagerID id);
uint8_t observer_eff_get_observer_count(ManagerID id);


#endif
