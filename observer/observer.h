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

// ==================== 灵活版本（字符串名称）====================
// 适合需要动态创建、灵活性高的场景

// 灵活版本配置
#define FLEX_MAX_MANAGERS 8
#define FLEX_MAX_NAME_LENGTH 16

// 管理器结构
typedef struct {
    ObserverCallback callbacks[MAX_OBSERVERS_PER_MANAGER];
    uint8_t observer_count;
    char name[FLEX_MAX_NAME_LENGTH];
} FlexObserverManager;

// 系统结构
typedef struct {
    FlexObserverManager managers[FLEX_MAX_MANAGERS];
    uint8_t manager_count;
} FlexObserverSystem;

// 灵活版本函数声明
void observer_flex_init(FlexObserverSystem* system);
uint8_t observer_flex_register(FlexObserverSystem* system, const char* manager_name, ObserverCallback callback);
void observer_flex_notify(FlexObserverSystem* system, const char* manager_name, void* data, uint16_t length, uint16_t type);
FlexObserverManager* observer_flex_get_manager(FlexObserverSystem* system, const char* manager_name);
void observer_flex_print_all(FlexObserverSystem* system);
void observer_flex_print_manager(FlexObserverSystem* system, const char* manager_name);
uint8_t observer_flex_get_manager_count(FlexObserverSystem* system);
uint8_t observer_flex_get_observer_count(FlexObserverSystem* system, const char* manager_name);

#endif
