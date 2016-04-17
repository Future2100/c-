//
//  ftpserver.cpp
//  ftpserver
//
//  Created by future on 16/4/6.
//  Copyright © 2016年 future. All rights reserved.
//
//    char buf[1024];
//    gethostname(buf, sizeof(buf));
//    std::cout << buf << std::endl;
//    struct hostent *hent = gethostbyname(buf);
//    char **addr = hent->h_addr_list;
//    while(*addr!=NULL)
//    {
//        std::cout<<inet_ntoa(*(struct in_addr *)(*addr))<<std::endl;
//        addr++;
//    }


#include "ftpserver.hpp"
#include "filemanager.hpp"
#include "mysocket.hpp"
#include <stdlib.h>


ftpserver::ftpserver(const char *addr,int port){
    serversock = new mysocket(addr,port);
    serversock->mybind();
    serversock->mylisten();
}

ftpserver::~ftpserver(){
    delete serversock;
    
}

long myatoi(const char *str){
    long res = 0,len = strlen(str);
    for (long i = len -1; i >= 0; --i) {
        res = res * 10 + (str[i] - '0');
    }
    return res;
}

void *deal_with(void *arg){
    int clientfd = *(int*)arg;
    pthread_detach(pthread_self());
    std::string dir;
    filemanager::getfilenamesbypath(".", dir);
    write(clientfd, dir.c_str(), dir.length());

    while (1) {
        char buf[1500];
    again:
        ssize_t len;
        if((len = read(clientfd, buf, sizeof(buf))) < 0){
            if(errno == EINTR)
                goto again;
            else
                return nullptr;
        } else if(len == 0){
            sockaddr_in tempaddr;
            socklen_t len = sizeof(tempaddr);
            getsockname(clientfd, (sockaddr*)&tempaddr, &len);
            close(clientfd);
            std::cout << inet_ntoa(tempaddr.sin_addr) << ":" << ntohs(tempaddr.sin_port) <<
            "断开连接" << std::endl;
            return nullptr;
        }
        
        buf[len] = 0;
        std::stringstream ss(buf);
        // transport file
        std::string filename;
        std::string port;
        ss >> filename;
        ss >> port;
        
        //transport filesize
        size_t filesize = filemanager::getfilecontentsizebyfilename(filename.c_str());
        write(clientfd, &filesize, sizeof filesize);
        
        
        
        //开启多线程传输数据
        filemanager::transportdata(clientfd, filename,(int)myatoi(port.c_str()));

    }
    return nullptr;
}

void ftpserver::run(){

    while(1){
        serversock->myaccept();//如果失败的话会直接退出
        pthread_t pth;
        int tempclientfd = serversock->clientfd;
        pthread_create(&pth, nullptr, deal_with, &tempclientfd);
    }
}


void ftpserver::sys_error(const char *msg){
    perror(msg);
    exit(1);
}