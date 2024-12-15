> 简单复习一下`Linux`中的信号以及信号的捕捉和网络编程中常用的信号
1. 发送信号可以使用`kill`函数,函数原型如下:
```c
int kill(pid_t pid, int sig);
```
其中`pid`的取值和发送目标进程的关系如下:
	- `pid` > 0 发送给 `PID`为 `pid`的进程
	- `pid` = 0 发送给本进程组内其他进程
	- `pid` = -1 发送给除了 `init` 进程之外的其他所有进程,需要有发送权限
	- `pid` < 0  发送给所有的组`ID` = `-pid` 的所有进程
2. 信号处理方式(也就是信号处理函数),信号处理函数的定义如下:
```c
typdef void(*__sighandler_t)(int)
```
除了自定义信号处理函数之外还有几种信号处理函数:
```c
#define SIG_DFL ((__sighandler_t) 0) // 使用信号的默认处理方式
#define SIG_IGN ((__sighandler_t) 1) // 忽略信号
```
3. `Linux`信号,信号的种类很多,介绍一种常用的信号:
	  -  `SIGINT` -> ctrl + C 中断进程
	  - `SIGQUIT` -> ctrl + \ 中断进程
	  - `SIGKILL` -> 终止进程,不可以被捕捉
	  - `SIGUSR1,SIGUSR2` -> 用户自定义信号
	  - `SIGSEGV` -> 段错误,非法访问内存
	  - `SIGPIPE` -> 向读端关闭的管道或者`socket` 中写入数据
	  - `SIGALRM` -> 时钟定时信号
	  - `SIGCHLD` -> 子进程状态发生变化(可用于回收子进程)
	  - `SIGTERM` -> 终止进程
	  - `SIGSTOP` -> 暂停进程,不可以被忽略或者捕捉
4. 中断系统调用: 进程执行阻塞系统调用的时候如何设置了某一个信号的信号捕捉函数并且接收到该信号,那么就会产生中断系统调用,并且对于默认行为为暂停进程的函数也会中断系统调用,并且`errno`被设置为 `EINTR`
5. `signal`函数: 用于设置信号处理函数:
```c
typedef void (*sighandler_t)(int);
sighandler_t signal(int signum, sighandler_t handler);
```
6. `sigaction`函数: 设置信号处理函数并且可以设置其他的行为(比如恢复中断系统调用等)
```c
int sigaction(int signum,
                     const struct sigaction *_Nullable restrict act,
                     struct sigaction *_Nullable restrict oldact);
```
其中`sigaction`结构体如下:
```c
struct sigaction {
               void     (*sa_handler)(int);
               void     (*sa_sigaction)(int, siginfo_t *, void *);
               sigset_t   sa_mask;
               int        sa_flags;
               void     (*sa_restorer)(void);
};
```
其中 `sig_handler`为信号处理方式,`sa_mask`为信号集掩码,可以使用 `sigprocmask`函数设置,`sa_flags`表示信号处理的选项,常见的选项如下:
![[Pasted image 20241215113918.png]]
7. 信号集,信号集可以使用 `sigset_t` 结构体表示,可以理解为一个位图,可以利用如下函数操作 `sigset_t`操作这一个结构体:
```c
int sigemptyset(sigset_t *set);
int sigfillset(sigset_t *set);
int sigaddset(sigset_t *set, int signum);
int sigdelset(sigset_t *set, int signum);
int sigismember(const sigset_t *set, int signum);
```
8. 设置信号掩码,使用 `sigprocmask`函数,函数原型如下:
```c
int sigprocmask(int how, const sigset_t *_Nullable restrict set,
                                  sigset_t *_Nullable restrict oldset);
```
`how`表示设置掩码的类型,`set`表示需要设置的信号集(需要使用上面的函数操作),`oldset`表示传出参数,传出之前的信号集,`how`可选选项如下:
	 - `SIG_BLOCK` -> 设置屏蔽
	 - `SIG_UNBLOCK` -> 非屏蔽
	 - `SIG_SETMASK` -> 直接设置
9. 被挂起的信号,当设置信号被屏蔽并且再一次接收到这一个信号的话就会导致信号被挂起,被挂起的信号当屏蔽区取消的时候就会被重新接收到,可以使用如下函数查看被挂起的信号:
```c
int sigpending(sigset_t *set);
```
`set`为传出参数
10. 进程和线程与父进程和父线程的信号处理方式和屏蔽信号集的说明：
	 - 子进程和父进程有相同的屏蔽信号集和信号处理方式,同时子进程可以自定义自己的信号处理方式和屏蔽信号集,未决信号集一样
	 - 子线程和主线程有自己的信号处理方式,但是可以自定义自己的屏蔽信号集,当向该进程发送信号的时候会会遍历所有线程直到找到第一个不阻塞该信号的线程执行信号处理函数(使用`phtread_sigmask`设置阻塞)