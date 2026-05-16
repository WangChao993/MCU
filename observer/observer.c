#include "observer.h"
#include <stdio.h>

#include "../inc/tool.h"
 
// 高效版本的全局管理器数组
static FlexObserverManager g_managers[MANAGER_COUNT] = {
    { .name = "debug",     .observer_count = 0 },
    { .name = "device",    .observer_count = 0 },
    { .name = "uart",      .observer_count = 0 },
    { .name = "hardware",  .observer_count = 0 },
    { .name = "storage",   .observer_count = 0 }
};

// 初始化高效版本系统
int observer_eff_init(void) 
{
    for (int i = 0; i < MANAGER_COUNT; i++) 
	{
        g_managers[i].observer_count = 0;
        for (int j = 0; j < MAX_OBSERVERS_PER_MANAGER; j++) 
		{
            g_managers[i].callbacks[j] = NULL;
        }
    }
	//
	return 0;
}

// 注册观察者（高效版本）
uint8_t observer_eff_register(ManagerID id, ObserverCallback callback) 
{
    if (id >= MANAGER_COUNT || callback == NULL) 
	{
        return 0;
    }
    
    FlexObserverManager* manager = &g_managers[id];
    if (manager->observer_count >= MAX_OBSERVERS_PER_MANAGER) 
	{
        return 0;
    }
    
    // 检查是否已注册
    for (int i = 0; i < manager->observer_count; i++) 
	{
        if (manager->callbacks[i] == callback) 
		{
            return 1; // 已存在
        }
    }
    // 注册新观察者
    manager->callbacks[manager->observer_count++] = callback;
    return 1;
}

// 发布通知（高效版本）
void observer_eff_notify(ManagerID id, void* data, uint16_t length, uint16_t type) 
{
    if (id >= MANAGER_COUNT || data == NULL || length == 0) 
	{
        return;
    }
    
    FlexObserverManager* manager = &g_managers[id];
    for (int i = 0; i < manager->observer_count; i++) 
	{
        if (manager->callbacks[i] != NULL) 
		{
            manager->callbacks[i](data, length, type);
        }
    }
}

// 打印所有管理器状态（高效版本）
void observer_eff_print_all(void) {
    printf("\n=== 高效版本 - 系统状态 ===\n");
    printf("预定义管理器数量: %d\n", MANAGER_COUNT);
    
    for (int i = 0; i < MANAGER_COUNT; i++) 
	{
        FlexObserverManager* manager = &g_managers[i];
        printf("[%d] '%s': %d/%d 观察者\n", 
               i, manager->name, manager->observer_count, MAX_OBSERVERS_PER_MANAGER);
        
        // 打印观察者详情
        for (int j = 0; j < manager->observer_count; j++) 
		{
            printf("    - 观察者[%d]: %p\n", j, manager->callbacks[j]);
        }
    }
    printf("=============================\n\n");
}

// 打印指定管理器详情（高效版本）
void observer_eff_print_manager(ManagerID id) {
    if (id >= MANAGER_COUNT) {
        printf("错误: 无效的管理器ID %d\n", id);
        return;
    }
    
    FlexObserverManager* manager = &g_managers[id];
    printf("\n=== 高效版本 - 管理器 [%d] '%s' 详情 ===\n", id, manager->name);
    printf("观察者数量: %d/%d\n", manager->observer_count, MAX_OBSERVERS_PER_MANAGER);
    
    for (int i = 0; i < manager->observer_count; i++) {
        printf("观察者[%d]: %p\n", i, manager->callbacks[i]);
    }
    printf("===================================\n\n");
}

// 获取观察者数量（高效版本）
uint8_t observer_eff_get_observer_count(ManagerID id) {
    if (id >= MANAGER_COUNT) {
        return 0;
    }
    return g_managers[id].observer_count;
}


REGISTER_CMD(M, observer_eff_print_all,desc)
/*-------------------------------------------------------------------*/
INIT_ENV_EXPORT(observer_eff_init);
