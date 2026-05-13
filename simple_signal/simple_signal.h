 
// simple_signal.h
#ifndef SIMPLE_SIGNAL_H
#define SIMPLE_SIGNAL_H

#include <stdint.h>
#include <stdbool.h>

// 信号定义（按你的需求，160个信号）
// 用户可以在这里定义自己的信号
typedef enum
{
    // 系统信号
    SIG_SYS_TICK_1MS = 0,
    SIG_SYS_TICK_10MS,
    SIG_SYS_TICK_100MS,
    SIG_SYS_TICK_1S,

	//
	SIG_FLASH_SAVE, //存储信号

	SIG_FLASH_PARAM_SAVE,
	
	SIG_FLASH_SAVE_LATER,
    // 按键信号
    SIG_KEY1_PRESS,
	SIG_KEY2_PRESS,
	SIG_KEY3_PRESS,
	SIG_KEY4_PRESS,
	SIG_KEY5_PRESS,
	SIG_KEY6_PRESS,
	SIG_KEY7_PRESS,
	//
	SIG_KEY1_LONG_PRESS,
	SIG_KEY2_LONG_PRESS,
	SIG_KEY3_LONG_PRESS,
	SIG_KEY4_LONG_PRESS,
	SIG_KEY5_LONG_PRESS,
	SIG_KEY6_LONG_PRESS,
	SIG_KEY7_LONG_PRESS,
    //
    SIG_KEY_UP,
    SIG_KEY_DOWN,
    SIG_KEY_RIGHT,
    SIG_KEY_LEFT,
    SIG_KEY_ENTER,
    SIG_KEY_BACK,
	//
	SIG_KEY_PRESS,
    //
	// 串口信号
	
	
    // 串口信号
    SIG_UART1_RX_READY,
    SIG_UART1_TX_DONE,
	//
    SIG_UART2_RX_READY,
	SIG_UART2_TX_DONE,

    // 网络信号
    SIG_NET_CONNECTED,
    SIG_NET_DISCONNECTED,
    SIG_NET_DATA_RECEIVED,
	// 电流信号校准
	//
	SIG_CALIB_ZERO_CURRENT,
    //
    SIG_UI_UPDATE,  //UI更新信号
	//
	SIG_MENU_TOGGLE_CURSOR,  //菜单光标闪烁
    SIG_MENU_DIR2_REFRESH,   //第二级菜单刷新
	
	SIG_MENU_MODIFY,   // 菜单修改参数
	SIG_MENU_CHANGE,   // 菜单选择参数
	//
	SIG_BACK_MAIN_UI,   // 返回主界面
	
	SIG_LOCK_MAIN_UI,   // 主界面锁
	
	SIG_DEVICE_ON_OFF,   // 主界面锁
	
    
	/*-------------------------------------------------------------------*/
	//报警
	SIG_ALARM,     		//报警
	SIG_ALARM_VOICE,	//报警声音
	SIG_SOS_MODE,		//紧急模式
	//
	SIG_MAIN_UI_REFLASH,//主界面刷新
    //通讯
    SIG_COMM_MODBUS_HOST_OK, //通讯

	//处于调试模式
	SIG_DEBUG_MODE,
 
    // 其他信号...
    // 最多支持 160 个信号 (0-159)

    SIG_MAX_COUNT = 160
} Signal;

// 3. 使用宏简化常用模式
#define PROCESS_SIGNAL(sig, handler) \
    if (signal_get(sig)) { \
        handler(); \
        signal_clear(sig); \
    }

// 只有三个函数！
void signal_set(Signal sig);       // 置位信号
void signal_clear(Signal sig);     // 清除信号
bool signal_get(Signal sig);       // 获取信号状态

// 检查并清除信号（原子操作）
bool signal_check_and_clear(Signal sig);

#endif // SIMPLE_SIGNAL_H
