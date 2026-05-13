#include "Ring_message_queue.h"

#include <stdio.h>
#include <stdlib.h>
//
#include "Init/init.h"

// 初始化消息队列
static int initQueue(MessageQueue *queue)
{
    queue->front = 0;
    queue->rear = -1;
    queue->count = 0;
	//
	return 0;
}

// 检查消息队列是否为空
static int isEmpty(MessageQueue *queue)
{
    return (queue->count == 0);
}

// 检查消息队列是否已满
static int isFull(MessageQueue *queue)
{
    return (queue->count == MAX_MESSAGES);
}

// 向消息队列中发送消息
static void sendMessage(MessageQueue *queue, Ring_Message message)
{
    if (!isFull(queue))
    {
        queue->rear = (queue->rear + 1) % MAX_MESSAGES;
        queue->messages[queue->rear] = message;
        queue->count++;
      //  printf("Message sent: ID = %d, data = %d\n", message.id, message.data[0]);
    }
    else
    {
     //   printf("Message queue is full. Cannot send message.\n");
    }
}

// 从消息队列中接收消息
static  Ring_Message receiveMessage(MessageQueue *queue)
{
    Ring_Message emptyMessage = {-1, 0,0};
    if (!isEmpty(queue))
    {
        Ring_Message receivedMessage = queue->messages[queue->front];
        queue->front = (queue->front + 1) % MAX_MESSAGES;
        queue->count--;
        //printf("Message received: ID = %d, data = %d\n", receivedMessage.id, receivedMessage.data[0]);
        return receivedMessage;
    }
    else
    {
       // printf("Message queue is empty. Cannot receive message.\n");
        return emptyMessage;
    }
}


Ring_message Ring_message0=
{
	.init    = initQueue,
	.isEmpty = isEmpty,
	.isFull  = isFull,
	//
	.send    = sendMessage,
	.receive = receiveMessage,
};
//

MessageQueue queue_gui;

int Ring_test_main()
{
    MessageQueue queue;
    Ring_message0.init(&queue);
    // 发送消息到队列中
    Ring_Message msg1 = {1, 960,33};
	Ring_message0.send(&queue, msg1);
	//
	Ring_message0.send(&queue, msg1);
	//
	Ring_Message receivedMsg = Ring_message0.receive(&queue);
	//
	msg1.data[0] = 369;
    Ring_message0.send(&queue, msg1);
    // 接收消息从队列中
     receivedMsg = Ring_message0.receive(&queue);
	printf("data : %d\r\n", receivedMsg.data[0]);
    return 0;
}

int Ring_Message_Queue_init()
{
	Ring_message0.init(&queue_gui); 
	
	return 0;
}
/*-------------------------------------------------------------------*/
INIT_APP_EXPORT(Ring_test_main);
INIT_APP_EXPORT(Ring_Message_Queue_init);
