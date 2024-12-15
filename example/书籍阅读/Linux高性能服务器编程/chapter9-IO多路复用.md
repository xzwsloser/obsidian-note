> 主要介绍三种`IO`多路复用函数: `select` , `poll` 和 `epoll` 笔记相应的服务器实现方式,终点掌握`IO`多路复用解决的问题,注意`IO`多路复用是一种同时监听多个事件的方法,本章的所有代码我之后会上传到`github`仓库中
1.  `select` 系统调用,函数原型如下:
```c
int select(int nfds, fd_set *_Nullable restrict readfds,
                  fd_set *_Nullable restrict writefds,
                  fd_set *_Nullable restrict exceptfds,
                  struct timeval *_Nullable restrict timeout);
```
解释一下其中的参数:
	- `nfds`: 最大的文件描述符号加上 `1`
	- `readfds`:  表示读取文件描述符号的集合,是一个结构体需要使用特定的函数操作
	- `writefds`: 表示可以写的文件描述符的集合,同上
	- `exceptfds`: 表示异常的文件描述符集合
	- 最后一项: `NULL` -> 阻塞, 否则表示具体的事件单位
	- 返回值: 三个文件描述符集合中准备好的文件描述符的个数

`fd_set` 结构体相关的操作函数如下:
```c
    void FD_CLR(int fd, fd_set *set);
    int  FD_ISSET(int fd, fd_set *set);
    void FD_SET(int fd, fd_set *set);
    void FD_ZERO(fd_set *set);
```
下面解释一下具体的事件就绪行为:
	 - 可读:
		 - 内核接受缓冲区中的字节数量大于最低水位线(可以使用 `setsockopt`)函数设置
		 - `socket`通信的对方关闭
		 - 监听`socket` 上面有新的连接请求
		 - `socket` 上有未处理的错误,此时可以使用 `getsockopt` 函数清除错误
	  - 可写:
		  - 内核发送缓冲区中的可用字节数量大于最大水位线(可以设置)
		  - `socket`的写操作被关闭,对于写操作关闭的 `socket` 执行写操作会触发一个 `SIGPIPE` 信号
		  - `socket` 使用非阻塞 `connect` 连接成功
		  - `socket` 中有没有处理的错误
	 - 异常:
		 - 接受到带外数据
2. `poll`系统调用,函数原型如下:
```c
int poll(struct pollfd *fds, nfds_t nfds, int timeout);
```
参数解释:
	 - `fds`:  表示准备好的文件描述符号数组
	 - `nfds`: 表示总共需要监听的文件描述符个数
	 - `timeout`: 超时事件,如果传入 `-1` 表示阻塞
     - 返回值: 也是准备好的文件描述符号个数
 使用基本和 `select`一样
 3. `epoll`系统调用,`Linux`中独有的系统调用,函数原型(使用如下三个函数完成`epoll`系统调用)如下:
```c
int epoll_create(int size);
int epoll_wait(int epfd, struct epoll_event *events,
                      int maxevents, int timeout);
int epoll_ctl(int epfd, int op, int fd,
                     struct epoll_event *_Nullable event);
```
其中`epoll_event`结构体如下:
```c
struct epoll_event {
           uint32_t      events;  /* Epoll events */
           epoll_data_t  data;    /* User data variable */
};

union epoll_data {
           void     *ptr;
           int       fd;
           uint32_t  u32;
           uint64_t  u64;
};
```
下面解释上面函数的含义:
	- `epoll_create`: 相当于创建内核文件注册表
	- `epoll_wait`:  根据内核注册表中注册的监听事件来监听事件的活动
	- `epoll_ctl`: 设置文件描述符号在监听过程中的属性,类似于 `poll` 中的设置 `fdset`集合的函数
4. `epoll` 中的`LT` 模式和 `ET` 模式:
	- `LT` 模式: 电平触发模式,只要接受区中有数据就会一致触发
	- `ET` 模式: 边沿触发模式,指由接受区中数据从无到有才会触发,这就要求文件描述符号必须是非阻塞的,应为如果设置为阻塞的(就是利用`read`读取数据的时候没有数据就会发生阻塞),这就导致没有数据的时候读取就会卡住,从而陷入死循环(可以使用 `fcntl` 函数设置文件描述符的阻塞属性) , 由于触发次数更少所以效率更高
5. 三种`IO` 多路复用模式之间的对比如下:
![[Pasted image 20241208215859.png]]
6. 多路复用的应用: 总结就是监听各种文件描述符号发生的事件,不仅仅限制于网络套接字,比如:
	 - 非阻塞`connect`的实现(可以参考`P163`面的原理)
	 - 需要监听多路事件的情况
7. 另外一种情况比如监听多路事件的超级服务:
![[Pasted image 20241208220819.png]]



