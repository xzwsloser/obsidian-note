> 主要介绍`gdb`调试

1. 利用`gdb`调试多进程:  可以使用 `attach pid` 的方法或者`set follow-fork-mode parent/child`的方法:
- `set follow-fork-mode parent/child` 设置追踪的进程
- `set detach-on-fork on/off`  是否阻塞其他的进程,可以设置为`on`
- `info inferiors` 显示正在运行的进程
- `inferior n` 切换调试进程(好像没有用)
2. 调试多线程:
- `info thread`: 显示线程信息
- `thread n`: 改变调试线程
- `set scheduler-locking on`: 阻塞其他的线程