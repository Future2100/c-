//
//  ftpclient.cpp
//  ftpclient
//
//  Created by future on 16/4/7.
//  Copyright © 2016年 future. All rights reserved.
//

#include "ftpclient.hpp"


ftpclient::ftpclient(const char *addr,int port):port(port){
    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = inet_addr(addr);
   
}

void ftpclient::myconnect(){
    

    
    if((clientfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        sys_error("socket");
    }
    if(connect(clientfd, (sockaddr*)&serveraddr, sizeof(serveraddr)) < 0){
        sys_error("connect");
    }

}


void ftpclient::run(){
    
    char buf[MSS] = {0};
    //读服务器的目录
    read(clientfd, buf, sizeof buf);
    std::cout << buf << std::endl;
    
    std::cout << "please choose file to download to local:" << std::endl;
    std::string filename;
    std::cin >> filename;
    write(clientfd, filename.c_str(), filename.size());//写入想要下载的文件名
    
    int fd = open(filename.c_str(),O_RDWR | O_CREAT,0777);
    size_t len;
    while ((len = read(clientfd, buf, sizeof buf)) > 0) {
        write(fd, buf, len);
        std::cout << buf << std::endl;
        memset(buf, 0, sizeof buf);
    }
    //close(clientfd);
    
    
}

void ftpclient::sys_error(const char *msg){
    perror(msg);
    exit(1);
}