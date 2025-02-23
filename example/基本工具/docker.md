> 记录构建各种容器的命令:

- `nginx`
```shell
sudo docker run -d \      
--name my-nginx \
-p 8080:80 \
-v /home/loser/project/Hmdp/Hmdp-java/hmdp/nginx-1.18.0/conf/nginx.conf:/etc/nginx/nginx.conf \
-v /home/loser/project/Hmdp/Hmdp-java/hmdp/nginx-1.18.0/html:/usr/share/nginx/html \
nginx
```
