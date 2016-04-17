//
//  main.cpp
//  posix_process
//
//  Created by future on 16/3/9.
//  Copyright © 2016年 future. All rights reserved.
//

#include <iostream>
#include "posix_process.h"

int main(int argc, const char * argv[],char *envp[]) {


    char *argv1[] = {(char*)"/bin/ls",(char*)"-l",nullptr};
    posix_process Child1("/bin/ls",argv1,nullptr);

    Child1.run();
    Child1.pwait();

    
    
    return 0;
}
