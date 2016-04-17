//
//  filemanager.hpp
//  ftpserver
//
//  Created by future on 16/4/6.
//  Copyright © 2016年 future. All rights reserved.
//

#ifndef filemanager_hpp
#define filemanager_hpp

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


const int MSS = 1460;





//thread transport file method
void *myfiletransport(void *arg);

//file manager class
class filemanager{
public:
    
    static void getfilenamesbypath(const std::string& path,std::string &res);
    
    static void transportdata(int clientfd,std::string &filename,int port);
    //---------------get a file content size by filename-------------
    static off_t getfilecontentsizebyfilename(const char *filename);
    //----------------get a file content size by fd-------------------
    inline static off_t getfilecontentsizebyfd(int fd){
        return lseek(fd, 0, SEEK_END);
    }
    
};

#endif /* filemanager_hpp */
