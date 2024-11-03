#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
/**
 *   利用互斥锁和条件变量实现信号量
 */

typedef struct ZSem_t {
    int value;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} zsem_t;

static void zsem_init(zsem_t* sem , int value)
{
    sem -> value = value;
    pthread_mutex_init(&(sem -> mutex) , NULL);
    pthread_cond_init(&(sem -> cond) , NULL);
}

static void zsem_wait(zsem_t* sem)
{
    pthread_mutex_lock(&(sem -> mutex));
    while(sem -> value <= 0) {
        pthread_cond_wait(&(sem -> cond) , &(sem -> mutex));
    }
    sem -> value --;
    pthread_mutex_unlock(&(sem -> mutex));
}

static void zsem_post(zsem_t* sem)
{
    pthread_mutex_lock(&(sem -> mutex));
    sem -> value ++;
    pthread_cond_signal(&(sem -> cond));
    pthread_mutex_unlock(&(sem -> mutex));
}