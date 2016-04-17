//
//  ct_thread.cpp
//  thread_frame_1
//
//  Created by future on 16/3/21.
//  Copyright © 2016年 future. All rights reserved.
//

#include "ct_thread.hpp"

ct_thread::ct_thread(void){
    Attr = nullptr;
}

ct_thread::ct_thread(pthread_attr_t *Attribute){
    Attr = Attribute;
}
ct_thread::~ct_thread(){
    
}

void ct_thread::begin(void *(*PFN)(void *) , void *X){
    pthread_create(&ThreadId, Attr, PFN, X);
}

void ct_thread::wait(void){
    pthread_join(ThreadId, nullptr);
}

pthread_t ct_thread::threadHandle(){
    return ThreadId;
}

pthread_t ct_thread::threadId(){
    return pthread_self();
}

