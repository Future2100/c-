//
//  main.cpp
//  错位字符
//
//  Created by future on 16/3/29.
//  Copyright © 2016年 future. All rights reserved.
//

#include <iostream>


const char *s = "`1234567890-=QWERTYUIOP[]\\ASDFGHJKL;'ZXCVBNM,./";

int main(int argc, const char * argv[]) {
    int i,c;
    while ((c = getchar())!= EOF) {
        for (i = 1; s[i] && s[i] != c; ++i);
        if(s[i]) putchar(s[i-1]);
        else putchar(c);
    }

    return 0;
}
