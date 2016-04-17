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



ftpserver::ftpserver(int port){
    
    
    
    if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        sys_error("socket");
    }
    sockaddr_in serveraddr;
    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = htonl(0);
    
    const int reuse = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof reuse);
    
    if(::bind(listenfd,(sockaddr*)&serveraddr,sizeof(serveraddr)) < 0)
        sys_error("bind");
    if(listen(listenfd, LISTENQ) < 0)
        sys_error("lsiten");
}

ftpserver::~ftpserver(){
    
}

//包装accept函数
//int ftpserver::accept(){
//    currentclientsocklen = sizeof(currentclientaddr);
//again:
//    if((currentfd = ::accept(listenfd, nullptr, nullptr)) < 0)
//    {
//        if( errno == EINTR)
//            goto again;
//        else
//            sys_error("accept");
//    }else {
//        std::cout << inet_ntoa(currentclientaddr.sin_addr) << "已连接" << std::endl;
//    }
//    return currentfd;
//}




void *deal_with(void *arg){
    
    //pthread_detach(pthread_self());
    
    std::string dir;
    filemanager::getfilenamesbypath(".", dir);
    int clientfd = *(int*)arg;
    write(clientfd, dir.c_str(), dir.length());


    char buf[1500];
again:
    ssize_t len;
    if((len = read(clientfd, buf, sizeof(buf))) < 0){
        if(errno == EINTR)
            goto again;
        else
            return nullptr;
    }
    buf[len] = 0;
    std::cout << buf << endl;
    // transport file
    std::string filename = buf;
    filemanager::transportdata(clientfd, filename);
    

    return nullptr;
}

void ftpserver::run(){

    while(1){
        
        pthread_t pth;
        int tempclientfd  = ::accept(listenfd, nullptr, nullptr);
        pthread_create(&pth, nullptr, deal_with, &tempclientfd);
    }
}


void ftpserver::sys_error(const char *msg){
    perror(msg);
    exit(1);
}