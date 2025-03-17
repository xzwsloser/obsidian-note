> 记录构建各种容器的命令:
# 构建容器
- `nginx`
```shell
sudo docker run -d  --name my-nginx \
-p 8080:8080 \
-v /home/loser/project/Hmdp/Hmdp-java/hmdp/nginx-1.18.0/conf/nginx.conf:/etc/nginx/nginx.conf \
-v /home/loser/project/Hmdp/Hmdp-java/hmdp/nginx-1.18.0/html:/usr/share/nginx/html \
nginx
```
- `mysql`
```shell
sudo docker run --name my-mysql \
-e MYSQL_ROOT_PASSWORD=123456 \ 
-p 3306:3306  \
-d mysql
```
- `redis`
```shell
docker run -d --name my-redis \
  -p 6379:6379 \
  -v /opt/redis/data:/data \
  -v /opt/redis/conf/redis.conf:/etc/redis/redis.conf \
  redis:latest \
  redis-server /etc/redis/redis.conf
```
- `zookeeper`
```shell
sudo docker run -d --name my-zookeeper \
-p 2181:2181 \
-v /etc/localtime:/etc/localtime \
wurstmeister/zookeeper
```
- `kafka`
```shell
sudo docker run -d --name kafka \
-p 9092:9092 \
--link zookeeper:zookeeper \
--env KAFKA_ZOOKEEPER_CONNECT=zookeeper:2181 \
--env KAFKA_ADVERTISED_LISTENERS=PLAINTEXT://localhost:9092 \
--env KAFKA_LISTENERS=PLAINTEXT://0.0.0.0:9092 \
--env KAFKA_OFFSETS_TOPIC_REPLICATION_FACTOR=1 \ wurstmeister/kafka
```
- `mongo`
```shell
sudo docker run -d --name my-mongo \
  -p 27017:27017 \
  -v /home/loser/data/mongo/data:/data/db \
  -e MONGO_INITDB_ROOT_USERNAME=root \
  -e MONGO_INITDB_ROOT_PASSWORD=123456 \
  mongo:latest --auth 
```
## 容器操作
- 删除容器
```shell
sudo docker stop container | xargs sudo docker rm
```
- 利用 `Dockerfile`构建容器
```shell
sudo docker build -t imags:tags . # 指定 Dockerfile 所在的目录
```

## 网络操作
- 创建网络名称并且指定子网掩码:
```shell
$ docker network create --subnet 172.0.0.0/24 net-test
```
- 查看网络段详情:
```shell
$ docker network inspect net-test
```
- 删除网络段
```shell
$ docker network rm net-test
```
- 给容器分配网络段
```shell
$ docker run --name go-net-test --ip 172.0.0.2 --net net-test -d go
```
## 日志操作
```shell
$ docker logs -f container-name
```
## docker-compose
- 启动容器
```shell
sudo docker-compose up -d # 根据配置文件内容开启容器
```
- 停止服务:
```shell
sudo docker-compose down
```
参考: https://juejin.cn/post/7042663735156015140
