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
- `semid`: 信号集的标识符
- `semnum`: 被操作信号量在信号集中的编号
- `op`: 指向的命令,后面的省略参数就是命令的参数
- 省略参数: 一般使用 `union semun` 结构体来只是参数
## 共享内存
> 注意共享内存和`mmap`的区别,共享内存相关的`API`返回创建的共享内存的文件描述符号,`mmap`可以把开辟的内存空间映射到进程的内存空间中,也就是可以直接使用指针来操作内存
1. 创建共享内存:
```c
#include <sys/shm.h>
int shmget(key_t key, size_t size, int shmflg);
```
- `key`标识共享内存的唯一标识符号
- `size`指定共享内存的大小
- `shmflg` 权限
2. 把共享内存关联/取消关联到进程的地址空间中(类似于 `mmap`/`munmap`):
```c
#include <sys/shm.h>
void *shmat(int shmid, const void *_Nullable shmaddr, int shmflg);
int shmdt(const void *shmaddr);
```
- `shmid`: 共享内存的标识符号
- `shmaddr`: 传出参数,关联的指针,最好设置为 `NULL` 让他自己返回
- `shmflg`: 各种标志
3. 控制共享内存的某些属性:
```c
#include <sys/shm.h>
int shmctl(int shmid, int op, struct shmid_ds *buf);
```
- `shmid`: 共享内存的标志
- `op`: 命令
- `buf`: 与设置相关
4. 创建共享内存(类似于创建一个匿名文件):
```c
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
int shm_open(const char *name, int oflag, mode_t mode);
int shm_unlink(const char *name);
```
- 和`open`一样,第二个参数指定权限选项(比如`O_RDONLY等`)
## 消息队列
> 用于进程之间传递消息
1. 创建消息队列:
```c
#include <sys/msg.h>
int msgget(key_t key, int msgflg);
```
- `key`: 消息队列的标识符号
- `msgflg`: 权限
2. 发送消息:
```c
#include <sys/msg.h>
int msgsnd(int msqid, const void msgp[.msgsz], size_t msgsz,
                      int msgflg);
ssize_t msgrcv(int msqid, void msgp[.msgsz], size_t msgsz, long msgtyp,int msgflg);
```
- `msqid`: 消息队列标识符号
- `msgp`: 必须指向特殊的结构体需要体现消息类型和缓冲区大小
- `msgsz`: 消息长度
- `msgflg`: 设置是否阻塞等选项
- 接受消息也是一样的
3. 控制消息队列属性:
```c
#include <sys/msg.h>
int msgctl(int msqid, int op, struct msqid_ds *buf);
```

> 感觉上面三种`IPC`方式太老了不太重要





