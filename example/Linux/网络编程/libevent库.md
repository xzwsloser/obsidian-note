# Libevent库
- 优点:
  - 开源,精简,跨平台,专注与网络通信
- 安装源码包的步骤(参考`Readme`文档):
  - `./configure`: 检查安装环境,生成`makefile`
  - `make`: 生成`.o`和可执行文件
  - `sudo make install`: 将必要的资源`cp`到系统指定的目录下
- 最好查看`readme`查看安装方法
- **如果无法连接可以把 `/usr/local/lib` 路径加入到 `/etc/ld.so.conf`中**
- 注意`/usr/local/lib`是用户级的目录,安装的库都会放在这一个目录下,几个库目录的区别: https://blog.csdn.net/chengfenglee/article/details/113964247
- `.a` 表示静态库  `.so` 表示动态库
## Libevent封装的框架思想

- 一般对于一个事件的监听设置方式如下(对于普通事件):

1. **创建 `event_base` (`event_base_new`)**
2. **创建事件: `event`  (`event_new(base , fd , what , cb , arg)`)**
3. **将事件添加到 `base`上 (`event_add(event , timeval)`)**
4. **循环监听事件满足  (`event_base_dispatch(base)`)**
5. **释放 `event_base`  (`event_base_free(base)`)**
- 创建`event_base`可以使用`event_base_new`函数,函数原型和使用方式如下:
```c
// 函数原型:
struct event_base* event_base_new(void);
// 使用方式
struct event_base* event_base = event_base_new();
```
- 释放`event_base`使用`event_base_free`函数,函数原型和使用方法如下:
- 创建事件可以使用 `event_new()`函数,如果需要创建带缓冲区的事件,可以使用`bufferevent_socket_new()`函数,函数原型如下:
```c
struct event* event_new(struct event_base* base , evutil_socket_t fd , short what , event_callback_fn cb , void* arg);
```
- 添加事件可以使用 `event_add`函数,函数原型如下:
```c
int event_add(struct event& ev , const struct timeval* tv);
```
- 循环监听函数可以使用 , `event_base_dispatch`函数,函数原型如下:
```c
int event_base_dispatch(struct event_base* base);
```
### Libevent库例程分析
- 选取`sample`中的`hello-world.c`进行分析
- **注意编译使用 `libevent`库需要使用 `-l event` 连接动态库,此时编译器默认包含头文件的路径中就包含了安装库的路径,所以不用指定包含头文件的路径**
- 头文件在 `/usr/local/include`中,一般来说安装的库或者软件一般都在`/usr/local`目录下,这一个目录下存放着库文件头文件等
- `Libevent`库: 基于事件的异步通信模型(主要依赖于回调机制)
### 框架中不常用的函数
- **启动循环使用: `event_base_dispatch(struct event_base* base)` 函数**(相当于普通的利用`IO`多路复用中的循环)
  - **参数:**
    - **`event_base_new` 函数的返回值**
    - **成功返回 `0` , 失败返回 `-1`**
  - **只有`event_new`中指定了`EV_PERSIST`才可以触发,否则触发一次,就会跳出循环,通常这样: `EV_WRITE | EV_PERSIST)` 或者 `EV_READ|EV_PERSIST`**
- 其他循环:
  - 在指定时间之后停止循环: `int event_base_loopexit(struct event_base* base , const struct timeval *tv)`
  - 立刻跳出循环: `int event_base_loopbreak(struct event_base* base)`
- 查看支持那些多路`IO`: `cosnt char** event_get_supported_methods(void)`
- 查看当前使用的多路`IO`: `const char* event_base_get_method(const struct event_base* base)`
- 查看`fork`之后子进程使用的`event_base`: `int event_reinit(struct event_base* base)`使用该函数之后,父创建的`base`才可以在子进程中生效(子进程复制父进程中的`base`,需要调用这一个函数才可以使得子进程中的`base`生效)
- **注意头文件: `<event2/event.h>`**
```c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<event2/event.h>
int main()
{
    // 演示不常用函数
    // 表示创建一个新的 struct_event_base
    struct event_base* base = event_base_new();
    const char** buf = event_get_supported_methods();
    int i = 0;
    while(buf[i] != NULL){
        printf("%s \n" , buf[i]);
        i ++;
    }
    const char* now = event_base_get_method(base);
    printf("%s \n" , now);
}
```
### 创建事件
- 作用: 创建事件
- 函数原型:
```c
struct event* event_new(struct event_base* base , evutil_socket_t fd , short what , event_callback_fn cb , void* arg);
```
- 参数:
  - **`base`: 表示 `struct event_base*` 对象**
  - **`fd`:   表示需要监听事件对应的套接字的文件描述符**
  - **`what`: 表示监听的事件类型,比如 读 写 异常,可以取得的值如下:**
    - **`EV_READ`  一次读事件**
    - **`EV_WRITE`  一次写事件**
    - **`EV_PERSIST`  表示持久化**
    - **`EV_ET`     表示边缘触发**
  - **`event_call_fn cb`: 表示事件发生之后的回调函数(以一旦事件满足监听条件就会调用这一个回调函数)**
    - 回调函数:
```c
typedef void(*event_callback_fn)(evuntil_socket_t fd , short , void*);
```
  - `arg`: 表示回调函数的参数
- 返回值:
  - 成功创建的事件对象
### 事件操作
#### event_add
- 作用: 添加事件到`base`上
- 函数原型:
```c
int event_add(struct event* ev , const struct timeval* tv);
```
- 参数:
  - `ev`: `event_new()`函数返回的事件对象
  - `tv`: 为`NULL`,不会超时,意思为: 一直等到事件被触发,回调函数就会被调用(阻塞),如果为非`0`,等待期间事件没有被触发,时间到了,回调函数依然会被调用(定时触发)
#### event_free
- 作用: 释放事件
- 函数原型:
```c
int event_free(struct event* ev);
```
- 返回值:
  - 成功: `0`
  - 失败: `-1`
#### event_del(一般不使用)
- 作用: 将事件从`base`上面拿下来
- 函数原型:
```c
int event_del(struct event* ev);
```
- `ev`: `event_new()` 函数返回的事件
#### 使用fifo的读写
- 使用`Libevent`完成`fifo`的读写:
- 注意事件的含义,比如`EV_READ`以及`epoll`中描述事件的符号都是表示文件可以怎么样,比如文件中有数据就表示可以读,文件有写的权限就表示可以写
- 比如利用`libevent`库监听`fifo`的读事件:
```c
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<event2/event.h>
#include <sys/types.h>
#include<fcntl.h>
#include <sys/stat.h>
#include<ctype.h>
#define FIFO_NAME "myfifo"
void sys_exit(const char* msg)
{
    perror(msg);
    exit(1);
}

void read_from_fifo(int fd , short whar , void* arg)
{
    char buf[BUFSIZ];
    int ret = read(fd , buf , sizeof(buf));
    if(ret == 0){
        perror("the fifo is closed !");
    } else if(ret == -1){
        perror("read from fifo failed !");
    } else if(ret > 0){
        for(int j = 0 ; j < ret ; j ++){
            buf[j] = toupper(buf[j]);
        }
        write(STDOUT_FILENO , buf , ret);
    }
}
int main()
{
    // 1. 首先创建有名管道
    unlink(FIFO_NAME);
    mkfifo(FIFO_NAME , 0644);
    // 2. 打开管道,获取文件描述符
    int fd = open(FIFO_NAME , O_RDONLY | O_NONBLOCK);
    if(fd == -1)  sys_exit("open the file failed !!!");
    // 3. 创建 event_base 对象
    struct event_base* base = event_base_new();
    // 4. 创建事件对象
    struct event* event = event_new(base , fd , EV_READ | EV_PERSIST , read_from_fifo , NULL);
    // 5. 添加事件到 base上
    event_add(event , NULL);  // 表示阻塞
    // 6. 启动事件循环
    event_base_dispatch(base);  // 底层调用 epoll 执行事件循环
    // 释放资源
    event_free(event);
    event_base_free(base);
    close(fd);
}
```
- 利用`libevent`库监听`fifo`的写事件:
```c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<event2/event.h>
#include<fcntl.h>
#define FIFO_NAME "myfifo"
char buf[BUFSIZ];
void sys_exit(const char* msg)
{
    perror(msg);
    exit(1);
}

void write_to_fifo(int fd , short what , void* arg)
{
    // 写入到缓冲区中
    scanf("%s" , buf);
    write(fd , buf , strlen(buf));
    memset(buf , '\0' , sizeof(buf));
}
int main()
{
    // 1. 首先打开
    int fd = open(FIFO_NAME , O_WRONLY);
    if(fd == -1){
        sys_exit("open the file failed !");
    }
    // 2. 创建 event_base对象
    struct event_base* base = event_base_new();
    // 3. 创建事件对象
    struct event* ev = event_new(base , fd , EV_WRITE | EV_PERSIST , write_to_fifo , NULL);
    // 4. 插入事件
    event_add(ev , NULL);
    // 5. 事件循环
    event_base_dispatch(base);
    // 6. 释放资源
    event_free(ev);
    event_base_free(base);
    close(fd);
}
```
- 注意由于`libevent`库都是基于`epoll` + `ET`模式 + `void* ptr`实现的`epoll`反应堆,所以读取文件必须使用非阻塞模式(前面有提到)
- 注意管道中的数据只是可以单向流动,半全双工
- **梳理脉络顺序:**
  - **首先获取文件描述符号**
  - **创建`event_base`对象: `event_base_new`方法**
  - **创建事件对象: `event_new(base , fd , what , cb , arg)`**
  - **插入事件: `event_add(event , NULL)`**
  - **事件循环: `event_base_dispatch(base)`**
  - **最后进行资源的释放: `event_base_free` , `event_free` , `close`**
### 事件的未决和非未决
- **未决: 有资格被处理,但是还没有被处理**
- **非未决: 没有资格处理**
- 事件状态的转移:
![alt text](<../img/image copy 11.png>)
## bufferevent
- 用于套接字通信,可以用于网络,带有缓冲区
### bufferevent特性
- 头文件: `<event2/bufferevent.h>`
- 原理: `bufferevent`有两个缓冲区: 也是队列实现,读走没,先进先出
  - **读: 有数据 --> 读回调函数被调用 --> 使用`bufferevent_read()` --> 读数据**  **--> 处理核心业务逻辑 --> 可以选择写回去**
  - **写: 使用`bufferevent_write()` --> 向写缓冲中写数据 --> 该缓冲区中有数据自动写出 --> 写完,回调函数被调用(作用很小)**(注意不是在写的回调函数中调用这一个方法)
- 注意缓冲区的作用: https://aceld.gitbooks.io/libevent/content/7_bufferevent.html
- 对于写缓冲: 当有数据需要写入的时候,首先把数据写入到输入缓冲区,到了一定的时候就会刷新
- 对于读缓冲: 当需要从事件中读取数据的时候,首先从读缓冲中读取数据(有一个数据被放入读缓冲的时机)
### bufferevent的相关操作
- **使用`bufferevent`监听事件的读写行为的方式如下(基本和`event`一样,基本上没有用):**
  1. **获取文件描述符**
  2. **创建`event_base`对象**
  3. **创建`bufferevent`对象**
  4. **将`bufferevent`对象挂载到`event_base`中使用 `event_add`**
  5. **启动事件循环监听**
  6. **释放资源**
#### bufferevent_socket_new函数
- 作用: 创建`bufferevent`对象(**`fd`可以使用一般方式获取或者可以通过`bufferevent_new_bind`函数中回调函数的参数获取)**
- 函数原型:
```c
struct bufferevent* bufferevent_socket_new(struct event_base* base , evutil_socket_t fd , enum bufferevent_options options);
```
- 函数参数:
  - `base`: 表示`event_base`对象
  - `fd`: 跟`fd`绑定的文件描述符,类比(`event_new()`)
  - **`options`: `BEV_OPT_CLOSE_ON_FREE`只用这一个就可以了(释放`bufferevent`的时候关闭底层传输接端口,这将要关闭底层套接字,释放底层的`bufferevent`等)**
- 返回值: 返回一个成功创建的`bufferevent`事件对象,包含文件描述符
#### bufferevent_free函数
- 作用: 释放`bufferevent`对象
- 函数原型:
```c
void bufferevent_free(bufferevent* ev);
```
- 参数: 表示 `event` 对象
- 返回值: 无
#### 给bufferevent对象设置回调
- `libevent`库中都是通过回调函数的方法设置回调,对比`event`
- ##### bufferevent_setcb函数
- 作用: 给`bufferevent`对象设置回调函数
- 注意 `bufferevent_socket_new`函数用于初始化`bufferevent`并且绑定文件描述符,同时结合`buffer_setcb`设置回调函数,这两个函数共同完成`event_new`函数的作用
- 函数原型:
```c
void bufferevent_setcb(struct bufferevent* bufev , bufferevent_data_cb readcb , bufferevent_data_cb writecb , bufferevent_event_cb eventcb , void* cbarg);
```
- 参数:
  - `bufev`: 表示`bufferevent`对象
  - `readcb`: 表示设置`bufferevent`读缓冲对应回调函数(`read_cb`(`bufferevent_read()`读取数据))
  - `writecb`: 设置`bufferevent`写缓冲,对应回调`write_cb()` -- 作用就是给调用者发送成功写通知,可以设置为`NULL`
  - `eventcb`: 表示事件回调,如果不想要拿到状态或者异常,也可以传递(`NULL`)
  - `cbarg`: 表示回调函数的参数
- `readcb`对应的回调函数:
```c
typedef void(*bufferevent_data_cb)(struct bufferevent* bev , void* ctx);

// 读回调函数中需要调用 bufferevent_read 函数进行书籍的读取
```
- 读取和写入缓冲区的函数:
```c
// 通常在 读回调函数中代替 read()函数
// 表示从缓冲区中读取数据,相当于底层向缓冲区中写入数据,外界进行读取(其实这里就是指的socket中的缓冲区,外界需要读取,那么就需要放数据到读缓冲中)
size_t bufferevent_read(struct bufferevent* bufev , void* data , size_t size);
```
```c
// 需要从缓冲区中拿出数据,所以需要设置数据类型未 const char*,此时需要从写缓冲中拿出数据进行刷新,从数据源中拿出数据所以数据不可以被修改(注意写回调函数表示这一个函数把数据写入到写缓冲区之后,自动把写缓冲区中的数据同步到对方的socket指向的文件中)
int bufferevent_write(struct bufferevent* bufev , const void* data , sizet_t size);
```
```c
typedef void(*bufferevent_event_cb)(struct bufferevent* bev , short events , void* ctx);
```
- `events`: 不同的标志位,代表不同的事件:
  - `EV_EVENT_READING`: 读取操作时发生某事件,具体是那一种事件还需要看其他的标志
  - `BEV_EVENT_WRITING`: 写入操作的时候发生某一个事件,具体是那一种事件请看其他情况
  - `BEV_EVENT_ERROR`: 操作时发生错误,关于错误的更多信息,请调用`EVUTIL_SOCKET_ERROR()`
  - `BEV_EVENT_TIMEOUT`: 发生超时
  - `BEV_EVENT_EOF`: 遇到文件结束指令
  - `BEV_EVENT_CONNECTED`: 请求的连接过程已经完成,实现客户端可用
- 表示遇到异常的时候的处理方式(作用就是捕捉异常)
#### 缓冲区的开启和关闭
- 缓冲区存在的好处: 可以实现半关闭,可以实现三次握手,四次挥手
- **默认: 新建的`bufferevent`写缓冲是`enable`的,读缓冲是`disable`的**
- 可以使用`bufferevent_enable`启动缓冲区,函数原型如下:
```c
// 通常使用这一个函数启动bufferevent的read缓冲
void bufferevent_enable(struct bufferevent* bufev , short events); // 启动缓冲区
```
- 可以使用 `buffer_disable`函数关闭缓冲,函数原型如下:
```c
void bufferevent_disable(struct bufferevent* bufev , short events); // 禁止使用
```
- `events`可取值:
  - `EV_READ`
  - `EV_WRITE`
  - `EV_READ | EV_WRITE`
- 还可以使用`bufferevent_get_enabled`函数获取禁用状态:
```c
// 获取缓冲区的禁用状态,需要使用 & 进行辅助
short bufferevent_get_enabled(struct bufferevent* bufev);
```
### 利用bufferevent实现TCP通信
#### 客户端和服务端通信流程
##### bufferevent_socket_connect函数
- 作用: 类似于`Socket`编程中的`connect`函数,用于连接服务器端
- 函数原型:
```c
int bufferevent_socket_connect(struct bufferevent* bev , struct sockaddr* address , int addrlen);
```
- 参数:
  - `bev`: 表示`bufferevent`函数(利用`buffer_socket_new` 和 `buffer_set_cb`创建)
  - `address`: 相当于服务器端的`IP + port`
  - `addrlen`: 表示地址的长度
##### evconnlistener_new函数
- 作用: 创建一个 `evconnlistener`对象(其实本身没有什么用)
##### evconnlistener_new_bind函数(很重要)
- 作用: 相当于`socket`,`listen`,`bind`,`accept`这几个函数的作用
- 函数原型如下:
```c
struct evconnlistener* evconnlistener_new_bind(
  struct event_base* base,
  evconnlistener_cb cb,
  void* ptr,
  unsigned flags,
  int backlog,
  const struct sockaddr* sa,
  int socklen
)
```
- 参数说明:
  - `base`: 表示`event_base`对象
  - `cb`:   监听回调函数,接受连接之后,用户需要做的操作
  - `flags`: 可以识别的标志:
    - `LEV_OPT_CLOSE_ON_FREE`: 释放`bufferevent`的时候关闭底层传输接口,这将会关闭底层套接字,释放底层`bufferevent`等
    - `LEV_OPT_REUSEABLE`: 端口复用,可以使用`|`
  - `backlog`: 表示最大连接数量
  - `sa`: 表示服务器的`IP + port`
  - `socklen`: 表示`sa`的大小
- 返回值: `eventconnlistener` 对象(表示事件监听器)
- 回调函数类型:
```c
typedef void (*evconnlistener_cb)(struct evconnlistener *listener,
    evutil_socket_t sock, struct sockaddr *addr, int len, void *ptr);
```
- 参数:
  - `listener`: 表示`evconnlistener`对象
  - `sock`:     表示套接字`fd`号
  - `addr`:     表示地址结构
  - `len`:      表示`addr`的大小
  - `ptr`:      表示创建`evconnlistener`是用户传递进入的参数,可以当成函数的参数
- 回调函数不用自己调用,由框架自动调用,其中可以完成读写操作
##### 服务器端TCP通信实现流程
- 步骤分析:
  1. **利用`event_base_new`函数创建`event_base`对象**
  
  2. **创建服务器连接监听器(`evconnlistener_new_bind()`)**
  
  3. **在`evconnlistener_new_bind`绑定的回调函数中处理接受连接之后的事情**
  
  4. **回调函数被调用,说明有一个客户端连接上来了,会得到一个新的`cfd`,用于和客户端进行通信(读,写)**
  
  5. **使用`bufferevent_socket_new`创建一个新的`bufferevent`对象,将`fd`封装到这一个对象中**(回调函数中需要做的事情)
  
  6. **使用`buffer_setcb`设置回调函数**
  
  7. **设置`bufferevent`的读写缓冲区开启或者关闭**
  
  8. **接受发送数据`bufferevent_read()`,`bufferevent_write()`**
  
  9. **启动循环监听**
  
  10. **释放资源**
  
      
  
  11. 服务器端的代码实现(其中`read_cb`和`write_cb`函数是`bufferevent_setcb`中的回调函数,并且`listen_call_back`是`bufferevent_socekt_bind`函数的回调函数,用于监听`listenfd`:(联连接事件)
```c
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<event2/bufferevent.h>
#include<event2/event.h>
#include <event2/listener.h>
#include<sys/socket.h>
#include<ctype.h>
#define SERV_PORT 10086                                             
char buf[BUFSIZ];
void read_cb(struct bufferevent* bev , void* ctx)
{
    // 调用读函数 bufferevent_read 函数,表示从读缓冲中读取数据
    int n = bufferevent_read(bev , buf , sizeof(buf));
    // 开始读取信息
    for(int i = 0 ; i < n ; i ++){
        buf[i] = toupper(buf[i]);
    }
    // 写回去,表示向写缓冲中写出数据,自动发送消息
    bufferevent_write(bev , buf , n);
}

void write_cb(struct bufferevent* bev , void* ctx)
{
    printf("Successfully write message to client !\n");
}
// 设置回调函数
void listen_call_back(struct evconnlistener* listener , evutil_socket_t sock , struct sockaddr* addr , int len , void* ptr)
{
    printf("client comes !!!\n");
    // 利用 sock 绑定读写回调函数
    struct bufferevent* bufferevent = bufferevent_socket_new((struct event_base*)ptr , sock , BEV_OPT_CLOSE_ON_FREE);
    // 进行回调函数的绑定
    // 打开缓冲区
    bufferevent_enable(bufferevent , EV_READ | EV_WRITE);
    bufferevent_setcb(bufferevent , read_cb , write_cb , NULL , NULL);
}



int main()
{
    // 1. 首先创建 event_base 
    struct event_base* base = event_base_new();
    // 2. 利用evconnlistener_new_bind 函数进行数据对象的绑定
    // 2.1 初始化地址结构
    struct sockaddr_in server_addr;
    memset(&server_addr , 0 , sizeof(server_addr));
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERV_PORT);
    struct evconnlistener* listener = evconnlistener_new_bind(base , listen_call_back , base , LEV_OPT_CLOSE_ON_FREE | LEV_OPT_REUSEABLE , 128 , 
    (struct sockaddr*)&server_addr , sizeof(server_addr));
    // 事件循环
    event_base_dispatch(base);
    // 释放资源
    event_base_free(base);
    evconnlistener_free(listener);
}
```
- 还是需要数理流程:
  1. **首先创建`event_base`对象**
  2. **创建`server_addr`对象并且使用`evconnlistener_new_bind`方法进行地址和端口的绑定以及`lfd`回调函数的绑定(注意把`base`当成参数传入,创建套接字的时候需要)**
  3. **回调函数中调用 `buffervent_socket_new` 创建 `bufferevent` 对象**
  4. **调用 `bufferevent_setcb`方法设置读写回调函数**
  5. **利用 `bufferevent_enable`函数使能读写缓冲区**
  6. **读回调函数中处理相关的逻辑,比如利用 `bufferevent_read`读取数据,利用`bufferevent_write`写出数据到写缓冲中,数据自动同步到客户端的`socket`中**
  7. **设置读回调函数(没有什么用处)**
  8. **调用事件循环(`event_base_dispatch`)**
  9. **释放资源**
##### 客户端代码实现
- 代码实现如下:
```c
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<event2/bufferevent.h>
#include<event2/listener.h>
#include<sys/socket.h>
#define SERV_PORT 10086
char buf[BUFSIZ];
void read_cb(struct bufferevent* event , void* ctx)
{
    // 读取数据
    int n = bufferevent_read(event , buf , sizeof(buf));
    write(STDOUT_FILENO , buf , n);
}

void write_cb(struct bufferevent* event , void* ctx)
{
    printf("receive data from server !\n");
}

void read_terminal(evutil_socket_t fd , short what , void* ptr)
{
    int len = read(fd , buf , sizeof(buf));
    bufferevent_write((struct bufferevent*)ptr , buf , len + 1);
}
int main()
{
    // 1. 首先创建 event_base 对象
    struct event_base* base = event_base_new();
    // 2. 利用 bufferevent_socket_new 创建
    // 获取 socket
    int sock = socket(AF_INET , SOCK_STREAM , 0);
    struct bufferevent* bev = bufferevent_socket_new(base , sock , BEV_OPT_CLOSE_ON_FREE);
    // 3. 利用 bufferevent_socket_connect 连接服务器
    struct sockaddr_in server_addr;
    memset(&server_addr , 0 , sizeof(server_addr));
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERV_PORT);
    bufferevent_socket_connect(bev , (struct sockaddr*)&server_addr , sizeof(server_addr));
    // 4. 利用 bufferevent_setcb 设置回调函数
    bufferevent_enable(bev , EV_READ);
    bufferevent_setcb(bev , read_cb , write_cb , NULL , NULL);
    // 设置另外的回调函数
    struct event* ev = event_new(base , STDIN_FILENO , EV_READ | EV_PERSIST , read_terminal , bev);
    event_add(ev , NULL);
    // 设置事件循环
    event_base_dispatch(base);
    // 释放数据
    event_base_free(base);
    event_free(ev);
    close(sock);
}
```
- 注意: 不要再读回调中首先调用 `bufferevent_write`函数,否则容易引发报错
- 梳理流程:
1. **首先利用`event_base_new`创建`event_base`**
2. **利用`socket`获取`fd`,利用`bufferevent_socket_new`获取`bufferevent`对象**
3. **利用`bufferevent_socket_connect`连接客户端(底层应该做了事件绑定)**
4. **利用 `bufferevent_setcb`设置各种回调函数**
5. **利用`event_base_dispatch`进行事件回调**
6. **最后释放各种资源**

- **总结一下: `libevent`库基于事件驱动,可以对于各种事件的各种行为进行监听,对于网络套接字的读写事件,可以监听普通事件,所以对于各种事件使用`libevent`库处理十分方便**
- 比如可以使用监听标准输入输出读写的方式来进行监听读写事件
