#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<unistd.h>
#include<ctype.h>
#include<string.h>
#include <arpa/inet.h>
#define SERVER_PORT 10086
int main() {
    // 1. 首先获取到 sockfd
    int sockfd , connfd , count; 
    char buf[1024];  // 读取消息
    sockfd = socket(AF_INET , SOCK_STREAM , 0);
    if(sockfd == -1) {
        fprintf(stderr , "create a sockefd failed !\n");
        exit(1);
    }
    // 2. 绑定IP地址和端口
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(sockfd , (struct sockaddr*)&server_addr , sizeof(server_addr)) != 0) {
        fprintf(stderr , "failed to bind ip and port to sockfd !\n");
        exit(1);
    }
    // 端口复用
    int opt = 1;
    setsockopt(sockfd , SOL_SOCKET , SO_REUSEADDR , (void*)&opt , sizeof(opt));
    // 3. 调用 Listen函数
    if(listen(sockfd , 1024) != 0) {
        fprintf(stderr , "set the max size of blocking queue failed !\n");
        exit(1);
    }
    // 4. 调用 accept 函数
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    if((connfd = accept(sockfd , (struct sockaddr*)&client_addr , &client_len)) == -1) {
        fprintf(stderr , "connect to client failed !\n");
        exit(1);
    } 
    char client_buf[1024];
    inet_ntop(AF_INET , (void*)&(client_addr.sin_addr.s_addr) , client_buf , sizeof(client_buf));
    printf("client_addr: %s , client_port: %d \n" , client_buf , ntohs(client_addr.sin_port));
    // 5. 开始监听时间并且作出反应
    while(1) {
        // 首先读取
        memset(buf , 0 , sizeof(buf));
        count = read(connfd , buf , sizeof(buf));
        if(count == EOF) {
            fprintf(stderr,"read to the end of client !\n");
            exit(0);
        } 
        // 进行数据的转换
        printf("buf = %s \n" , buf);
        
        if(strcmp(buf , "exit") == 0) {
            printf("client leaves !\n");
            exit(0);
        }
        for(int i = 0 ; i < count ; i ++) {
            buf[i] = toupper(buf[i]);
        }
        if(write(connfd , buf , count) == -1) {
            fprintf(stderr , "failed to write to client!\n");
        }
    }
}