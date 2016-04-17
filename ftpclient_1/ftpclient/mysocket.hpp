//
//  mysocket.hpp
//  ftpserver
//
//  Created by future on 16/4/8.
//  Copyright © 2016年 future. All rights reserved.
//

#ifndef mysocket_hpp
#define mysocket_hpp

#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/errno.h>
#include <sys/socket.h>
#include <string>
#include <sys/types.h>
#include <cstdlib>
#include <netdb.h>
#include <iostream>
#include <sstream>


const int LISTENQ = 5;


class mysocket{
public:
    mysocket(const char *addr,int port);
    mysocket(in_addr,int port);
    mysocket();

public:
    int mybind();
    int myaccept();
    int mylisten();
    int myconnect();

    
    
public:
    int             listenfd;
    int             clientfd;
    sockaddr_in     serveraddr,clientaddr;
    socklen_t       clientlen,serverlen;
    
    
    
};

#endif /* mysocket_hpp */
