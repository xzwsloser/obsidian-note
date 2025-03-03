>`Kafka`官方网站: https://kafka.apache.org/

# KafKa 的安装

 `KafKa`使用 `Scale`进行开发,由于 `Scale` 运行在 `JVM` 上面,所以需要 `JDK` 的环境

1. 首先需要到官方网站下载 `Kafka`, 并且解压
2. `Kafka` 的启动,可以使用 `zookeeper` 或者 `KRaft` 启动

- 使用 `Zookeeper`启动,进入到 `kafka/bin` 目录其中就是启动需要的脚本文件,`kafka/config`其中就有 `zookeeper` 的配置文件,启动命令如下:
```shell
# 1. 启动 zookeeper 服务器 zookeeper 默认监听 2181 端口
sudo ./zookeeper-server-start.sh ../config/zookeeper.properties &
# 2. 启动 kafka
sudo ./kafka-server-start.sh ../config/server.properties & 
# 3. 关闭 kafka
sudo ./kafka-server-stop.sh ../config/server.properties
# 4. 关闭 zookeeper
sudo ./zookeeper-server-stop.sh ../config/zookeeper.properties
```
顺便补充一下查看进程和端口的命令:
```shell
# 查看监听的端口和进程
netstat -nlpt
# 查看进程
ps -ef | grep ProcessName
# 查看端口
lsof -i :port
```

