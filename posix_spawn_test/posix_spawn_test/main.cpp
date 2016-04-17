//
//  main.cpp
//  posix_spawn_test
//
//  Created by future on 16/3/9.
//  Copyright © 2016年 future. All rights reserved.
//

#include <iostream>
#include <spawn.h>
#include <unistd.h>
#include <string>
#include <sys/wait.h>

using namespace std;

int main(int argc, const char * argv[]) {

    pid_t pid;
    char  *argv1[] = {"aa",nullptr};
    int ret = posix_spawn(&pid,"/bin/pwd",NULL,NULL,argv1,NULL);//打开一个新的进程
    if(ret != 0){
        perror("posix_spawn");
        exit(1);
    }
    
    cout << pid << endl;
        
        
    
    
    
    return 0;
}



