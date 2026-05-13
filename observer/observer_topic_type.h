#ifndef _OBSERVER_TOPIC_TYPE_H_
#define _OBSERVER_TOPIC_TYPE_H_

#ifdef __cplusplus
extern "C" {
#endif
	

//主题类型 
#define OBSERVER_TYPE(A) 	OBSERVER_TYPE_##A
enum 
{
	SENSOR_NAME=1,
	SENSOR_UNIT,
	SENSOR_POINT,
	SENSOR_RANGE,
	SENSOR_DATA,
/*-------------------------------------------------------------------*/
	OBSERVER_TYPE(uart1),
	OBSERVER_TYPE(uart2),
	OBSERVER_TYPE(uart3),
	OBSERVER_TYPE(uart4),
	OBSERVER_TYPE(uart_modus_host),
/*-------------------------------------------------------------------*/
	//
	OBSERVER_TYPE(current_1),
	OBSERVER_TYPE(current_2),
	//
	OBSERVER_TYPE(voltage_1),
	OBSERVER_TYPE(voltage_2),
	//
	OBSERVER_TYPE(debug_current),
	OBSERVER_TYPE(debug_voltage),
	//
	OBSERVER_TYPE(debug_org_current),
	OBSERVER_TYPE(debug_org_voltage),
/*-------------------------------------------------------------------*/

/*-------------------------------------------------------------------*/
	DEVICE_ID,	
};

	
#ifdef __cplusplus
}
#endif

#endif
