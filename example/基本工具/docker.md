> 记录构建各种容器的命令:

- `nginx`
```shell
sudo docker run -d  --name my-nginx \
-p 8080:80 \
-p 8081:8081 \
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
