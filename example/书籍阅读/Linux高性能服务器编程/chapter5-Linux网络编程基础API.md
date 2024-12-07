> 重要的就那么几个,说几个注意点即可

1. 利用  `socket` 创建网络套接字的时候函数的第二个选项: `type` 可以选择与宏定义:  `SOCK_NONBLOCK` 和 `SOCK_CLOEXEC` 选项进行相与操作,第一个参数表示设置套接字为非阻塞,后面一个选项表示 `fork`子进程的时候关闭父进程中的套接字
2. `listen`函数的作用:可以设置内核监听队列的最大长度,如果长度超过最大队列长度就不会受理新的客户连接,`backlog`参数是指所有处理半连接状态(`SYN_RCVD`)和完全连接状态 (`ESTABLELISHED`)状态的连接
3. `accept`函数的作用只是在内核监听队列中取出参数,并不会检查网络状态
4. `TCP`协议中的数据读写函数如下,第三个选项可以根据自己的需要选择(`P81`)
```c
ssize_t recv(int sockfd, void buf[.len], size_t len, int flags);
ssize_t send(int sockfd, const void buf[.len], size_t len, int flags);
```
5.  `UDP`读写数据使用的函数如下(从下面的函数可见,`UDP`使用数据包的方式传递数据):
```c
   ssize_t recvfrom(int sockfd, void buf[restrict .len], size_t len,
                        int flags,
                        struct sockaddr *_Nullable restrict src_addr,
                        socklen_t *_Nullable restrict addrlen);

ssize_t sendto(int sockfd, const void buf[.len], size_t len, int flags,
                      const struct sockaddr *dest_addr, socklen_t addrlen);

```
另外还用通用的读写函数,但是一些简单的需求可以使用上面的函数就够了
6. 可以使用如下函数来通过套接字来获取到绑定的地址结构体相关的信息:
```c
#include<sys/socket.h>
int getsockname(int sockfd , struct sockaddr* address , socklen_t* address_len);

int getsockname(int sockfd , struct sockaddr* address , socklen_t* address_len);
```
