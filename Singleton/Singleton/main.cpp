//
//  main.cpp
//  Singleton
//
//  Created by future on 16/3/5.
//  Copyright © 2016年 future. All rights reserved.
//

#include <iostream>
#include <pthread.h>

#define barrier() __asm__ volatile ("lwsync")

template<class T>
class Singleton{
    volatile Singleton *pInst = 0;
public:
    Singleton *GetInstance(){
        if(!pInst){
            lock();
            if(!pInst){
                Singleton *temp = new Singleton;
                barrier();
                pInst = temp;
            }
            unlock();
        }
        return pInst;
    }
};


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
