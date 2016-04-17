//
//  test.cpp
//  6-3
//
//  Created by future on 16/4/16.
//  Copyright © 2016年 future. All rights reserved.
//

#include <stdio.h>


int main23(int argc,char *argv[]){
    for (int i = 1010; i < 10000; ++i) {
        if(i / 1000 == (i % 100) / 10){
            printf("%d\n",i);
        }
    }
    
    
    
    return 0;
}
