//
//  main.cpp
//  3-4-2
//
//  Created by future on 16/4/4.
//  Copyright © 2016年 future. All rights reserved.
//

#include <stdio.h>
#include <string.h>


#define maxn 100000 + 10 //+1



int main() {
    printf("%d",234);

    char s[maxn];
    scanf("%s",s);
    int tot = 0;
    size_t len = strlen(s);
    for (size_t i = 0; i < len; ++i) {//len +1
        if(s[i] == '1') tot ++;//+1
    }
    printf("%d\n",tot);
    
    
    return 0;
}
