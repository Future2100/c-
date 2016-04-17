//
//  set_server.cpp
//  thread_frame_1
//
//  Created by future on 16/3/21.
//  Copyright © 2016年 future. All rights reserved.
//

#include "set_server.hpp"
#include "ct_thread.hpp"
#include "mt_set.hpp"
#include <iostream>

using namespace std;


set_server::set_server(){
    
}

void *setUnion(void *X){
        set_server *server = static_cast<set_server*>(X);
        mt_set SafeSet(server->argument.a);
        server->argument.result = SafeSet.setUnion(server->argument.b);
    return nullptr;
}



set<string,less<string>> set_server::setUnion(set<string,less<string>> X,set<string,less<string>> Y){
    lock();
    ct_thread thread;
    argument.a = X;
    argument.b = Y;
    thread.begin(::setUnion, this);
    thread.wait();
    unlock();
    return argument.result;
}
