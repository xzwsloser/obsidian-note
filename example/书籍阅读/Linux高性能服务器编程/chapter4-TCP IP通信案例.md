> 第四章介绍 `TCP/IP`通信案例: 也就是访问 `Internent` 上面的 `Web`服务器,但是我认为比较重要的部分就是访问`DNS Server`的过程,这一个过程中各种协议的使用在访问其他的服务器中也是一样的

1. `DNS`访问的过程:
![[Pasted image 20241206193314.png]]
2. `DNS`地址存储在本机的 `/etc/resolv.conf`目录中,如果没有就需要使用`DNS`协议解析主机地址,同时在 `/etc/hosts`目录下存储着主机名和 `IP`地址之间的映射关系,比如本机的 `/etc/hosts`中的内容如下:
```text
127.0.0.1 localhost
127.0.1.1 loser-XiaoXinPro-16-IRH8
# The following lines are desirable for IPv6 capable hosts
::1     ip6-localhost ip6-loopback
fe00::0 ip6-localnet
ff00::0 ip6-mcastprefix
ff02::1 ip6-allnodes
ff02::2 ip6-allrouters
```
