> 介绍 `gdb` 调试视角

# 单可执行文件调试
1. `b n`: 在 `n` 行设置断点
2. `r`: 从头开始
3. `c(continue)`: 命中断点之后继续执行
4. `info breaks`: 显示断点信息
5. `delete n`: 删除对应编号的断点
6. `s`: `step into` 步入
7. `n`: `next` 下一步
8. `si`: 单步执行当前汇编指令
9. `bt`: 查看当前栈帧
10. `frame N`: 切换到第 `N` 个栈帧
11. `up , down`: 向上 or 向下移动栈帧
12. `info frame`: 打印当前栈帧的信息(参数列表,`pc`,保存寄存器等)
13. `info locals`: 打印全部的局部变量
# 多文件调试
1. `info source`: 查看当前代码文件
2. `info sources`: 列出项目中所有的源文件
3. `info functions`: 列出所有函数
4. `info variables`: 列出所有全局变量
5. `break function_name ,break file_name:line_number , break process_data if data_value > 100`: 设置断点
6. `tbreak N`: 只触发一次的断点
7. `list file_name:line_number`: 跳转到指定文件
8. `list function_name`: 跳转到指定函数
9. `set variable_name = new_value`: 修改变量值
10. `tui enable`: 大概 `tui` 模式,同时查看代码和调试信息 `ctrl + x a -> 切换tui界面`
# 调试动态库
1. `sharedlibrary`: 加载符号表
2. `info sharedlibrary`: 列出加载的动态库
3. `break library_function_name`: 在动态库中设置断点
# 多进程程序调试
1. `set follow-fork-mode child`: 设置 `gdb` 附加到子进程上
2. `set follow-fork-mode parent`: 切换会父进程上
3. `catch fork , catch vfork`: `fork` 事件断点
4. `info inferiors`: 查看当前调试的进程 `ID` 
5. `inferiors <num>`: 切换到指定进程
6. `attach <pid>`: 如果子进程和父进程分离,可以利用 `ps` 查看 `pid` 之后附加即可
7. `detach`: 分离进程
8. `break function_name if getpid() == <num>`: 给特定的进程指定断点位置
9. `info signals`: 查看信号设置
# 多线程程序调试
1. `info threads`: 启动多线程支持,并且显示所有线程信息
2. `thread <thread-id>`: 切换到指定的线程
3.  `bt`: 查看当前线程的调用栈
4. `interrupt`: 暂停所有的线程
5. `thread <thread-id> c`: 恢复指定线程
6. `c`: 恢复所有线程
7. `print *mutex`: 查看互斥锁的状态
8. `print *cond`: 查看条件变量的状态
9. `info locals`: 查看局部变量
10. `watch shared_variable`: 检测共享变量的修改
11. `break pthread_create`: 停止在创建线程的位置
## 调试汇编程序
1. `layout split`: 进入布局模式,同时显示源代码和汇编程序
2. `layout src`: 返回源代码窗口
3. `layout asm`: 返回汇编代码窗口
4. `layout regs`: 显示寄存器

## 其他
- `x/[格式][单位] 地址或表达式` , 常见的单位如下:
![[Pasted image 20250512184804.png]]
比如 `x/6i addr` 就可以查看顺序的 `6` 条汇编指令














