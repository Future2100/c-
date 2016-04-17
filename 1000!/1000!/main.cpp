//
//  main.cpp
//  1000!
//
//  Created by future on 16/3/29.
//  Copyright © 2016年 future. All rights reserved.
//

#include <iostream>
#include <string>


//单调桟  双端队列  线段树 滑动窗口
#define maxn 3000

int res[maxn];

int main(int argc, const char * argv[]) {

    memset(res, 0, sizeof(res));
    res[0] = 1;
    int n;
    std::cin >> n;
    for (int i = 2; i <= n; ++i) {
        int c = 0;
        for (int j = 0; j < maxn; ++j) {
            int r = res[j] * i + c;
            res[j] = r % 10;
            c = r / 10;
        }
    }
    int i ;
    for ( i = maxn -1; i >= 0; i--) {
        if(res[i] != 0)
            break;
    }
    for (int j  = i; j >= 0 ; --j) {
        std::cout << res[j] ;
    }
    
    
    
    return 0;
}
