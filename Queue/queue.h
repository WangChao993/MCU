/**
 * @file queue.h
 * @brief 通用环形队列（FIFO），适用于MCU，支持任意数据类型
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

/**
 * @brief 队列结构体
 * @note 用户需提供静态缓冲区，通过 queue_init 初始化
 */
typedef struct {
    uint8_t *buffer;          // 存储数据的字节缓冲区
    size_t   element_size;    // 每个元素的大小（字节）
    size_t   capacity;        // 队列可容纳的最大元素个数
    size_t   head;            // 头部索引（读取位置）
    size_t   tail;            // 尾部索引（写入位置）
    size_t   count;           // 当前元素个数
} Queue;

/**
 * @brief 初始化队列
 * @param q        队列指针
 * @param buffer   用户提供的缓冲区（至少 element_size * capacity 字节）
 * @param elem_sz  每个元素的大小（可使用 sizeof 获取）
 * @param cap      队列容量（最大元素个数）
 */
static inline void queue_init(Queue *q, void *buffer, size_t elem_sz, size_t cap) {
    q->buffer       = (uint8_t*)buffer;
    q->element_size = elem_sz;
    q->capacity     = cap;
    q->head         = 0;
    q->tail         = 0;
    q->count        = 0;
}

/**
 * @brief 判断队列是否为空
 */
static inline bool queue_is_empty(const Queue *q) {
    return q->count == 0;
}

/**
 * @brief 判断队列是否已满
 */
static inline bool queue_is_full(const Queue *q) {
    return q->count == q->capacity;
}

/**
 * @brief 获取队列中当前的元素个数
 */
static inline size_t queue_size(const Queue *q) {
    return q->count;
}

/**
 * @brief 获取队列容量
 */
static inline size_t queue_capacity(const Queue *q) {
    return q->capacity;
}

/**
 * @brief 入队（拷贝数据到队列内部缓冲区）
 * @param q   队列指针
 * @param data 指向要存储的元素的指针
 * @return true 成功，false 队列已满
 */
static inline bool queue_enqueue(Queue *q, const void *data) {
    if (queue_is_full(q)) {
        return false;
    }

    // 计算尾部位置，拷贝数据
    size_t offset = q->tail * q->element_size;
    memcpy(&q->buffer[offset], data, q->element_size);

    // 更新 tail 和 count
    q->tail = (q->tail + 1) % q->capacity;
    q->count++;
    return true;
}

/**
 * @brief 出队（将队列头部元素拷贝到用户提供的缓冲区并移除）
 * @param q    队列指针
 * @param out  存放出队数据的指针（需保证足够容纳一个元素）
 * @return true 成功，false 队列为空
 */
static inline bool queue_dequeue(Queue *q, void *out) {
    if (queue_is_empty(q)) {
        return false;
    }

    // 计算头部位置，拷贝数据
    size_t offset = q->head * q->element_size;
    memcpy(out, &q->buffer[offset], q->element_size);

    // 更新 head 和 count
    q->head = (q->head + 1) % q->capacity;
    q->count--;
    return true;
}

/**
 * @brief 查看队首元素（不移除）
 * @param q    队列指针
 * @param out  存放队首数据的指针
 * @return true 成功，false 队列为空
 */
static inline bool queue_peek(const Queue *q, void *out) {
    if (queue_is_empty(q)) {
        return false;
    }

    size_t offset = q->head * q->element_size;
    memcpy(out, &q->buffer[offset], q->element_size);
    return true;
}

/**
 * @brief 清空队列（重置 head/tail/count，不擦除缓冲区数据）
 */
static inline void queue_clear(Queue *q) {
    q->head  = 0;
    q->tail  = 0;
    q->count = 0;
}

#endif /* QUEUE_H */
