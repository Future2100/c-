//
//  main.cpp
//  计算进位的个数
//
//  Created by future on 16/3/30.
//  Copyright © 2016年 future. All rights reserved.
//

#include <iostream>

using namespace  std;

int main(int argc, const char * argv[]) {

    int a,b;
    while (cin>> a >> b) {
        if(!a || !b)
            break;
        int counter = 0,c = 0;
        for(int i  = 0 ;i < 9;++i){
            c = (a % 10 + b % 10 + c) > 9 ? 1 : 0;
            counter += c;
            a /= 10,b /= 10;
        }
        cout << counter << endl;
    }
    
    
    
    std::cout << "Hello, World!\n";
    return 0;
}
