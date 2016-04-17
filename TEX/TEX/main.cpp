//
//  main.cpp
//  TEX
//
//  Created by future on 16/3/29.
//  Copyright © 2016年 future. All rights reserved.
//

//使用一个标志变量


#include <iostream>

int main(int argc, const char * argv[]) {

    int c,q = 1;
    while ((c = getchar()) != EOF) {
        if( c == '"') {printf("%s",q ? "``":"\""); q = !q;}
        else
            putchar(c);
    }
    
    
    return 0;
}
