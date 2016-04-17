//
//  posix_process.cpp
//  posix_process
//
//  Created by future on 16/3/9.
//  Copyright © 2016年 future. All rights reserved.
//

#include <stdio.h>
#include "posix_process.h"
#include <sys/wait.h>



posix_process::posix_process(string Path,char **av,char **env){
    argv = av;
    envp = env;
    ProgramPath =  Path;
    posix_spawnattr_init(&SpawnAttr);
    posix_spawn_file_actions_init(&FileActions);
}

posix_process::posix_process(string Path,char **av,char **env,
                             posix_spawnattr_t X,posix_spawn_file_actions_t Y){
    
    argv = av;
    envp = env;
    ProgramPath = Path;
    SpawnAttr = X;
    FileActions = Y;
    posix_spawnattr_init(&SpawnAttr);
    posix_spawn_file_actions_init(&FileActions);
}


void posix_process::run(){
    posix_spawn(&Pid,ProgramPath.c_str(),&FileActions,
                &SpawnAttr,argv,envp);
}

void posix_process::pwait(){
    wait(&Pid);
}
