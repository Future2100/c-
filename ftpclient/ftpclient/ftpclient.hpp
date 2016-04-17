//
//  ftpclient.hpp
//  ftpclient
//
//  Created by future on 16/4/7.
//  Copyright © 2016年 future. All rights reserved.
//

#ifndef ftpclient_hpp
#define ftpclient_hpp

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
#include <fcntl.h>


const int MSS = 1460;

class ftpclient{
private:
    int             port;
    int             clientfd;
    sockaddr_in     serveraddr;
    
public:
    ftpclient(const char *addr,int port);
    void myconnect();
    void run();
    
    
    static void sys_error(const char *msg);
};

#endif /* ftpclient_hpp */
