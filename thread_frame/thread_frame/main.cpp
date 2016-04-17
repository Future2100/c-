//
//  main.cpp
//  thread_frame
//
//  Created by future on 16/3/18.
//  Copyright © 2016年 future. All rights reserved.
//

//首先，我们需要打*.hpp / *.cpp都要放入main函数所在的头文件中，其实编写模板都应该全部放在头文件或者.cpp文件中，不然的话会造成类型
//找不到吧


#include <iostream>
#include <set>
#include <string>
#include "mt_set.hpp"
#include "ct_thread.hpp"
#include "server_argument.hpp"
#include "mt_set.cpp"



using namespace std;



set<string,less<string>> A;
set<string,less<string>> B;
set<string,less<string>> C;
set<string,less<string>>::iterator i;



int main(int argc, const char * argv[]) {

    cout << "Start main thread " << endl;
    A.insert("hello");
    B.insert("world");
    
    set_server<string> Server;
    C = Server.setUnion(A, B);
    i = C.begin();
    while (i != C.end()) {
        cout << *i << endl;
        i ++ ;
    }
    
    
    
    return 0;
}
