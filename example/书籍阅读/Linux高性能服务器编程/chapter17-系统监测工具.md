> 各种网络相关的工具

1. `tcpdump`抓包工具,可以参考 [[chapter1-TCP IP 协议族]] 注意使用这一个命令的格式
2. `lsof`: 列出当前系统打开的文件描述符工具,常用命令如下:
- `-i` 显示 `socket` 文件描述符号,选项的使用方法:
```shell
$ lsof -i [46] [protocol][@hostname|ipaddr][:service|post]
```
- `-u`: 显示用户启动的所有进程打开的所有文件描述符
- `-c`: 显示指定的命令打开的所有文件描述符
- `-p`: 显示指定进程打开的所有文件描述符(可以用于监听进程打开的文件描述符号)
- `-t`: 显示打开了目标文件描述符的进程的`PID`
- 一般用于插件监听某一个端口的进程,或者检测打开某一个个文件的进程:
```shell
╰─$ lsof -i :10086
COMMAND     PID  USER   FD   TYPE DEVICE SIZE/OFF NODE NAME
epoll_ser 19596 loser    3u  IPv4  98693      0t0  TCP *:10086 (LISTEN)
```
3. `nc`: 可以充当服务器或者客户端
- `-i` 指定数据包传送的时间间隔
- `-l`: 以服务器的方式运行,指定监听的端口使用 `-p` 端口
- `-p`: 指定端口
- `-s`: 设置本地主机发送处的数据包的`IP`地址
- `-C`: 将`\r\n`作为结束符
- `-u`: 使用`UDP`协议
- `-w`: 没有检测输入就会退出
- `-X`: 指定代理方式
- `-x`: 指定代理服务器的`IP`和端口号
- `-z`: 扫描目标服务某一个端口是否开启
4. `strace`: 跟踪系统调用和信号,常用选项如下:
- `-c`: 统计每一个系统调用的执行时间,执行次数和出错次数
- `-f`: 跟踪由`fork`调用生成的子进程
- `-t`: 在输出的每一行加上时间信息
- `-e`: 指定表达时,比如 `-e = signal`就是跟踪信号的系统调用
显示如下:
```shell
strace: Process 22035 attached
restart_syscall(<... resuming interrupted read ...>) = ? ERESTART_RESTARTBLOCK (Interrupted by signal)
--- SIGINT {si_signo=SIGINT, si_code=SI_KERNEL} ---
+++ killed by SIGINT +++
```
5. `netstat`命令: 打印本地网卡接口的全部连接以及状态,路由表信息网卡信息等,选项如下:
- `-n`: 使用`IP`地址标识主机
- `-a`: 显示结果中包含监听`socket`
- `t`: 仅仅显示`tcp`连接
- `-r`: 显示路由信息
- `-i`: 显示网卡接口的数据流量
- `-p`: 显示`socket`所属的进程的`PID`和名字
输出信息如下:
```shell
Proto Recv-Q Send-Q Local Address           Foreign Address         State      
tcp        0      0 127.0.0.1:2017          0.0.0.0:*               LISTEN     
tcp        0      0 127.0.0.1:631           0.0.0.0:*               LISTEN 
```
6. `vmstat`: 输出各种资源的使用情况比如进程信息,内存使用,`CPU`使用率等小信息以及`IO`使用情况,具体选项如下:
- `-f` 显示系统启动以来执行的`fork`次数
- `-s` 显示内存相关的统计信息以及多种系统活动的数量
- `-d` 显示磁盘相关的统计信息
- `-p` 显示磁盘分区的统计信息
- `-S` 指定单位
- `delay` 采用时间间隔
- `count` 统计次数
显示信息如下:
```shell
procs -----------memory---------- ---swap-- -----io---- -system-- -------cpu-------
 r  b 交换 空闲 缓冲 缓存   si   so    bi    bo   in   cs us sy id wa st gu
 1  1      0 21983280 274416 7508224    0    0   534   323 2481    1  2  0 98  0  0  0
 0  0      0 22019692 274448 7485988    0    0     0    86  975 1862  1  0 99  0  0  0
 1  0      0 22034664 274464 7479256    0    0     0    31  816 1298  1  0 99  0  0  0
```
7. `ifstat`: 网络流量检测工具,常用选项包含:
- `-a` 检测系统的所有网卡接口
- `-i` 指定网卡接口
- `-t` 输出信息加上时间戳
- `-b`: 使用`Kbit/s`为单位
- `delay`: 采样时间间隔
- `count`: 采用次数
显示信息如下:
```shell
        lo              wlp0s20f3        br-1fd1af8b9846         docker0      
 KB/s in  KB/s out   KB/s in  KB/s out   KB/s in  KB/s out   KB/s in  KB/s out
    6.25      6.25      0.00      0.00      0.00      0.00      0.00      0.00
    6.24      6.24      0.00      0.14      0.00      0.00      0.00      0.00
    6.25      6.25      0.06      0.19      0.00      0.00      0.00      0.00
    6.24      6.24      7.26      1.27      0.00      0.00      0.00      0.00
    6.24      6.24      0.28      0.37      0.00      0.00      0.00      0.00
    6.25      6.25      0.00      0.11      0.00      0.00      0.00      0.00
    6.35      6.35      0.00      0.19      0.00      0.00      0.00      0.00
    6.24      6.24      0.06      0.24      0.00      0.00      0.00      0.00
    6.24      6.24      0.04      0.09      0.00      0.00      0.00      0.00
    6.24      6.24      0.00      0.09      0.00      0.00      0.00      0.00
    6.25      6.25      0.00      0.20      0.00      0.00      0.00      0.00
```
8. `mpstat`: 监视多处理器系统上每一个`CPU`调用情况,使用格式如下:
```shell
$ mpstat [-P {ALL}] [interval] [count]
```
- `-P`可以指定监听的`CPU`编号,输出信息如下:
```shell
22时08分42秒  CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
22时08分45秒  all    0.57    0.00    0.10    0.02    0.00    0.00    0.00    0.00    0.00   99.32
22时08分45秒    0    0.33    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00   99.67
22时08分45秒    1    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00
```
其中只需要关心:
- `%usr`: 用户空间运行时间占比
- `%sys`: 运行在内核空间时间占比(不包含中断)
- `%idle`: 系统空闲时间占`CPU`运行时间 