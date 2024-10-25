# Socket编程
## 套接字
- 在通信过程中,套接字都是成对出现的,可以理解为插头和插座的关系,只有两者成对出现的时候,才可以进行通电
- 套接字的通信原理如下:
- 注意只有一个文件描述符号但是有两个缓冲区(对于服务器端的`connfd`和客户端端的`clientfd`都有一个读缓冲,一个写缓冲)
![alt text](../img/image.png)
- 一个文件描述符指向一个套接字(该套接字内部由内核借助两个缓冲区实现),在通信过程中一定时成对出现的
### 网络字节序
- 首先了解以下小端法和大端法: https://blog.csdn.net/qq_41337034/article/details/112818650
- 小端法(`pc`本地存储): 高位存储高地址,低位存储低地址
- 大端法(网络存储): 高为存储低地址,低位存储高地址
- 网络数据流采用大端字节序
- 可以调用如下库函数完成网络字节序和主机字节序的转换:
```c
#include<arpa/inet.h>

uint32_t htonl(uint32_t hostlong);
uint32_t htons(uint32_t hostshort);
uint32_t ntohl(uint32_t netlong);
uint32_t ntohs(uint16_t netshort);
```
- 其中 `h` 表示 `host` , `n` 表示 `network`,`l` 表示 `32`位长整数(`IP`协议),`s` 表示`16`位短整数(`port`)
- 应用场景如下:
  - `htonl`: 本地 -> 网络 (`IP`)
  - `htons`: 本地 -> 网络 (`port`)
  - `ntohl`: 网络 -> 本地 (`IP`)
  - `ntohs`: 网络 -> 本地 (`port`)
- 对于`IP`地址, 点分十进制(`string`) --> `atoi` --> `htonl`
#### IP转换函数
- 利用以下两个函数可以完成点分十进制和网络字节序列的相互转换:
```c
#include<arpa/inet.h>
int inet_pton(int af , const char* src , void* dst);
const char* inet_ntop(int af , const void* src , char* dst , socklen_t size);
```
##### inet_pton函数
- 作用: 完成点分十进制到网络字节序列的转换
- 函数原型如下:
```c
int inet_pton(int af, const char *restrict src, void *restrict dst);
```
- 参数:
  - `af` 指定使用 `ipv4` 还是 `ipv6`,使用两个宏定义指定: `AF_INET` 和 `AF_INET6`
  - `src`: 表示需要传入的 `IP` 地址
  - `dst`: 传出参数,转换之后的网络字节序的 `IP` 地址
- 返回值:
  - 成功: `1`
  - 异常: `0`, 说明 `src` 指向的不是一个有效的 `ip` 地址
  - 失败: `-1` 并且设置 `errorno`
##### inet_ntop函数
- 作用: 把网络字节序列转换为本地字节序列
- 函数原型:
```c
onst char *inet_ntop(int af, const void *restrict src,
                             char dst[restrict .size], socklen_t size)
```
- 参数:
  - `af`指定使用`ipv4`还是`ipv6`
  - `src` 指定网络字节序`IP`地址
  - `dst`(缓冲区): 本地字节序(`string IP`)
  - `size`: 缓冲区大小
- 返回值:
  - 成功: `dst`
  - 失败: 返回 `NULL`
#### sockaddr地址结构
- `sockaddr`地址结构和之后的衍生结构如下:
![alt text](../img/Screenshot_20240830_144159_tv.danmaku.bilibilihd.jpg)
- 但是之前`unix`设计的函数中的参数只可以使用 `sockaddr`(当时没有出现泛型指针),并且之前的`API`不好用,所以可以强制类型转换的方式对于参数进行转换
##### bind函数
- 作用: 绑定`IP + port`
- 函数原型:
```c
       int bind(int sockfd, const struct sockaddr *addr,
                socklen_t addrlen);
```
- 参数:
  - `sockfd`: 套接字的文件描述符
  - `addr`: 表示`sockaddr`地址结构,但是一般都是利用 `sockaddr_in` 强制转换为 `sockaddr`使用
```c
   struct sockaddr_in {
               sa_family_t    sin_family; /* ()(使用那一种类型的 IP 地址)address family: AF_INET */
               in_port_t      sin_port;   /* (表示端口号)port in network byte order */
               struct in_addr sin_addr;   /* (IP地址,32位)internet address */
           };

  /* Internet address */
           struct in_addr {
               uint32_t       s_addr;     /* address in network byte order */
           };
```
  - `addrlen`  表示取得到 `sockaddr`地址结构所占用的字节数量(长度)
- 调用 `bind` 函数的实例如下:
- 特别注意 `sockaddr_in`的初始化方式
- 由于本地的变量存储都是使用小端法,但是网络中的变量存储都是使用的大端法,所以一定需要进行转换,把本地的变量转化为网络传输中可以使用的变量
```c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include <netinet/in.h>

int main()
{
    // 首先准备结构体
    struct sockaddr_in addr;
    // 初始化成员
    addr.sin_family = AF_INET;  // 表示使用 ipv4
    addr.sin_port = htons(3306);  // 注意这一个函数表示把本地的变量转换为网络序列中的变量
    int dst;
    inet_pton(AF_INET , "192.168.59.132" , (void*)&dst);
    addr.sin_addr.s_addr = dst;  // 注意也是一个结构体

    // addr.sin_addr.s_addr 的另外一种初始化方式
    addr.sin_addr.s_addr = htonl(INADDR_ANY); // 这一个宏定义默认取出系统任意有效的 IP 地址,二进制类型   
    // bind(fd , (struct sockaddr_in*)&addr , sizeof(addr))
}
```
### socket模型创建流程
- 注意一个客户端和一个服务端进行通信的时候,会有三个文件描述符
- 通信的大体流程如下:
![alt text](<../img/image copy.png>)
- 具体的细节如下:
![alt text](<../img/image copy 2.png>)
#### socket函数
- 作用: 创建一个 `socket`
- 函数原型如下:
```c
int socket(int domain, int type, int protocol);
```
- 函数参数：
  - `domain`: 表示使用那一种形式(`ipv4` `ipv6`): `AF_INET`,`AF_INET6`,`AF_UNIX`
  - `type`: `SOCK_STREAM`(流式协议,`TCP`) , `SOCK_DGRAM`(报式通信,`UPD`)
  - `protocol`: 和上一个参数配合表示使用那一种协议,如果上面传递流式协议那么这里传递 `0` 表示使用 `TCP`
- 返回值: 成功返回文件描述符(新套接字对应的文件描述符),失败返回`-1`并且设置 `errno`
#### bind函数
- 作用: 给套接字绑定地址结构(`IP` + `port`)
- 函数原型如下:
```c
int bind(int sockfd, const struct sockaddr *addr,
                socklen_t addrlen);
```
- 参数:
  - `sockfd`: 表示需要绑定结构地址的`socket`的文件描述符号 `fd`
  - `sockaddr`: 需要利用 `struct sockaddr_in` 进行强制类型转换(两种方法,参考前面)
  - `addrlen`: 地址结构的大小(`sizeof(addr)`)
- 返回值: 成功返回 `0` , 失败返回 `-1`
#### listen函数
- 作用: 设置同时与服务器建立连接的上限数量(同时进行三次握手的客户端数量)
- 函数原型如下:
```c
int listen(int sockfd, int backlog);
```
- 函数参数:
  - `sockfd`: 表示`socket`的文件描述符号
  - `backlog`: 表示最大的连接上限数量
- 返回值:
  - 成功: `0`
  - 失败: `-1`
#### accept函数
- 作用: 阻塞等待客户端建立连接,成功返回一个与客户端成功连接的 `socket` 文件描述符
- 函数原型:
```c
       int accept(int sockfd, struct sockaddr *_Nullable restrict addr,
                  socklen_t *_Nullable restrict addrlen);
```
- 参数:
  - `sockfd`: 表示套接字的文件描述符
  - `addr`: 传出参数(成功与服务器建立连接哪一个客户端的地址结构(`IP` + `port`))
  - `addrlen`: 传入传出参数, 传入: `addr`的大小,传出: 客户端`addr`的实际大小(比如定义方式: `socket_t socket_client_size = sizeof(addr)`)
- 返回值:
  - **可以和客户端进行通信的文件描述符**
  - 失败返回 `-1` , 设置 `errorno`
#### connect函数
- 作用: 与服务器建立连接,使用现有的 `socket` 建立连接
- 函数原型:
```c
       int connect(int sockfd, const struct sockaddr *addr,
                   socklen_t addrlen);
```
- 参数:
  - `sockfd`: 表示客户端的 `fd`
  - `addr`: 传入参数,表示服务器的地址结构
  - `addrlen`: 表示服务器地址结构的大小
- 如果不使用 `bind` 函数绑定客户端的地址结构,采用"隐式绑定"的方式
#### 客户端服务端实现
- `server`:
  1. `socket()`  创建 `socket`
  2. `bind()`  绑定服务器地址结构
  3. `listen()` 设置监听上限
  4. `accept()` 阻塞监听客户端连接
  5. `read(fd)` 读取 `socket` 获取客户端数据
  6. 业务逻辑操作
  7. `write(fd)`  写数据
  8. `close()` 关闭连接
- `client`:
  1. `socket()` 创建 `socket`
  2. `connect()` 连接服务器
  3. `write()` 写数据到 `socket`
  4. `read()` 读转换之后的数据
  5. 业务逻辑处理
  6. `close()`
#### server实现
- `server`的实现如下:
```c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<ctype.h>
#define SERVER_PORT 10087
void sys_err(const char* msg)
{
    perror(msg);
    exit(1);
}

int main()
{
    // 1. 首先利用 socket() 获取 socket
    int socket_fd = socket(AF_INET , SOCK_STREAM , 0); // 表示采用 tcp
    if(socket_fd == -1){
        sys_err("create a socket failed !!!");
    }
    // 2. 使用 bind 进行绑定
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(SERVER_PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY); // 当然也可以使用 inet_pton 函数
    bind(socket_fd , (struct sockaddr*)&addr , sizeof(addr));
    // 3. 利用 listen 指定最大连接数量
    listen(socket_fd , 128);
    // 4. 利用 accept 进行阻塞并且获取新的 fd
    printf("等待客户端连接 ... \n");
    struct sockaddr_in target_addr;
    socklen_t target_len = sizeof(target_addr);
    int fd = accept(socket_fd , (struct sockaddr*)& target_addr , &target_len);
    if(fd == -1){
        sys_err("accept client failed !!!");
    }
    printf("连接成功 ... \n");
    // 获取客户端的地址和端口号
    // printf("address: %d \n" , ntohsl(target_addr.sin_addr.s_addr));
    // 注意需要使用 inet_ntop
    char client_IP[1024];
    // 注意进行转换
    inet_ntop(AF_INET , (void*)&(target_addr.sin_addr.s_addr) , client_IP , sizeof(client_IP));
    printf("addresss: %s \n" , client_IP);
    printf("port: %d \n" , ntohs(target_addr.sin_port));
    // 5. 开始循环读取写入
    char buf[BUFSIZ];  // 表示 4096
    while(1){
        int n = read(fd , buf , BUFSIZ);
        // 如果读取到信息
        if(n > 0){
            if(strcmp(buf , "exit") == 0){
                close(fd);
                printf("服务器端退出了 ... \n");
                exit(0);
            }
            // 进行转换
            // 进行转换
            for(int i = 0 ; i < n ; i ++){
                buf[i] = toupper(buf[i]);
            }
            // 写回去
            write(fd , buf , n);  
        }
    }
}
```
#### client实现
- `client`实现方式如下:
```c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>
#define CLINET_PORT 10089
#define SERVER_PORT 10087
void sys_err(const char* msg)
{
    perror(msg);
    exit(1);
}
int main()
{
    // 1. 首先获取 socket 
    int ret;
    int socket_fd;
    socket_fd = socket(AF_INET , SOCK_STREAM , 0);
    if(socket_fd == -1){
        sys_err("socket failed !");
    }
    // 2. 可选,绑定 端口号和 IP 地址
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(CLINET_PORT);
    bind(socket_fd , (struct sockaddr*)&addr , sizeof(addr));
    // 3. connect 进行连接
    struct sockaddr_in server_addr;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_family = AF_INET;
    ret = connect(socket_fd , (struct sockaddr*)&server_addr , sizeof(server_addr));
    if(ret == -1){
        sys_err("connect failed !");
    }
    // 建立连接开始循环读取
    char buf[BUFSIZ];
    while(1){
        // 通过重定向的方法进行数据的输入和输出
        scanf("%s" , buf);
        write(socket_fd , buf , strlen(buf));
        // 开始读取结果
        int n = read(socket_fd , buf , sizeof(buf)); 
        if(n > 0){
            write(STDOUT_FILENO , buf , n);
        }
    }
    close(socket_fd);
}
```
- 注意函数 `strlen` 和 `sizeof` 函数的区别,定义字符串首选字符数组格式的
- 可以使用 `nc` 工具模拟客户端和服务器端进行通信
#### TCP通信时序和代码的对应关系
- `TCP`通信时许和代码的对应关系,一定需要注意 `connect` 和 `accept` 函数的返回时机,另外还需要注意 `read(0)`  的时候对因半关闭建立完成(无法接受数据)
![alt text](../img/Screenshot_20240831_095355_tv.danmaku.bilibilihd.jpg)
- 注意利用 `read` 方法读取 `socket` 中的数据是阻塞形式的
#### 错误处理函数的封装
- 可以把所有错误处理封装到一个函数中去,从而时的不用再主程序中检测返回值是否正确
- 错误处理的方式如下:
- 使用前面系统函数名第一个字母变成大小即可跳转 `man` 手册
```c
#include "wrap.h"
void sys_err(const char* msg)
{
    perror(msg);
    exit(1);
}

// socket 函数封装
int Socket(int domain, int type, int protocol)
{
    int fd = socket(domain , type , protocol);
    if(fd == -1){
        sys_err("create socket failed !");
    }
    return fd;
}

// bind 函数封装
int Bind(int sockfd, const struct sockaddr *addr,socklen_t addrlen)
{
    int ret = bind(sockfd , addr , addrlen);
    if(ret == -1){
        sys_err("bind Ip and port failed !");
    }
    return ret;
}
// listen 函数封装
int Listen(int sockfd, int backlog)
{
    int ret = listen(sockfd , backlog);
    if(ret == -1){
        sys_err("bind max num to connect the server failed !");
    }
    return ret;
}
// accept函数封装
int Accept(int sockfd, struct sockaddr* addr,socklen_t* addrlen)
{
    int n;
    while((n = accept(sockfd , addr , addrlen)) < 0){
        if(errno == ECONNABORTED || errno == EINTR){
            // 继续循环
            continue;
        } else {
            sys_err("accept failed !");
        }
    }
    return n;
}
// connect 函数封装
int Connect(int sockfd, const struct sockaddr *addr,socklen_t addrlen)
{
    int n;
    n = connect(sockfd , addr , addrlen);
    if(n == -1){
        sys_err("connect failed !");
    }
    return n;
}
```
- 注意`static`关键字的作用: 限制函数的作用域,只在当前模块里面有用
- 注意注意指针的运用
- 封装 `readn` 和 `readline` 封装思想如下:
```c
// 封装 Readn 函数指定读取 n个字节
ssize_t Readn(int sockfd , void* vptr , size_t n)
{
    char* ptr = vptr;  // 指向 vptr
    size_t nleft = n;  // 剩余的字节数量
    size_t nread;
    while(nleft > 0){
        if((nread = read(sockfd , ptr , nleft)) < 0){
            if(errno == EINTR){
                nread = 0;
            } else {
                return -1;
            }
        } else if(nread == 0){
            // 表示读完了
            break;
        }
        nleft -= nread;
        ptr += nread;  // 进行偏移防止覆盖
    }
    return n - nleft;
}
```
- 关于`static`关键字的介绍: https://blog.csdn.net/xiaozhiwise/article/details/111871556
### 端口复用函数
#### setsockopt函数
- 作用: 可以用于实现端口复用
- 函数原型:
```c
 int setsockopt(int sockfd, int level, int optname,
                      const void optval[.optlen],
                      socklen_t optlen);
```
- 使用方法:
  - `int opt = 1`
  - `setsockopt(sockfd , SOL_SOCKET , SO_REUSEADDR , (void*)&opt , sizeof(opt))`
- 直接使用以上代码就可以进行代码复用
```c
int opt = 1;
    setsockopt(lfd , SOL_SOCKET , SO_REUSEADDR , (void*)&opt , sizeof(opt));
```
