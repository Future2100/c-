//
//  mytcp.cpp
//  getaddrinfo
//
//  Created by future on 16/3/26.
//  Copyright © 2016年 future. All rights reserved.
//

#include "mytcp.hpp"

int mytcp::tcp_listen(){
    struct addrinfo hints,*res,*ressave;
    const int on  = 1;
    bzero(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_socktype = SOCK_STREAM;
    int n;
    if((n = getaddrinfo(host.c_str(), serv.c_str(), &hints, &res)) != 0){
        sys_error("getaddrinfo");
    }
    ressave = res;
    do{
        listenfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if(listenfd < 0)
            continue;
        setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
        if(bind(listenfd, res->ai_addr, res->ai_addrlen) == 0)
            break;
        close(listenfd);
        
    }while ((res = res->ai_next) != nullptr) ;
    if(res == nullptr)
        print_err_quit("tcp_listen err for " + host + serv);
    addrlen = res->ai_addrlen;
    listen(listenfd, 5);

    freeaddrinfo(ressave);
    return listenfd;
    
}