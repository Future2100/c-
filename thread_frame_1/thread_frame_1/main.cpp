//
//  main.cpp
//  thread_frame_1
//
//  Created by future on 16/3/21.
//  Copyright © 2016年 future. All rights reserved.
//


#include <set>
#include <string>
#include <iostream>
#include "ct_thread.hpp"
#include "set_server.hpp"

using namespace std;




set<string,less<string>> A;
set<string,less<string>> B;
set<string,less<string>> C;
set<string,less<string>>::iterator i;



int main(int argc, const char * argv[]) {
    
    cout << "Start main thread " << endl;
    A.insert("hello");
    B.insert("world");
    
    set_server Server;
    C = Server.setUnion(A, B);
    i = C.begin();
    while (i != C.end()) {
        cout << *i << endl;
        i ++ ;
    }
    
    
    return 0;
}
