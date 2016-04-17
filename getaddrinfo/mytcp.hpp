//
//  mytcp.hpp
//  getaddrinfo
//
//  Created by future on 16/3/26.
//  Copyright © 2016年 future. All rights reserved.
//

#ifndef mytcp_hpp
#define mytcp_hpp

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/errno.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <strings.h>
#include <iostream>
#include <string>
#include <netdb.h>

class mytcp{
private:
    std::string host;
    std::string serv;
    socklen_t   addrlen;
    int         listenfd;
    
public:
    mytcp(std::string host,std::string serv):host(host),serv(serv){
        
    }
    
    int tcp_listen();// return listen fd
    void sys_error(const std::string msg){
        perror(msg.c_str());
        exit(1);
    }
    void print_err_quit(const std::string msg){
        std::cout << msg << std::endl;
        exit(1);
    }
    
    
    
};


#endif /* mytcp_hpp */
