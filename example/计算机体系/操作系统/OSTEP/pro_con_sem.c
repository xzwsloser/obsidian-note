#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include <semaphore.h>
#define MAX_LINE 100
/*********************
 *  使用条件变量来实现消费者生产者模型
 *********************/
typedef struct queue_t {
    int front;  // 指向第一个元素
    int rear;  // 指向最后一个元素的下一个元素
    int array[MAX_LINE];
} queue_t;

queue_t que;
int count = 0;  /* 生产资料 */
sem_t full;   /* 表示产品数量 */
sem_t empty;  /* 空格数量 */
sem_t lock;  /* 互斥锁 */

static void que_init();
static void que_put(int value);
static int que_get();
void* producer_handler(void* arg);
void* consumer_handler(void* arg);
int main() {
    sem_init(&empty , 0 , MAX_LINE);
    sem_init(&full , 0 , 0);
    sem_init(&lock , 0 , 1);
    pthread_t pro[10];
    pthread_t con[5];
    for(int i = 0 ; i < 10 ; i ++) {
        pthread_create(&pro[i] , NULL , producer_handler , (void*)i);
    }

    for(int j = 0 ; j < 5 ; j ++) {
        pthread_create(&con[j] , NULL , consumer_handler , (void*)j);
    }

    for(int i = 0 ; i < 10 ; i ++) {
        pthread_join(pro[i] , NULL);
    }

    for(int j = 0 ; j < 5 ; j ++) {
        pthread_join(con[j] , NULL);
    }
}

static void que_init()
{
    que.front = que.rear = 0;
}

static void que_put(int value)
{
    que.array[que.rear] = value;
    que.rear = (que.rear + 1) % MAX_LINE;
}

static int que_get()
{
    int temp = que.array[que.front];
    que.front = (que.front + 2) % MAX_LINE;
    return temp;
}

void* producer_handler(void* arg)
{
    int index = (int)arg;
    while(1) {
        sem_wait(&empty);
        sem_wait(&lock);
        count ++;
        que_put(count);
        printf("[pro: %d] put %d into the queue!\n" , index , count);
        sem_post(&lock);
        sem_post(&full);
        sleep(2);
    }
}

void* consumer_handler(void* arg)
{
    int index = (int)arg;
    while(1) {
        sem_wait(&full);
        sem_wait(&lock);
        int temp = que_get();
        printf("[con: %d] get %d from the queue!\n" , index , temp);
        sem_post(&lock);
        sem_post(&empty);
        sleep(1);
    }
}