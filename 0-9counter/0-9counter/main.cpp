//
//  main.cpp
//  0-9counter
//
//  Created by future on 16/3/30.
//  Copyright © 2016年 future. All rights reserved.
//

#include <iostream>


// f(n) = n10e(n-1)

int myexp(int n){
    return n ? n*myexp(n-1) : 1;
}


int main(int argc, const char * argv[]) {

    int n;
    std::cin >> n;
    for (int i = 0; i < 10; ++i) {
        std::cout << i << " " << i*myexp(i-1) << std::endl;
    }
    
    
    return 0;
}
