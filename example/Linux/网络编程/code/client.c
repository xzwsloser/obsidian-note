#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
#include<unistd.h>
#define SERVER_PORT 10086
int main() {
    // 1. 首先获取 clientfd
    int clientfd,count;
    char buf[1024];
    clientfd = socket(AF_INET , SOCK_STREAM , 0);
    if(clientfd == -1) {
        fprintf(stderr , "failed to get a clientfd !\n");
        exit(1);
    }
    // 2. Connect 函数
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(connect(clientfd , (struct sockaddr*)&server_addr , sizeof(server_addr)) != 0) {
        fprintf(stderr , "connect to server failed !\n");
        exit(1);
    }
    while(1) {
        // 读取
        scanf("%s",buf);
        if(write(clientfd , buf , strlen(buf)) == -1) {
            fprintf(stderr , "write to server failed !\n");
            continue;
        }
        // 读取
        count = read(clientfd , buf , sizeof(buf));
        if(count == EOF) {
            fprintf(stderr , "read failed !\n");
            continue;
        }
        write(STDOUT_FILENO , buf , count);
        write(STDERR_FILENO , "\n" , 1);
    }
}