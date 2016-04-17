//
//  filemanager.cpp
//  ftpserver
//
//  Created by future on 16/4/6.
//  Copyright © 2016年 future. All rights reserved.
//

#include "filemanager.hpp"
#include "ftpfiletransmit.hpp"


void filemanager::getfilenamesbypath(const std::string& path,std::string &res){
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


void filemanager::transportdata(int clientfd,std::string &filename,int port){//

    ftpfiletransmit fft(clientfd,filename.c_str(),port);
    fft.send();
    
    
}


//---------------get a file content size by filename-------------
off_t filemanager::getfilecontentsizebyfilename(const char *filename){
    int fd = open(filename, O_RDONLY);
    off_t size;
    size = lseek(fd, 0, SEEK_END);
    close(fd);
    return size;
}
