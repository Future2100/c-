//
//  main.cpp
//  getaddrinfo
//
//  Created by future on 16/3/26.
//  Copyright © 2016年 future. All rights reserved.
//

#include "mytcp.hpp"
#include <time.h>

char *getcurrenttime(){
    time_t  ticks;
    time(&ticks);
    return ctime(&ticks);
}
class cc{
public:
    cc(){
        std::cout << "cc " << std::endl;
    }
    ~cc(){
        std::cout << "~cc" << std::endl;
    }
};


class aa{
public:
    cc c;
    aa(){
        std::cout << "aa " << std::endl;
    }
    ~aa(){
        std::cout << "~aa" << std::endl;
    }
};


class bb: public aa{
public:
    cc a;
    bb(){
        std::cout << "bb" << std::endl;
    }
    ~bb(){
        std::cout << "~bb" << std::endl;
    }
};


int main(int argc, const char * argv[]) {
    
    //bb b;
   
    mytcp m("0","8888");
    int listenfd = m.tcp_listen();
    sockaddr_storage clientaddr;
    time_t t;
    for(;;){
        socklen_t len = sizeof(clientaddr);
        int connfd = accept(listenfd, (struct sockaddr*)&clientaddr, &len);
        sockaddr_in *tempaddr = (sockaddr_in*)&clientaddr;
        std::cout << "connect from " << inet_ntoa(tempaddr->sin_addr) << std::endl;        
        time(&t);
        char buf[128];
        snprintf(buf,sizeof buf,"%.24s\r\n",ctime(&t));
        ssize_t wret = write(connfd, buf ,sizeof(buf));
        if(wret <= 0)
            m.sys_error("write");
    }

    
    
    return 0;
}
