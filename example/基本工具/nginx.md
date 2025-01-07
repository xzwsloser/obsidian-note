> `Nginx`的使用方式,参考: https://github.com/dunwu/nginx-tutorial
# nginx基本命令
- `Nginx`中的基本指令如下:
```shell
nginx -s stop       快速关闭Nginx，可能不保存相关信息，并迅速终止web服务。
nginx -s quit       平稳关闭Nginx，保存相关信息，有安排的结束web服务。
nginx -s reload     因改变了Nginx相关配置，需要重新加载配置而重载。
nginx -s reopen     重新打开日志文件。
nginx -c filename   为 Nginx 指定一个配置文件，来代替缺省的。
nginx -t            不运行，仅仅测试配置文件。nginx 将检查配置文件的语法的正确性，并尝试打开配置文件中所引用到的文件。
nginx -v            显示 nginx 的版本。
nginx -V            显示 nginx 的版本，编译器版本和配置参数。
```
注意入上的 `reload` 命令可以重新加载配置文件不需要每一次都重启 `nginx`服务器
# nginx实战
## 设置 Http 反向代理
- 反向代理: 把外界的请求转发给内部网络的服务器同时又可以把请求返回给外界
- `conf/nginx.conf`是默认的配置文件,当然也可以在 `conf.d/default.conf`中写一部分内容