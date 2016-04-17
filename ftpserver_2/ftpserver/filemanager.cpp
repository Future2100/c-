//
//  filemanager.cpp
//  ftpserver
//
//  Created by future on 16/4/6.
//  Copyright © 2016年 future. All rights reserved.
//

#include "filemanager.hpp"


void *myfiletransport(void *arg){
  //  pthread_detach(pthread_self());
        threadmm *tm = static_cast<threadmm*>(arg);
        char *addr = (char*)tm->addr;
        for(int i = 0;i < tm->size;i+= MSS){
            ssize_t len;
    
            if((len = write(tm->fd, addr + tm->off + i, MSS))  < MSS){
                std::cout << pthread_self() << std::endl;
            }
        }
    return nullptr;
}