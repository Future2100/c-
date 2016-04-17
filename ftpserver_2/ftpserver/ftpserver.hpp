//
//  ftpserver.hpp
//  ftpserver
//
//  Created by future on 16/4/6.
//  Copyright © 2016年 future. All rights reserved.
//

#ifndef ftpserver_hpp
#define ftpserver_hpp

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

class ftpserver{
private:
    int             listenfd;
    int             currentfd;
    sockaddr_in     currentclientaddr;
    socklen_t       currentclientsocklen;
public:
    ftpserver(int);//we will initialize the server sock ,bind and listen
    ~ftpserver();
   // int accept();
    void run();
    inline int getcurrentlistenfd(){ return currentfd;}
    static void sys_error(const char *);
    
};

#endif /* ftpserver_hpp */
