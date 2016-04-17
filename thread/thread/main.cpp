//
//  main.cpp
//  thread
//
//  Created by future on 16/3/14.
//  Copyright © 2016年 future. All rights reserved.multiple threads
//

#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
#include <functional>

using namespace std;


#in\
cl\
ude<stdio.h>


atomic_int



void func(atomic<int> &counter){
    for(int i = 0;i < 10000;++i)
        counter ++;
}

int main(int argc, const char * argv[]) {

    vector<thread> vc;
    atomic_int counter(0);
    for(int i = 0;i < 10; ++i){
        vc.push_back(thread(func,ref(counter)));
    }
    
//    for(int i = 0; i < 10; ++i){
//        vc[i].join();
//    }

    for(auto &t :vc)//等待线程回收，同时也能起到同步的作用
        t.join();
    cout << "counter : " << counter << endl;
    
    
    return 0;
}
