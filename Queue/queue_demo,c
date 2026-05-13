#include "queue.h"
#include <stdio.h>   // 仅用于示例打印，MCU环境中可去掉

// 示例1：存储 int 类型
void example_int(void) {
    // 静态缓冲区: 容量为 5 的 int 队列
    int buffer[5];
    Queue q;
    queue_init(&q, buffer, sizeof(int), 5);

    int val = 100;
    queue_enqueue(&q, &val);
    queue_enqueue(&q, &(int){200});  // 直接传临时变量地址

    int out;
    queue_dequeue(&q, &out);
    printf("dequeued: %d\n", out);   // 输出 100
}

// 示例2：存储结构体
typedef struct {
    uint8_t id;
    float   temperature;
    char    note[4];
} SensorData;

void example_struct(void) {
    // 静态缓冲区: 容量为 3 的 SensorData 队列
    SensorData buffer[3];
    Queue q;
    queue_init(&q, buffer, sizeof(SensorData), 3);

    SensorData data1 = {1, 23.5f, "A"};
    SensorData data2 = {2, 24.0f, "B"};

    queue_enqueue(&q, &data1);
    queue_enqueue(&q, &data2);

    SensorData out;
    queue_dequeue(&q, &out);
    // 输出：id=1, temp=23.5, note=A
    printf("id=%d, temp=%.1f, note=%s\n", out.id, out.temperature, out.note);
}

// 示例3：在中断中使用（需注意临界段保护）
// 假设 MCU 支持关闭中断的宏（以 ARM Cortex-M 为例）
// #define ENTER_CRITICAL()   __disable_irq()
// #define EXIT_CRITICAL()    __enable_irq()

// 中断安全入队示例
static volatile bool irq_enqueued = false;

bool irq_safe_enqueue(Queue *q, const void *data) {
    bool success;
    // ENTER_CRITICAL();
    success = queue_enqueue(q, data);
    // EXIT_CRITICAL();
    return success;
}
