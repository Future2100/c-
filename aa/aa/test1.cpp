//
//  test1.cpp
//  aa
//
//  Created by future on 16/3/17.
//  Copyright © 2016年 future. All rights reserved.
//


#include <iostream>

using namespace std;

#define max 33

int main2(int argc ,char *argv[]){
    for(int i = 0;i < max;++i)
        for(int j = i+1;j < max;++j)
            for(int k = j+1;k < max;++k){
                if( i*i + j*j + k*k == 1000){
                    cout << i << " " << j << " " << k << endl;
                }
            }
        
    
    
    
    
    return 0;
}