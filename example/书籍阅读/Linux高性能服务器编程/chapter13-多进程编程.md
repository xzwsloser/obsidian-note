> 主要讲解了进程之间通信的方法以及进程同步的方法也就是信号量,共享内存和消息队列
1. `fork` 创建出来的子进程的特点:
	- 子进程与父进程之间相同的有堆栈指针,寄存器,`.text`代码段
	- 写时复制
	- 原来的文件描述符号打开
	- 信号处理方式不同
2. `exec`系统调用,不会关闭原来程序打开的文件描述符
3. 僵尸进程和孤儿进程:
	- 僵尸进程: 父进程没有退出但是子进程退出,导致子进程的资源没有被释放
	- 孤儿进程: 父进程退出但是子进程没有退出,此时子进程会被 `init` 进程接管,等待子进程执行任务完毕之后回收子进程资源
4. 一般可以使用 `waitpid + SIGCHLD` 来回收子进程,比如:
```c
static void handler_child(int sig) {
	pid_t pid;
	int stat;
	while((pid = waitpid(-1 , &stat , WONHANG)) > 0) {
		/*  处理子进程退出状态 */	
	}
}
```
## 信号量
> 类似于线程同步中的信号量,核心就是`PV`操作
1. 创建信号量集,或者获取到已经存在的信号量:
```c
#include <sys/sem.h>
int semget(key_t key, int nsems, int semflg);
```
- `key`: 信号量的唯一标识符号,通常可以设置为 `IPC_PRIVATE`
- `nsems`: 信号集中信号量的个数,如果只是获取到信号量可以传入 `0`
- `sem_flags`: 标识信号量的权限
- 返回值就是信号量的标识值
2. 对于信号量进行 `PV` 操作:
```c
#include <sys/sem.h>
int semop(int semid, struct sembuf *sops, size_t nsops);

// sembuf 成员
unsigned short sem_num;  /* semaphore number */
short          sem_op;   /* semaphore operation */
short          sem_flg;  /* operation flags */
```
- `semid`: 信号量标识符
- `sops`: 
	- `sem_num`: 信号量的编号
	- `sem_op`: 信号量的操作数
	- `sem_flag`: `SEM_UNDO | SEM_NOWAIT` 都可以设置
- `nspos`: 第二个操作数是一个数组,只是数组中的元素个数
3. 设置信号量参数:
```c
#include <sys/sem.h>
int semctl(int semid, int semnum, int op, ...);
```
