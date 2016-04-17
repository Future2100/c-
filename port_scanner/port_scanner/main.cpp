//
//  main.cpp
//  port_scanner
//
//  Created by future on 16/3/21.
//  Copyright © 2016年 future. All rights reserved.
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/errno.h>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <iostream>

struct qujian{
    int begen,end;
};


void *pthread_scanner(void *arg){
    qujian *q = static_cast<qujian*>(arg);
    struct sockaddr_in serveraddr;
    bzero(&serveraddr,sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    inet_pton(AF_INET,"127.0.0.1",&serveraddr.sin_addr.s_addr);

    for(int i = q->begen;i < q->end;++i){
         int listenfd = socket(AF_INET,SOCK_STREAM,0);
        serveraddr.sin_port = htons(i);
        if(connect(listenfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr)) == 0){
            printf("%d\n",i);
        }
        close(listenfd);
    }
    return 0;
}


int main(int argc,char *argv[]){
    
    
    struct sockaddr_in serveraddr;
    bzero(&serveraddr,sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    inet_pton(AF_INET,"127.0.0.1",&serveraddr.sin_addr.s_addr);
    serveraddr.sin_port = htons(13);
    pthread_t pid[7];
   
    
    qujian q[7];
    for(int i = 1,j = 0;i < 65535 ;i += 10000,j++){

        q[j].begen = i;
        q[j].end = i*10000;
        pthread_create(&pid[j],nullptr,pthread_scanner,&q[j]);
    }
    
    for(int i = 0;i < 7;++i)
        pthread_join(pid[i], nullptr);
    
    
    return 0;
    
}