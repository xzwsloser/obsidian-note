> 基本上没有用,这里指介绍比较重要的概念和函数

1. `pipe`: 创建匿名管道,用于进程之间通信
2. `dup2`: 函数原型如下:
```c
int dup2(int oldfd, int newfd);
```
作用: 相当于把 `newfd`对应的 `inode`表项复制给 `oldfd`,这样使得使用 `oldfd`的时候就像使用 `newfd`一样了
3. `readv`和 `writev`函数: 并文件描述符号写或者读到分散的内存中,没用
4. `mmap`和 `munmap`作用： 可以将文件映射到程序的内存中,后者可以删除这一种映射,可以用于进程进程之间的通信
```c
void *mmap(void addr[.length], size_t length, int prot, int flags, 
int fd, off_t offset);
int munmap(void addr[.length], size_t length);
```
最安全的做法就是: `mmap(NULL , file_len , PROT_READ | PROT_WRITE , MAP_SHARED , 0)` 即可
5. `sendfile`用于在两个文件描述符之间发送文件,使用零拷贝(也就是直接在内核中进行文件内容的拷贝),类似于的函数还有 `splice`
6. `tee`: 用于在两个管道之间进行内容的拷贝
7. `fcntl`函数: 用于改变或者读取文件的属性,函数原型如下,相对来说比较重要
```c
 #include <fcntl.h>
int fcntl(int fd, int op, ... /* arg */ );
```
其中`fd`表示文件描述符,`op`表示操作类型,之后的表示参数,其中操作类型的种类包含:
![[Pasted image 20241207135712.png]]
![[Pasted image 20241207135726.png]]

比如利用 `fcntl`函数设置文件属性为非阻塞的方式如下:
```c
int setnobloking(int fd) {
	int old_option = fcntl(fd , F_GETFL);
	int new_option = old_option | O_NOBLOCK ;
	fcntl(fd , F_SETFL , new_option);
	return old_option;
}
```
这一个函数相对比较重要
8. 同时另外比较重要的`IO`函数还有:  `stat` , `lseek` , `open`等函数,可以参考之前的笔记
```c
int stat(const char *restrict pathname,
                struct stat *restrict statbuf);

 int open(const char *pathname, int flags, ...
                  /* mode_t mode */ );

off_t lseek(int fd, off_t offset, int whence);
```
