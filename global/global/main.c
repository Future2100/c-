//
//  main.cpp
//  global
//
//  Created by future on 16/3/29.
//  Copyright © 2016年 future. All rights reserved.
//

#include <stdio.h>


int i = 10;//zai data segment


int main(int argc, const char * argv[]) {
    // insert code here...

    
    
    int i = 20; //in bbs segment    
    printf("%d %d",i,i);
    
    return 0;
}
