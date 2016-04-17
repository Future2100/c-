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
#include <pthread.h>


using namespace std;


const int PREFILESIZE = 1024*1460;
const int MSS = 1460;

//--------------parameter struct---------------
struct threadmm{
    void *addr;
    size_t size;
    int   fd;
    size_t off;
    
};

//thread transport file method
void *myfiletransport(void *arg);

//file manager class
class filemanager{
public:
    
    static void getfilenamesbypath(const std::string& path,std::string &res){
        DIR *dir = opendir(path.c_str());
        dirent* drent;
        while((drent = readdir(dir)) != NULL){
            if(strcmp(drent->d_name , ".") == 0 || strcmp(drent->d_name , "..") == 0 ){
                continue;
            } else {
                if(drent->d_type == DT_DIR){
                    res += "*";
                    res += drent->d_name;
                    res += "*\n";
                } else {
                    res += drent->d_name;
                    res += "\n";
                }
            }

        }
        return ;
    }
    
    
    
   // --------despatch   transport file task---------------------
    static void transportdata(int clientfd,std::string &filename){//
        int fd = open(filename.c_str(), O_RDONLY);
        off_t size = getfilecontentsizebyfd(fd);
        char *mm = (char*)mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0);
        int len = ceil(size / PREFILESIZE) + 1;
        threadmm *tm = new threadmm[len];
        int i = 0;
        for( ;i < len -1 ;++i){
            tm[i].addr = mm;
            tm[i].off = i*PREFILESIZE;
            tm[i].fd = clientfd;
            tm[i].size = PREFILESIZE;
            pthread_t pid;
            pthread_create(&pid, NULL,myfiletransport , &tm[i]);
        }
        tm[i].addr = mm;
        tm[i].off = i*PREFILESIZE;
        tm[i].fd = clientfd;
        tm[i].size = size % PREFILESIZE;
        pthread_t pid;
        pthread_create(&pid, NULL,myfiletransport , &tm[i]);
        
    }
    
    //---------------get a file content size by filename-------------
    static off_t getfilecontentsizebyfilename(const char *filename){
        int fd = open(filename, O_RDONLY);
        off_t size;
        size = lseek(fd, 0, SEEK_END);
        close(fd);
        return size;
    }
    //----------------get a file content size by fd-------------------
    static off_t getfilecontentsizebyfd(int fd){
        return lseek(fd, 0, SEEK_END);
    }
    
    
};

#endif /* filemanager_hpp */
