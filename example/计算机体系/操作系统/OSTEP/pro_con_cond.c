#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#define MAX_LEN 100   /* 环形队列的最大长度 */
/**********************
 *  利用条件变量实现生产者-消费者模型
 ***********************/
pthread_mutex_t mutex;  /* 需要的互斥锁 */
pthread_cond_t empty;   /* 用于阻塞消费者 */
pthread_cond_t full;    /* 用于阻塞生产者 */
// 定义环形队列
typedef struct queue_t {
    int front; // 指向队列头部
    int rear;  // 执行队列尾部
    int array[MAX_LEN];
} queue_t;

queue_t que;  /* 需要操作的队列 */
int count = 0;  /* 消费者生产数据 */

static void queue_init(queue_t* que);  /* 初始化队列 */
static void queue_put(int value);
static int queue_get();   

void* producer(void* arg);  /* 生产者线程任务 */
void* consumer(void* arg);  /* 消费者线程任务 */
int main() {
    pthread_cond_init(&full , NULL);
    pthread_cond_init(&empty , NULL);
    pthread_mutex_init(&mutex , NULL);
    // 多个消费者多个生产者
    pthread_t pro[4];
    pthread_t con[8];
    for(int i = 0 ; i < 4 ; i ++) {
        pthread_create(&pro[i] , NULL , producer , (void*)i);
    }

    for(int j = 0 ; j < 8 ; j ++) {
        pthread_create(&con[j] , NULL , consumer , (void*)j);
    }

    for(int i = 0 ; i < 4 ; i ++) {
        pthread_join(pro[i] , NULL);
    }

    for(int j = 0 ; j < 8 ; j ++) {
        pthread_join(con[j] , NULL);
    }
}

static void queue_init(queue_t* que)
{
    que -> front = que -> rear = 0;
    // 此时数组使用栈空间
}

static void queue_put(int value)
{
      // front 指向第一个元素前面一个元素
      // rear 指向最后一个元素
      que.rear = (que.rear + 1) % MAX_LEN;
      que.array[que.rear] = value;
}

static int queue_get()
{
    que.front = (que.front + 1) % MAX_LEN;
    return que.array[que.front];  /* 返回之前的一个元素 */
}

void* producer(void* arg)
{
    int index = (int)arg;
    while(1) {
        pthread_mutex_lock(&mutex);
        while(((que.rear + 1) % MAX_LEN) == que.front) {
            pthread_cond_wait(&full , &mutex);  // 阻塞
        }
        count ++;
        queue_put(count);
        printf("[pro: %d]pro put %d into the queue !\n" , index ,count);
        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
}

void* consumer(void* arg)
{
    int index = (int)arg;
    while(1) {
        pthread_mutex_lock(&mutex);
        while(que.rear == que.front) {
            pthread_cond_wait(&empty , &mutex);
        }
        int res = queue_get();
        printf("[con: %d]consumer get %d from the queue!\n" , index , res);
        pthread_cond_signal(&full);
        pthread_mutex_unlock(&mutex);
        sleep(2);
    }
}