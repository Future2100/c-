//
//  main.cpp
//  6_3_1_1
//
//  Created by future on 16/4/16.
//  Copyright © 2016年 future. All rights reserved.
//

#include <iostream>
#include <cstring>

const int maxd = 20;
int  s[1 << maxd];

using namespace  std;

int main(int argc, const char * argv[]) {
    // insert code here...
    int D,I;
    while(cin >> D >> I){
        memset(s, 0, sizeof(s));
        int k = 1,n = (1<<D) -1;
        for(int i = 0;i < I;++i){
            k = 1;
            while (1) {
                s[k] = !s[k];
                k = s[k] ? k * 2 : 2* k +1;
                if(k > n) break;
            }
        }
        printf("%d\n",k /2);
    }

    
    
    
    return 0;
}

