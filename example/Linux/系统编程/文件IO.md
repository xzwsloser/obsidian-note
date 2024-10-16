# 文件 IO
## open/close 函数
### open 函数
- `open/close`是系统函数/系统调用
- 作用: 打开或者创建文件
- 头文件: `<fcntl.h>`(存储这宏定义)
- 头文件: `<unistd>`(存储这 `open`函数)
- 函数原型:
```c
int open(const char *pathname, int flags, ...
                  /* mode_t mode */ );

int open(const char *pathname, int flags, ...
                  mode_t mode  );
```
- 参数如下:
  - `pathname` 表示文件路径名称
  - `flag` 打开的状态:
    - `O_RDONLY` `O_WRONLY` `O_RDWR` `O_APPEND` `O_CREATE` `O_EXCL`(是否存在) `O_TRUNC`(截断) `O_NONBLOCK`(没有阻塞)
  - `mode` 表示执行权限(一般和`umask`相关,文件权限=`mode&~umask`)
- 返回值就是一种文件描述符
- 注意出现的三种错误:
```c
#include<stdio.h>
#include<unistd.h>  // 表示 unix 标准库文件 open
#include<fcntl.h>   // 使用 宏定义 需要的头文件
#include<errno.h>   // 表示 errno
int main()
{
    int fd;
    // 如果文件存在的打开并且只读,并且截断成 0 
    // 如果文件不存在创建文件,并且设置权限为 644
    // 创建是的权限就是 mode & ~umask
    fd = open("./file/dict.cp" , O_RDONLY | O_CREAT | O_TRUNC, 0644);  // -rw-r--r--
    // 错误1: 打开不存在的文件
    int fd1 = open("./file/dict.cp11," , O_RDONLY);
    // 错误2: 使用写的方式打开只读文件
    int fd2 = open("./file/dict.cp" , O_WRONLY);
    // 错误3: 使用只写的方式打开一个目录
    int fd3 = open("./file" , O_WRONLY);
    printf("fd1 = %d , errorno = %d \n" , fd1 , errno);
    printf("fd2 = %d , errorno = %d \n",fd2, errno);
    printf("fd3 = %d, errno = %d \n",fd3, errno);
    printf("fd = %d \n" , fd);
    close(fd);
    return 0;
}
```
### close函数
- 作用关闭文件
- 注意多使用 `man` 查看系统函数 `man 2 函数名` 即可查看
- 函数原型:
```c
int close(int fd);
```
- `fd` 表示文件描述符号
- 返回值: `0` 成功 , `-1` 失败
## read/write函数
### read函数
- 作用: 读取文件
- 头文件: `<unistd.h>`
- 函数原型:
```c
ssize_t read(int fd, void buf[.count], size_t count);
```
- 参数:
  - `fd` 表示需要读取的文件描述符
  - `buf[.count]` 表示缓冲区
  - `count` 缓冲区的大小
- 返回值: 返回 `0` 表示读取到了文件末尾,读取成功返回的就是读取到的字节数量,失败就会返回 `-1`
### write函数
- 向文件中写入数据
- 头文件: `<unistd>`
- 函数原型:
```c
ssize_t write(int fd, const void buf[.count], size_t count);
```
- 参数:
  - `fd` 表示文件描述符
  - `buf` 表示缓冲区
  - `count` 表示每一次最多写入的字节数量
- 返回值:
  - 成功返回写入的字节数量
  - 失败返回 `-1`
- 利用 `read` 和 `write` 实现 `cp` 命令的过程如下:
```c
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
int main(int argc , char* argv[])
{
    char buf[1024];  // 注意缓冲区的创建
    int fd1 = open(argv[1] , O_RDONLY);  // 第一个文件
    // printf("fd1 = %d \n" , fd1);
    // 这里阶段表示阶段文件,之后进行写入的操作
    int fd2 = open(argv[2] , O_RDWR | O_CREAT | O_TRUNC , 0644);  // 第二个文件
    int n = 0;
    while((n = read(fd1 , buf , 1024)) != 0){
        // printf("n = %d \n",n);
        write(fd2 , buf , n);  // 表示读取多少写多少
    }
    close(fd1);
    close(fd2);
}
```
- 可以使用 `void perror(const char* error)` 用于打印错误信息
```c
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
int main(int argc , char* argv[])
{
    char buf[1024];  // 注意缓冲区的创建
    int fd1 = open(argv[1] , O_RDONLY);  // 第一个文件
    // printf("fd1 = %d \n" , fd1);
    if(fd1 == -1)
    {
        perror("open argv[1] error!");  // 表示打印错误信息
        exit(1);  // 表示退出
    }
    // 这里阶段表示阶段文件,之后进行写入的操作
    int fd2 = open(argv[2] , O_RDWR | O_CREAT | O_TRUNC , 0644);  // 第二个文件
    if(fd2 == -1)
    {
        perror("opee argv[2] error!");
        exit(1);
    }
    int n = 0;
    while((n = read(fd1 , buf , 1024)) != 0){
        // printf("n = %d \n",n);
        if(n == -1)
        {
            perror("read argv[1] fail!");
            exit(1); // 表示异常退出
        }
        write(fd2 , buf , n);  // 表示读取多少写多少
    }
    close(fd1);
    close(fd2);
}
```
### 系统调用和库函数比较
- 库函数都是通过调用系统调用函数来控制驱动完成功能的
- 库函数 `fputc` 和 `write` 函数的调用关系如下:
![alt text](img/image.png)
- 但是 `fputc` 的速度比 `write` 更加快,这是为什么?
- 可以使用 `strace 可执行程序名称` 查看可执行程序调用的时候进行的系统调用
- 注意 `fputc` 的底层调用 `write` 的时候,每一次设置缓冲区的大小就是 `4096`字节
- 从用户空间切换到内核空间使用的时间比较大
- `fputc`内部有一个缓冲区,缓冲区的大小就是 `4096`字节,当缓冲区的大小为 `4096`的时候,才会完成用户到内核的切换,把数据写入到内核的缓冲区
- 预读入缓输出机制如下:
![alt text](img/Screenshot_20240824_213920_tv.danmaku.bilibilihd.jpg)
- 所以有时候可以使用库函数的地方,还是需要优先使用库函数(库函数积累了多年,所以可能性能比较好)
- 有时候可以根据特殊的场景确定特殊的需求
## 文件描述符
- `PCB` 进程控制块(进程描述符号),本质就是一个结构体,结构体中有一个成员叫做文件描述符表
- 文件描述符其实本质就是键值对映射,可以看成一个文件结构体指针,相当于打开文件描述信息,`open`函数返回的文件描述符号其实就是文件描述符表的下标,之后系统通过下标就可以找到`file`结构体,操作系统隐藏了底层细节
- 文件描述符号:
  - `stdin`  == `0`  `STDIN_FILENO` 
  - `stdout` == `1`  `STDOUT_FILENO`
  - `stderr` == `2`  `STDERR_FILENO`
- 之后打开文件就会随着这下标递增,如果把`0`关了,那么下一次开启得到的文件描述符号就是`0`
- 一个进程最大可以打开的文件就是 `1024`(`0` - `1023`)
- `PCB`进程控制块 包含 文件描述符号表 包含文件描述符号为索引,文件指针为内容的键值对
## 阻塞和非阻塞
- 读常规文件是不会发生阻塞的
- 产生阻塞时间场景:
  - 读取设备文件
  - 读取网络文件
- `/dev/tty` 对应着终端文件
- 如下,读取设备文件的时候,就会发生阻塞
```c
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
int main()
{
    char buf[10];
    int n;
    n = read(STDIN_FILENO,buf,10);
    if(n == -1)
    {
        perror("读取失败");
        exit(1);
    }
    write(STDOUT_FILENO , buf ,n);
    return 0;
}
```
- 注意阻塞就是文件的属性,设备文件默认的属性就是阻塞
- 可以利用 `open` 函数,把文件的属性设置为 `O_NOBLOCK`状态
- 对于非阻塞文件,如果文件中没有数据,就会返回 `-1`(读取失败),但是此时`errno`会被设置为 `EWOULDBLOCK` 
- 注意 如果 `read` 返回 `-1` 并且 `errno`为`EAGIN` 或者 `EWOULDBLOCK`不是说明`read`失败,而是 `read` 在使用非阻塞的方式读取一个设备文件(网络文件),并且文件没有数据
- 所以处理这一种阻塞的方式,可以设置一个超时时间,当超时时间过了的情况下就会相应失败,但是这一种方式仍然不是最优的,最好是可以自己报告阻塞状态,这个就和之后要学习的 `poll` 和 `epoll` 有关
### fcntl函数
- 作用: 改变一个已经打开的文件的访问控制权限
- 头文件: `<fcntl.h>`
- 函数原型:
```c
int fcntl(int fd, int op, ... /* arg */ );
```
- 参数:
  - `fd`: 文件描述符
  - `op`: 表示可选选项,比如:
    - `F_GETFL` 表示获取文件状态
    - `F_SETFL` 表示设置文件状态
- 返回值:
  - 其实返回值就是一个位图,位图是一个整形类型,比如`int`占用`4`个字节,包含`32`个比特位,每一个比特位就可以表示一种文件描述符的状态,所以可以对于得到的`flags`(位图)进行位置运算就可以加上新的权限
- 一个`demo`如下:
```c
int flag = fcntl(STDIN_FILENO,F_GETFL);
flag |= O_NONBLOCK; // 表示加上这一个属性
fcntl(STDIN_FILENO,F_SETFL,flag);
```
- 可以使用 `~` 进行文件属性的减少等操作
### lseek函数
- 作用：控制文件指针的位置
- 函数原型如下:
```c
off_t lseek(int fd, off_t offset, int whence);
```
- 参数:
  - `fd` 表示文件描述符号
  - `offset` 表示偏移量
  - `whence` 表示开始位置:
    - `SEEK_SET` 开始位置
    - `SEEK_CUR` 当前位置
    - `SEEK_END` 结尾位置
- 返回值:
  - 成功返回相对于文件头部的偏移量
  - 否则返回 `-1`
- `lseek`允许超过文件末尾位置,同时文件的读写使用同样一个偏移位置
- 使用`demo`如下:
```cpp
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<cstdlib>  // 注意包含标准 C 库
int main()
{
    int fd1 = open("./file/dict.txt" , O_TRUNC | O_RDWR);
    if(fd1 == -1){
        perror("can not open file!");
        exit(1);
    }
    // 开始写入数据
    char* msg = "hello world\n";
    char ch;
    int n = write(fd1,msg,strlen(msg));
    //设置偏移
    lseek(fd1,0,SEEK_SET); 
    if(n == -1){
        perror("write into file error!");
        exit(1);
    }
    // 开始读取文件
    int res = 0;
    while((res = read(fd1,&ch,1)) != 0)
    {
        if(res == -1)
        {
            perror("read from file error!");
            exit(1);
        }
        // 写入到标准输出中
        int n1 = write(STDOUT_FILENO,&ch,1);
        if(n1 == -1)
        {
            perror("write into stdout fail!");
            exit(1);
        }
    }

}
```
- 应用场景:
  - 文件的读写使用同一个偏移位置
  - 使用`lseek`获取,拓展文件大小位置(`wherence`设置为`SEEK_END`,`offset`设置为`0`)
  - 可以用于拓展文件大小(超出偏移量): 但是注意一定需要有`IO`操作
- 使用情况:
```cpp
#include<stdio.h>
#include<cstdlib>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
int main(int argc , char* argv[])
{
    int fd = open(argv[1] , O_RDWR);
    if(fd == -1)
    {
        perror("open file error !");
        exit(1);
    }
    int len = lseek(fd,0,SEEK_END);
    printf("文件大小为: %d\n" , len);
    // 拓展文件大小
    lseek(fd , 100 , SEEK_END);
    write(fd , "/0" , 1);
    close(fd);
}
```
- 命令:
  - `od -tcx filename` 查看文件十六进制格式
  - `od -tcd filename` 查看文件十进制格式
- 利用`truncate`也可以拓展文件大小
### 传入参数和传出参数
- 传入参数(用于读取):
  - 指针作为函数参数
  - 通常有 `const` 关键字修饰
  - 指针执行有效区域,在函数内部作读操作,在函数内部作读操作
- 传出参数(用于写入):
  - 指针作为函数参数
  - 在函数调用之前,指针指向的空间可以没有意义,但是必须有效
  - 在函数内部,可以作读写操作
  - 函数调用结束之后,充当函数返回值
- 传入传出参数(用于独处写入):
  - 指针作为函数操作
  - 在函数调用之前,指针指向的空间有实际意义
  - 在函数内部,先做读操作,之后做写操作
  - 函数调用结束之后,可以充当函数返回值
- 典型函数就是 `strtok(char* str , const char*delim char ** saveptr)`
## 文件系统
### 文件存储
#### Inode
- 可以根据 `stat 文件名` 命令来查看文件的相关信息,文件属性中包含一个 `inode`
- `inode` 本质就是一个结构体,里面包含存储文件的属性信息(权限,大小,类型,时间,用户,盘符位置...),大多数的`inode`存储在磁盘中,少数的`inode`存储在内存中
- 文件名单独存储和`inode`值存储在`dentry`中
- `dentry`中存储着文件名和`inode`值,`inode`值指向了`inode`结构体,`inode`结构体中存储着文件在磁盘中的地址,可以通过地址取得文件的内容
- 注意当创建硬链接的时候,其实只是创建了新的`dentry`,并且`dentry`中存储的文件名不同,但是`inode`相同
- 总结:
  - 文件存储的方式: 创建一个`dentry`结构体(存储着`inode`和文件名),`inode`指向一个结构体存储着文件的各种属性(包含文件位置),通过这一个结构体就可以找到文件的位置,取出文件的内容
### stat函数
- 作用: 获取文件内容
- 函数原型:
```c
int stat(const char *restrict pathname,
                struct stat *restrict statbuf);
```
- 参数:
  - `pathname` 文件路径名称
  - `statbuf` 一个传入参数,调用函数之后就有意义了,里面的成员存储这文件的各种内容(比如访问权限,所有者等信息)
- 返回值: 
  - `0` 表示成功 `1` 表示失败,可以通过`errorno`确定错误类型
- 演示`demo`如下,还可以使用相应的函数判断文件类型:
- 但是如下`demo`中,如果使用软链接作为参数的时候,那么就会发生`stat`穿透
- 获取文件大小:
  - 文件大小: `st_size`
  - 获取文件类型和权限: `st_mode`
```cpp
#include<stdio.h>
#include<cstdlib>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
int main()
{
    struct stat* res = (struct stat*) malloc (sizeof(struct stat));
    int status = stat("./file/dict.txt" , res);
    if(status == -1)
    {
        perror("get file status failed!");
        exit(1);
    }
    printf("file-size = %d \n" , res->st_size);
    printf("file-mode = %d \n" , res -> st_mode);
    mode_t mode = res -> st_mode;
   switch (mode & S_IFMT) {
           case S_IFBLK:  printf("block device\n");            break; // 块文件
           case S_IFCHR:  printf("character device\n");        break; // 字符文件
           case S_IFDIR:  printf("directory\n");               break; // 目录
           case S_IFIFO:  printf("FIFO/pipe\n");               break; // FIFO
           case S_IFLNK:  printf("symlink\n");                 break; // 软链接
           case S_IFREG:  printf("regular file\n");            break;  // 普通文件
           case S_IFSOCK: printf("socket\n");                  break; // socket
           default:       printf("unknown?\n");                break; // UNKNOWN
           }
    // 注意还可以使用函数
    if(S_ISREG(mode))
    {
        printf("普通文件!!!\n");
    }

    return 0;
}
```
- 注意以上的`demo`中,每一个宏定义的内容如下:
- 注意第一个`S_IFMT` 就是一个掩码类型
- 同时也可以使用宏函数判断文件类型(`S_IFDIR(mode_t mode)`)
```c

#define	__S_IFMT	0170000	/* These bits determine file type.  */

/* File types.  */
#define	__S_IFDIR	0040000	/* Directory.  */
#define	__S_IFCHR	0020000	/* Character device.  */
#define	__S_IFBLK	0060000	/* Block device.  */
#define	__S_IFREG	0100000	/* Regular file.  */
#define	__S_IFIFO	0010000	/* FIFO.  */
#define	__S_IFLNK	0120000	/* Symbolic link.  */
#define	__S_IFSOCK	0140000	/* Socket.  */
````
### lstat函数
- `stat`会穿透符号连接但是`lstat`不会(符号连接就是当传入参数为软链接的时候,就会导致其实判断的就是他执行的文件)
- 函数原型:
```c
 int lstat(const char *restrict pathname,
                struct stat *restrict statbuf);

```
- 返回值和参数和`stat` 一样
- 传出参数`statbuf`相当于传递进入一个地址,把函数的结构带回来,所以函数调用之前不一定需要有意义,还可以使用引用传递
### link函数和UNlink隐式回收
#### link函数
- 可以用于创建硬链接
- 函数原型如下:
```c
int link(const char *oldpath, const char *newpath);
```
#### unlink函数
- 作用: 可以用于删除文件(删除硬链接,使得硬链接参数减少)
- 函数原型:
```c
int unlink(const char *pathname);
```
- `unlink`函数的特征: 清除文件的时候,如果文件硬链接数量减少到 `0` ,没有 `dentry`对应,但是该文件不会立刻被释放,需要等到所有打开该文件的进程关闭该文件,系统才会条时间把该文件释放(只是让该文件具有了可以释放的条件)
- 使用`link`和`unlink`完成文件的移动操作:
```cpp
#include<stdio.h>
#include<cstdlib>
#include<unistd.h>
#include<fcntl.h>
int main(int argc , char** argv)
{
    // 模拟 mv 命令
    int ret1 = link(argv[1] , argv[2]);
    if(ret1 == -1)
    {
        perror("create new file failed !");
        exit(1);
    }
    int ret2 = unlink(argv[1]);
    if(ret2 == -1)
    {
        perror("delete source file failed!");
        exit(1);
    }
    return 0;
}
```
- 隐式回收:
  - 当进程结束运行的时候,所有该进程打开的文件爱你会被关闭,申请的内存空间会被释放,系统这一个特性被成为隐式回收资源
- 演示`demo`,可以写入文件成功:
```cpp
#include<stdio.h>
#include<cstdlib>
#include<unistd.h>
#include<fcntl.h>
#include<cstring>
int main()
{
    int fd,ret;
    char* p1 = "hello temp!\n";
    char* p2 = "error happended!\n";
    fd = open("temp.txt" , O_CREAT | O_RDWR , 0644);
    if(fd == -1)
    {
        perror("open file failed!");
        exit(1);
    }
    // 直接 Unlink文件
    ret = unlink("temp.txt");
    if(ret == -1)
    {
        perror("unlink file failed!\n");
        exit(1);
    }
    // 写入文件
    ret = write(fd , p1 , strlen(p1));
    if(ret == -1)
    {
        perror("write into file failed 1 !!! \n");
        exit(1);
    }
    ret = write(fd , p2 , strlen(p2));
    if(ret == -1)
    {
        perror("write into file failed2 !!! \n");
        exit(1);
    }
    p1[3] = 'c';
    // 关闭文件
    close(fd);
}
```
### 文件目录rwx权限差异
- 可以使用`readlink`命令查看文件本身
- `rename`函数用于重命名
- `getcwd`函数拥有查看当前工作目录
- `chdir`函数用于改变当前进程的工作目录
#### 文件目录的权限
- `linux`中一切都是文件,所以目录也是一个文件
- 使用 `vim 目录名` 就可以看到文件列表
- 目录和文件的 `rwx` 权限:

类型|`r`|`w`|`x`|
---|---|---|---|
文件|文件的内容可以被查看,`cat`,`less`,`more`|内容可以被修改,`vi`,`>`| 可以运行产生一个进程 `./文件名`  
目录|目录可以被浏览`ls`,`tree`|创建,修改删除文件|`cd`
### 目录操作函数
#### opendir函数
- 作用: 打开目录,库函数
- 头文件:
      - `#include <sys/types.h>`
      - `#include <dirent.h>`

- 函数原型:
```c
DIR *opendir(const char *name);
```
#### readir函数
- 作用读取目录,可以获取到文件名称
- 头文件:
  - `#include <dirent.h>`
- 函数原型:
```c
struct dirent *readdir(DIR *dirp);
```
- 返回值：
  - 是一个结构体,可以用于获取其中文件的名称
```c
 struct dirent {
               ino_t          d_ino;       /* Inode number */
               off_t          d_off;       /* Not an offset; see below */
               unsigned short d_reclen;    /* Length of this record */
               unsigned char  d_type;      /* Type of file; not supported
                                              by all filesystem types */
               char           d_name[256]; /* Null-terminated filename */
           };
```
- 利用`opendir`和`readdir`模拟`ls`命令:
```c
#include<stdio.h>
#include<cstdlib>
#include<cstring>
#include<dirent.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
int main(int argc , char** argv)
{
    // 1. 打开文件
    DIR* dir = opendir(argv[1]);
    if(dir == NULL)
    {
        printf("open dir failed !!!\n");
        exit(1);
    }
    // 2. 读取文件内容
    dirent* sdp; // 表示文件内容
    while((sdp = readdir(dir)) != NULL)
    {
        if((sdp -> d_name)[0] == '.')
        {
            continue;
        }

        printf("%s \t" , sdp -> d_name);
    }   
    printf("\n");
}
```
#### 案例: 递归遍历文件
- 要求: 递归遍历文件并且显示文件大小
- 思路:
  - 首先进行判断:
    - 如果是文件之间打印大小和名称
    - 如果是目录,进行递归遍历
- 注意使用 `strcmp` 进行比较,利用`strcat`进行拼接
- `demo`:
```cpp
#include<stdio.h>
#include<cstdlib>
#include<cstring>
#include<sys/types.h>
#include<dirent.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
void travel_dir(const char* pathname)
{
    // 首先获取状态
    struct stat* status = (struct stat*) malloc (sizeof(struct stat));
    int res = stat(pathname , status);
    // printf("%d\n",res);
    if(res == -1)
    {
        perror("get the status of file failed !!!\n");
        exit(1);
    }
    if(!S_ISDIR(status -> st_mode))
    {
        // 不是文件显示大小
        printf("%-20s\t%lu \n" , basename(pathname) , status -> st_size);
        free(status);
        return ;
    } 
    DIR* dir;
    dirent* dirent;
    dir = opendir(pathname);
    if(dir == NULL)
    {
        perror("open file failed!!!");
        exit(1);
    }
    // 开始遍历
    
    while((dirent = readdir(dir)) != NULL){
    // 开始遍历
        printf("%s \n" , dirent -> d_name);
        if((dirent -> d_name)[0] == '.'){
            continue;
        }
        // 注意拼接
        // pathname + / + dirent -> d_name
        char buf[1024];
        sprintf(buf,"%s/%s",pathname,dirent -> d_name);
        travel_dir(buf);
    }
    closedir(dir);
}
int main(int argc , char** argv)
{
    // printf(argv[1]);
    // printf("\n");
    if(argc == 1)
    {
        travel_dir(".");
        return 0;
    }
    travel_dir(argv[1]);
}
```
#### char* 和 const char* 和 char[] 的区别
- `char*` 表示一个字符指针,可以表示字符串,它可以指向任何区域(包含常量区,栈区,堆区等),利用常量字符串初始化的 `char*` 指向常量区,它指向的内容不可以修改,但是指针的指向仍然可以改变
- `const char*` 表示指针指向的内容不可以修改
- `char[]` 表示一个字符数组,其中的内容可以修改,但是指针的指向不可以修改
- `char* const` 表示指针常量不可以修改
```cpp
#include<stdio.h>
#include<cstring>
int main()
{
    char* pstr1 = "hello";
    // pstr1[1] = 'X'  error
    pstr1 = "world";
    printf("%s \n" , pstr1);
    // 最好写成如下形式
    const char* pstr2 = "hello";
    // pstr2[1] = 'X' error
    pstr2 = "fajlsdfajdslf";
    printf("%s \n" , pstr2); // true
    char* const pstr3 = "good";
    // pstr3 = "hello"; // error

}
```
- 可以通过传递函数地址的方式来调用函数,当然`C++`中是使用 `std::function<return_value(...)>`
## 重定向
### dup和dup2函数
#### dup函数
- 作用: 重定向(相当于把输入流中的内容重定向到文件中)
- 函数原型:
```c
int dup(int oldfd);
```
- 参数:
  - `oldfd`: 旧的文件描述符号
- 返回值:
  - 新的文件描述符号
- `demo`如下:
```c
#include<unistd.h>
#include<fcntl.h>
int main(int argc , char* argv[])
{
    int fd = open(argv[1] , O_RDONLY);
    printf("fd = %d \n" , fd);
    int new_fd = dup(fd);
    // 作用就是起到一个保存的作用
    printf("new_id = %d \n" , new_fd);
}
```
#### dup2函数
- 作用改变文件描述符号
- 函数原型:
```c
int dup2(int oldfd, int newfd);
```
- 参数:
  - `oldfd` 表示旧的文件描述符
  - `newfd` 表示新的文件描述符
- 作用就是可以在文件描述符表中的 `oldfd` 的位置拷贝给 `newfd` 那么就会导致 `newfd` 和 `oldfd` 执行同一个文件位置
- `dup2` 会返回新的文件描述符号,并且会让新的文件描述符号和旧的文件描述符号执行同一个文件位置
- 注意执行关系
```cpp
#include<stdio.h>
#include<cstdlib>
#include<unistd.h>
#include<fcntl.h>
int main(int argc , char** argv)
{
    int fd1 = open(argv[1] , O_RDWR);
    int fd2 = open(argv[2] , O_RDWR);
    int fd_ret = dup2(fd1 , fd2);
    printf("fd_ret = %d \n" , fd_ret);
    // 开始进行写操作
    int ret = write(fd2 , "123456" , 7);
    // 这就成为了重定向文件
    if(ret == -1)
    {
        printf("write into file failed...\n");
    }
    dup2(fd1,STDOUT_FILENO);  // 表示重定向
    // 表示把标准输出拷贝给文件
    printf("看到了没有\n");
    return 0;
}
```
#### 利用 fcntl 函数完成 dup2的功能
- 使用方式:
```c
int fcntl(目标文件描述符号 , F_DUPFD , 新的文件描述符)
```
- 第三个参数:
  - 被占用的,返回最小可用的
  - 没有被占用的,返回 `=`该值文件描述符号
- `demo`:
```c
#include<stdio.h>
#include<cstdlib>
#include<unistd.h>
#include<fcntl.h>
int main(int argc , char** argv)
{
    int fd = open(argv[1] , O_RDWR);
    printf("fd = %d \n" , fd);
    int new_fd = fcntl(fd , F_DUPFD , 0); // 0 被占用,fcntl使用文件描述符表中最小的文件描述符号返回
    printf("new_fd = %d \n" , new_fd);
    int new_fd2 = fcntl(fd , F_DUPFD , 7); // 指定 7 的时候没有被占用,就会返回一个 >= 7 的文件描述符号
    printf("new_fd2 = %d \n" , new_fd2);
    write(new_fd2 , "abc" , 3); // 文件描述符号在头部
}
```
