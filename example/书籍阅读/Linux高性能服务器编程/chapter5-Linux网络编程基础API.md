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
6. 可以使用如下函数来通过套接字来获取到绑定的地址结构体相关的信息(下面的参数都是传入传出参数):
```c
#include<sys/socket.h>
int getsockname(int sockfd , struct sockaddr* address , socklen_t* address_len);

int getsockname(int sockfd , struct sockaddr* address , socklen_t* address_len);
```
7. 可以利用如下两个函数来修改 `socket`相关的选项:
```c
int getsockopt(int sockfd, int level, int optname,
                      void optval[restrict *.optlen],
                      socklen_t *restrict optlen);
int setsockopt(int sockfd, int level, int optname,
                      const void optval[.optlen],
                      socklen_t optlen);

```
比如可以利用下面一个函数修改`TCP`缓冲区的大小,或者可以修改为允许端口复用,可选选项如下:
![[Pasted image 20241207110724.png]]
比如设置允许端口复用的方法如下:
```c
int setVal = 1;
setsockopt(sockfd , SOL_SOCKET , SO_REUSEADDR , &setVal , sizeof(setVal));
```
8. 网络信息 `API` 种类很多,大多都是基于 `DNS`协议工作的,可以获取到主机名或者服务名(或者对应的端口),需要使用的时候查看
9. `gethostbyname`和`gethostbyaddr` 通过主机名称或者主机地址来获取主机相关的信息(通过结构体 `struct hostent`来获取)
10. `getserverbyname`和`getserverbyport` 通过服务名称或者服务端口获取服务相关的信息,结果存储在结构体: `struct servant`中
11.  `getaddrinfo`通过主机名称或者服务名称来获取到主机或者服务相关的信息,函数原型如下:
```c
int getaddrinfo(const char *restrict node,
                       const char *restrict service,
                       const struct addrinfo *restrict hints,
	                  struct addrinfo **restrict res);
```
返回结果是一个链表,链表中的节点存储这需要的数据:
```c
struct addrinfo {
               int              ai_flags;
               int              ai_family;
               int              ai_socktype;
               int              ai_protocol;
               socklen_t        ai_addrlen;
               struct sockaddr *ai_addr;
               char            *ai_canonname;
               struct addrinfo *ai_next;
};
```
其中`hints`表示提示消息相当于过滤消息
12. `getnameinfo`通过 `socket`地址同时获取到主机名称和服务名称:
```c
int getnameinfo(const struct sockaddr *restrict addr, socklen_t addrlen,
                       char host[_Nullable restrict .hostlen],
                       socklen_t hostlen,
                       char serv[_Nullable restrict .servlen],
                       socklen_t servlen,
                       int flags);

```
