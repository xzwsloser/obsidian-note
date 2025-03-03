> 记录构建各种容器的命令:

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
- `kafka`:
```shell
sudo docker run  -d --name my-kafka \
-p 9092:9092 \
-e KAFKA_BROKER_ID=0 \
-e KAFKA_ZOOKEEPER_CONNECT=127.0.0.1:2181 \
-e KAFKA_ADVERTISED_LISTENERS=PLAINTEXT://127.0.0.1:9092 \
-e KAFKA_LISTENERS=PLAINTEXT://0.0.0.0:9092 \
-t wurstmeister/kafka
```

