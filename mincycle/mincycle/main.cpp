//
//  main.cpp
//  mincycle
//
//  Created by future on 16/3/29.
//  Copyright © 2016年 future. All rights reserved.
//

#include <iostream>

int main(int argc, const char * argv[]) {

    char buf[100];
    std::cin >> buf;
    size_t len = strlen(buf);
    for (int i = 1; i <= len; ++i) {
        if(len % i == 0){
            int ok = 1;
            for (int j = i; j < len; ++j) {
                if(buf[j] != buf[j % i]){
                    ok = 0;
                    break;
                }
            }
            if (ok) {
                std::cout << i << std::endl;
            }
        }
    }
    
    
    return 0;
}
