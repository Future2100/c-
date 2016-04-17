//
//  ct_thread.hpp
//  thread_frame_1
//
//  Created by future on 16/3/21.
//  Copyright © 2016年 future. All rights reserved.
//

#ifndef ct_thread_hpp
#define ct_thread_hpp

#include <pthread.h>


typedef void *(*FunctionPtr)(void*);

class ct_thread{
    
private:
    pthread_t       ThreadId;
    pthread_attr_t  *Attr;
    
public:
    ct_thread(void);
    ct_thread(pthread_attr_t *Attr);
    ~ct_thread(void);
    
    
public:
    
    void        begin(FunctionPtr PFN,void *X);
    void        wait(void);
    pthread_t   threadHandle(void);
    pthread_t   threadId(void);
    
};





#endif /* ct_thread_hpp */
