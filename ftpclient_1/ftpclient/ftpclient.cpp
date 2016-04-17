//
//  ftpclient.cpp
//  ftpclient
//
//  Created by future on 16/4/7.
//  Copyright © 2016年 future. All rights reserved.
//

#include "ftpclient.hpp"
#include "filereceiver.hpp"


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

char* itoa(size_t t){
    char *buf = new char[128];
    int i = 0;
    while (t) {
        buf[i++] = t % 10 + '0';
        t /= 10;
    }
    buf[i]  = 0;
    return buf;
}

void ftpclient::run(){
    
    char buf[MSS] = {0};
    //读服务器的目录
    read(clientfd, buf, sizeof buf);
    while (1) {
        std::cout << buf << std::endl;
    input:
        std::cout << "please input filename : ";
        std::string filename,senddata;
        std::cin >> filename;
        std::string tempstr = buf;
        if( filename == "q" || filename == "Q" ){
            close(clientfd);
            return;
        } else if(tempstr.find(filename) == -1){
            std::cout << "file not found on the server,again:" <<std::endl;
            goto input;
        }
        
        senddata = filename;
        senddata += " ";
        
        srand((int)time(0));
        int recvport = 10000 + rand() % 6666;
        senddata += itoa(recvport);
        size_t  buflen;
        write(clientfd, senddata.c_str(), senddata.size());//写入想要下载的文件名
        read(clientfd, &buflen ,sizeof buflen);
        
        filereceiver recver(filename.c_str(),buflen, recvport);
        recver.recv();
    }
}

void ftpclient::sys_error(const char *msg){
    perror(msg);
    exit(1);
}