//
//  main.cpp
//  test_mmap
//
//  Created by future on 16/4/9.
//  Copyright © 2016年 future. All rights reserved.
//

#include <iostream>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/stat.h>


using namespace std;

off_t getfilecontentsizebyfilename(const char *filename){
    int fd = open(filename, O_RDONLY);
    off_t size;
    size = lseek(fd, 0, SEEK_END);
    close(fd);
    return size;
}


int main(int argc, const char * argv[]) {

    char dest[] = "5.pdf";
    char src[] = "2.pdf";
    int fd = open(src, O_RDWR);
    off_t filelen = getfilecontentsizebyfilename(src);
    
    
    int fd1 = open(dest, O_CREAT | O_RDWR,0777);
    lseek(fd1, filelen - 1 , SEEK_SET);
    write(fd1, "\n", 1);
    lseek(fd1, 0, SEEK_SET);
    
    char *addr1 = (char*)mmap(nullptr, filelen, PROT_READ | PROT_WRITE, MAP_SHARED, fd1, 0);
    if (addr1 == MAP_FAILED) {
        perror("1map");
    }

    int had = 0;
    char buf[1024] = {0};
    while (filelen) {
        int len = (int)read(fd,buf,sizeof(buf));
        int i = 0;
        while (len) {
            addr1[had++] = buf[i++];
            len --;
        }
        filelen -= len;
        
    }
    
    
    
    return 0;
}
