//
//  posix_process.h
//  posix_process
//
//  Created by future on 16/3/9.
//  Copyright © 2016年 future. All rights reserved.
//

#ifndef posix_process_h
#define posix_process_h

#include <spawn.h>
#include <string>
#include <errno.h>
#include <iostream>

using namespace std;

class posix_process{
protected:
    pid_t Pid;
    posix_spawnattr_t SpawnAttr;
    posix_spawn_file_actions_t FileActions;
    char  **argv;
    char  **envp;
    string ProgramPath;
public:
    posix_process(string Path,char **av,char **env);
    posix_process(string Path,char **av,char **env,posix_spawnattr_t X,
                  posix_spawn_file_actions_t Y);
    void run();
    void pwait();
    
    
};


#endif /* posix_process_h */
