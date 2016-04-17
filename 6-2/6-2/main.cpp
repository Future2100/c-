//
//  main.cpp
//  6-2
//
//  Created by future on 16/4/16.
//  Copyright © 2016年 future. All rights reserved.
//

//stack 的相关应用
#include <iostream>
#include <stack>

using namespace std;



const int MAXN = 1000 + 10;

int n,target[MAXN];



int main(int argc, const char * argv[]) {

    while (cin >> n) {
        for (int i = 0; i < n; ++i) {
            cin >> target[i];
        }
        int ok = 1;
        int A = 1,B = 0;
        stack<int> s;
        while (B < n) {
            if(A == target[B]){ A++,B++;}//如果相等，那么两者都向后
            else if(!s.empty() && s.top() == target[B]){s.pop(),B++;}//不相等，那么看桟顶元素是否相等
            else if(A <= n) s.push(A++);//不相等，压桟
            else {ok = 0;break;}//都不对的话，impossible
        }
        cout << (ok ? "yes" : "no")<< endl;
    }
    
    
    return 0;
}
