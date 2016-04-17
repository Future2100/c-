//
//  ftpfiletransmit.hpp
//  ftpserver
//
//  Created by future on 16/4/8.
//  Copyright © 2016年 future. All rights reserved.
//

//开起多个线程来进行传输，
//      1.需要文件名
//      2.seq文件的偏移量
//      3.端口号
//

#ifndef ftpfiletransmit_hpp
#define ftpfiletransmit_hpp


#include <stdio.h>
#include <string>
#include <sstream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <sys/socket.h>
#include <pthread.h>



const int SLICE = 1024*1024 * 10; // 10Mb

//每次咋开始的时候都要先发送一个off
//只用一个文件名
//在用一个起始端口号

struct threadmm{
    int     clientsockfd;
    size_t  transmitlength;
    size_t  off;
    char*   addr;
    int     port;
};

class ftpfiletransmit{
private:
    const char*     filename;//文件名
    size_t          size;
    char*           addr;
    unsigned short  port;//起始端口
    int             clientsockfd;
public:
    ftpfiletransmit(int ,const char*,unsigned short);
    void send();
    friend void*  pthread_transimit_func(void*);
};





#endif /* ftpfiletransmit_hpp */
