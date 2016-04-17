//
//  main.cpp
//  6.2
//
//  Created by future on 16/4/16.
//  Copyright © 2016年 future. All rights reserved.
//

#include <iostream>
#include <string>

using namespace  std;

const int maxn = 100 + 5;
int last,cur,mynext[maxn];
char s[maxn];




int main(int argc, const char * argv[]) {
    // insert code here...

    while (cin >> (s + 1)) {
        int n = (int)strlen(s + 1);
        last = cur = 0;
        mynext[0] = 0;
        
        for (int i = 1; i <= n; ++i) {
            char ch = s[i];
            if(ch == '[') cur = 0;
            else if(ch == ']') cur = last;
            else {
                mynext[i] = mynext[cur];
                mynext[cur] = i;
                if(cur == last) last = i;
                cur = i;
            }
        }
        for(int i = mynext[0];i != 0;i = mynext[i]){
            cout << s[i];
        }
        cout << endl;
    }
    
    
    
    return 0;
}
