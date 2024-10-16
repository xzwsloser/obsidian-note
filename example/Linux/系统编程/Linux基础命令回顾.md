# Linux基本命令
- 终端: 一系列输入输出设备的总称
- 终端内嵌入了`shell`,可以执行输入的命令
- 可以查看 `/etc/shells` 查看 `shell` , `$SHELL` 就是现在使用的 `shell`解析器
- `shell`中可以使用的快捷键如下:  

|功能|快捷键|含义|
|---|---|---|
|上|`ctrl+p`|`previous`|
|下|`ctrl+n`|`next`|
|左|`ctrl+b`|`backforward`|
|右|`ctrl+f`|`forward`|
|`Del`|`ctrl+d`|`delete`光标之后的|
|`Home`|`ctrl+a`|`the first letter`|
|`End`|`ctrl+e`|`end`|
|`Backspace`|`Backspace`|`delete`光标之前的|
## 类Unix的目录结构
- `Linux`操作系统中一切都是文件
- `Linux`的目录结构如下:
  - `/dev` 存放各种设备相关的文件
  - `/etc` 存放相关的配置文件信息,比如`/etc/passwd`存放着用户的密码和信息
  - `/home` 表示用户目录,进入之后可以看到用户目录
  - `/lib` 表示库目录,使用的所有库都放在这一个 `/lib` 中(比如`C`库等)
  - `/root` 表示 `root`用户的家目录
  - `/bin` 存放着各种命令
  - `/usr` 存放着各种软件资源,安装的各种软件资源都放在 `/usr`中,自己装的软件可以放在 `/usr/local`中
  - `/boot` 存放开机启动程序
## 文件和目录操作
- `~` 表示家目录
- 文件类型(`shell`编程中提到过):
  - `-` 普通文件
  - `d` 目录文件
  - `c` 字符设备文件(按照字节进行读写)
  - `b` 块设备文件(可以随机读写)
  - `l` 软连接
  - `p` 管道
  - `s` 套接字
- `rmdir` 删除空目录(一般使用 `rm -r`)
- `mkdir -p a/b` 表示递归的创建文件夹
- `cp -a dir ..` 表示把`dir`全部拷贝到`..`中,否则就会略过 `dir`,`-a`会把所有的信息(包含权限拷贝过去,甚至时间都会被拷贝过去)
- `cat` 查看文件内容
- `tac` 表示倒置显示,比如可以查看日志文件可以使用这一个
- `more` 表示分割显示(空格翻页,`enter`一行,`q`退出)
- `less` 基本一致,但是无法使用 `ctrl + C` 退出
- `head` 读取头部
- `tail` 读取尾部
- `du` 查看目录大小
- `df` 查看磁盘挂载点和使用情况
- 不会的命令使用 `--help` 查看帮助文档
### 软连接和硬连接
- 创建软连接(相当于快捷方式): `ln -s file file.s`
- 注意此时创建的快捷方式占用的空间大小就是文件名称的大小,实际上访问快捷方式就是访问了关联的文件名称(当成快捷方式看待)
- 为了保证软连接可以任意移动,创建时需要使用绝对路径
- 注意文件权限和软连接的权限(软连接的权限全部开发只是表示软连接本生的读写权限,并且和原始文件无关)
- 硬连接: 注意硬连接和软连接的区别就是硬连接和原始的文件执行同一个数据空间,所以更改任何一个硬连接的内容,原始的内容也会发生改变
- 注意目录不可以创建硬连接
- 硬连接记数:
  - 每创建一个硬连接,硬连接技术都会发生改变,当硬连接技术减少为 `0` 的时候,就会删除文件
- 实现方式: 
  - 各种文件会在一个棵树(节点使用 `Inode` 表示,硬连接都有一个相同的 `Inode`)
  - 删除的时候,只将硬连接记数减少,当记数减少为 `0` 的时候才会完全删除
- 可以使用 `stat` 命令查看`Inode`
### 创建和修改用户组
- `whoami` 查看当前用户
- `chmod [who] [+][-] [mode] 文件名`
  - `a` 表示所有人
  - `u` 表示文件所有者(第一个位置)
  - `o` 表示其他人
  - `g` 表示给第二个位置修改权限
- 文件权限修饰:
  - 首位表示文件类型
  - 之后表示所有者的权限
  - 表示用户组的权限
  - 表示其他人的权限
- 数组设定法:
  - `r` 4
  - `w` 2
  - `x` 1
- 比如设置: `chomod 471 文件`,结果如下:
  - -r--rwx--x
- `chown`命令用户修改文件所有者,当创建一个文件的时候,这一个文件属于用户和文件所有者,所以 `chown`可以修改用户组和用户:
  - `chown 用户名/用户组 文件名`
- 注意修改之后,所有者就会发生改变,所以利用 `chmod`的时候一定需要注意
- `adduser` 表示创建用户:
  - `sudo adduser 用户名`
- `addgroup` 表示添加用户组:
  - `sudo addgroup 用户组`
- `chgrp`表示修饰文件所有的用户组:
  - `chgrp 用户组 文件名`
- 或者直接使用 `chown 用户:用户组 文件`就可以直接设置,创建用户的同时会创建一个同名的用户组
- 删除用户: `deluser`:
  - `deluser 用户`
- 删除用户组: `delgroup`:
  - `delgroup 用户组名`
### find命令
- `find`使用方式:
  - `find 查找目录 [options] 类型(名称)`
- `options`:
  - `-type` 表示文件类型
  - `-name` 表示文件名称
  - `-size` 表示按照文件大小查找
  - `-atime(最近访问时间),-mtime(修改时间),-ctime(修改时间)` 表示按照时间进行修改
- 还可以指定搜索深度(`-maxdepth n`表示最大递归深度)
- 例如:
```shell
# 表示  > 20M  < 50M
$ find ~ -size +20M -size -50M
# 表示一天以内修改了
$ find ~ -ctime 1
# 找到的结果交给某一个命令执行
$ find /usr/ -name "*.tmp" -exec ls -l {}\
# 表示执行某一个命令(交互模式)
$ find /usr/ -name "*.tmp" -ok rm -r {}\
```
- 如果不使用 `-size` 就默认按照块搜索,传统的磁盘的最小计量单位 `512B`,最小的就是 `512B`
- 重点掌握参数,可以使用 `man find`查看帮助文档
- `grep` 以文件内容作为搜索对象: 
```shell
# 表示递归搜索文件夹(按照文件名称搜索)
$ grep -r D 目录名
# 用途搜索指定的进程或者搜索文件名称
$ ps aux | grep bash
# 一般就是结合管道使用
```
- `xargs` 和 `exec` 的区别(都是类似于管道的功能):
  - `xargs` 当搜索结果集的大小比较大的时候,那么就会分片执行(执行效率比较高)
  - `exec` 直接执行所有结果集
```shell
# 表示打印的结果使用 null 作为结果
$ find ./ -maxdepth 1 -type f -print0 | xargs -print0  ls -l
```
- 其实搜索到的结果就是一个集合,可以结合管道结合 `xargs` 命令使用,提高效率
- 当文件名中间有空格的时候,比如文件名为: `abc xyz` 的时候,如果直接使用 `xargs` 就会导致解析成两个文件,所以可以使用 `find` 的 `-print0`参数(表示每一个结果使用 `null`进行分割)
```shell
$ find ./ -size +20k -21k -print0 | xargs -0 ls -l
```
- `sed`会按照行进行拆分,利用`awk`会按照列进行拆分
## 软件的卸载和安装
- `apt` 相当于是 `apt-get` 的子集,并且比`apt`更新,推荐使用 `apt`
- `apt`换源方式: https://blog.csdn.net/weixin_65451201/article/details/135198265
- `sudo apt update` 更新软件库
- `sudo apt remove` 卸载软件
- `sudo apt upgrade` 升级软件包
- `deb`包的安装:
  - `sudo dpkg -i xxx.deb` 安装 `deb`软件包
  - `sudo dpkg -r xxx.deb` 删除`deb`软件包
  - `sudo dpkg -r --purge xxx.deb` 连同配置文件一起删除
  - `sudo dpkg -info xxx.deb` 查看软件包的信息
  - `sudo dpkg -L xxx.deb` 查看文件拷贝详细命令
  - `sudo dpkg -l` 查看系统中已经安装软件报的信息命令
  - `sudo dpkg-reconfigure xxx` 重新配置软件包命令
- 源代码安装:
  - 解压
  - `cd dir`
  - `./configure`
  - `make（编译源码)`
  - `sudo make install(把库和可执行文件安装到系统路径下)`
  - `sudo make distclean(删除和卸载软件)`
- 压缩包安装:
  - 首先解压
  - 之后移动到 `/usr/local`中
  - 之后启动脚本文件即可
## 压缩和解压
- 压缩:
  - `tar -zcvf 需要生成的压缩包 压缩材料`,例如: `tar -zcvf test.tar.gz file1 dir2`
- `gzip`命令用于压缩文件: `gzip file`,但是弊端就是只可以压缩一个文件,不可以压缩多个文件或者文件夹
- `tar -zcvf`中:
  - `z` 表示压缩
  - `c` 表示创建
  - `v` 表示显示压缩过程
  - `f` 表示文件
  - 创建压缩文件
- `bzip2`命令, `bzip2 文件`
- 所以总结一下解压和压缩的命令:
  - `tar -zcvf 目标文件名 文件` 表示使用 `gzip 压缩` 后缀: `.tar.gz`
  - `tar -jcvf 目标文件名 文件` 使用 `bzip2`进行压缩,后缀也是一样
- 解压缩
  - `tar -zxvf test.tar.gz` 表示使用 `gunzip` 解压
  - `tar -jxvf test.tar.gz` 表示使用 `bzip2`解压
- `-C` 表示解压到那一个文件中
- `rar`压缩:
  - `rar a -r newdir dir` 表示递归压缩,默认后缀就是 `.rar`
  - `unrar x Xxx.rar` 解压命令
- `zip`压缩 :
  - 压缩: `zip -r dir.zip dir`
  - 解压: `unzip dir.zip`
- 总结:
  - `linux`中解压工具有`gzip`和`bzip2`,但是他们都只可以压缩单个文件,所以需要使用 `tar -zcvf -jcvf -zxvf -jxvf`代替
  - 同时也可以利用 `rar` 和 `zip`工具进行`linux`下工具的打包
- `cat &`  表示后台运行 `cat`
- `jobs` 可以查看后台的作业
- `fg` 表示切换到前台
- `bg` 表示切换到后台
- `env` 表示查看环境变量
- `passwd 用户名`  表示修改密码
- `ifconfig` 用于查看当前的 `ip` 地址
- `man` 查看帮助手册:
  - 第一章节命令
  - 第二章: C lib库
- `man n 命令` 可以查看某一个命令在某一章的介绍
- `alias` 表示起别名 `l$ alias pg='ps aux | grep bash'`
- `umask 权限` 表示掩码，比如`664 使用 777 减去就是 113`,去掉执行权限之后就是 `002`
-  比如 `umask 522`  得到的掩码就是 `777 - 522 - 111`,创建的权限显示之后就可以得到掩码值
- 创建终端:
  - `ctrl + alt + t` 新建终端
  - `ctrl + shfit + t` 拆分终端
## vim 的基本使用方式
### 三种工作模式
- 命令模式: `i a o I A O s S` 进入文本模式,`:`进入末行模式
- 文本模式 `esc` 进入命令模式
- 末行模式: 可以输入各种命令,按下两次`esc`键两次也可以回到末行模式
- 
- 不用 `vim` 了,用不来  