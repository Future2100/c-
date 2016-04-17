//
//  filereceiver.cpp
//  ftpclient
//
//  Created by future on 16/4/8.
//  Copyright © 2016年 future. All rights reserved.
//

#include "filereceiver.hpp"
#include <time.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <math.h>
#include "mysocket.hpp"

filereceiver::filereceiver(const char *filename,size_t filesize,int port):filesize(filesize),recvport(port){
    srand((int)time(nullptr));
    umask(0);
    int mmfd = open(filename,O_CREAT | O_RDWR,0777);
    lseek(mmfd, filesize - 1, SEEK_SET);
    write(mmfd, " ", 1);
    lseek(mmfd, 0, SEEK_SET);
    mmaddr = (char*)mmap(nullptr, filesize, PROT_WRITE, MAP_SHARED, mmfd, 0);
    if(mmaddr == MAP_FAILED){
        perror("mmap");
        exit(1);
    }
    close(mmfd);
}



struct recvstruct {
    char *mmaddr;
    int   off;
    int    recvport;
};

void *recvthread_fun(void*  arg){
    //-------------transport param-----------------
    recvstruct rs = *(recvstruct*)arg;
    off_t off = rs.off;
    char *mmaddr = rs.mmaddr;
    int recvport = rs.recvport;
    
    //-------------create listen fd----------------
    char buf[1024];

    mysocket* ms = new mysocket("127.0.0.1",recvport);
    ms->mybind();
    ms->mylisten();
    ms->myaccept();
    //-------------begin to recv ------------------
    size_t len = 0;
    int had = 0;
    while ((len = read(ms->clientfd, buf, sizeof buf)) > 0) {
        int i = 0;
        while (len) {
            mmaddr[off + had++] = buf[i++];
            len --;
        }
    }
    close(ms->listenfd);
    return nullptr;
    
}

void filereceiver::recv(){
    int len = ceil((filesize+0.0) / SLICE);
    recvstruct *rs = new recvstruct[len];
    pthread_t *pid = new pthread_t[len];
    
    for (int i = 0; i < len; ++i) {
        rs[i].off = i*SLICE;
        rs[i].mmaddr = mmaddr;
        rs[i].recvport = recvport + i;
        pthread_create(&pid[i], NULL, recvthread_fun, &rs[i]);
    }
    for (int i = 0; i < len; i++) {
        pthread_join(pid[i], NULL);
    }
    delete [] rs;
    delete [] pid;
    
}