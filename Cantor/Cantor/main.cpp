//
//  main.cpp
//  Cantor
//
//  Created by future on 16/4/15.
//  Copyright © 2016年 future. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <math.h>


using namespace  std;

int findcol(int n){
    n = n * 2;
    return sqrt(n);
}


int main(int argc, const char * argv[]) {

    int n;
    while ( cin >> n) {
        int k = (int)floor((sqrt(8.0 * n + 1) - 1) / 2 - 1e-9) + 1;
        int s = k * (k + 1) / 2;
        printf("%d/%d",s-n + 1,k - s + n);
    }
    
    return 0;
}
