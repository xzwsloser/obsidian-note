# tar 命令
- 参考文档: https://blog.csdn.net/Ruishine/article/details/134439661
- 一般的用途如下:
```bash
tar -zxvf 压缩文件.xz -C 目标位置 # 表示把文件解压到目标位置
tar -zxvf 压缩文件.xz 解压
```
- 同时可以结合 gzip bzip2 xz等工具使用

# /etc/profile 和 ~/.bashrc 和 /etc/environment 的区别
- 可以参看文章: https://www.cnblogs.com/renyz/p/11351934.html
- 都是环境变量但是作用范围不用,修改之后可以使用 `source Xxx`  是他们生效
# Linux中各种目录的作用
- 参考文档: https://blog.csdn.net/m0_49448331/article/details/121137732
# apt 命令的用法:
- 参考: https://blog.csdn.net/m0_61549984/article/details/138661082
- sudo apt install 安装软件
- sudo apt purge(remove) 删除软件,purge会删除配置文件
- sudo apt list 
- sudo apt search 
- sudo apt install Xxx.deb 还可以安装本地的安装包
