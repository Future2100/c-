//
//  main.cpp
//  6-3
//
//  Created by future on 16/4/16.
//  Copyright © 2016年 future. All rights reserved.
//

#include <iostream>
#include <string>
#include <stack>

using namespace std;

struct Matrics{
    int a,b;
    Matrics(int a = 0,int b = 0):a(a),b(b){}
} m[26];


int main2(int argc, const char * argv[]) {

    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        char temp;
        cin >> temp;
        int idx = temp - 'A';
        cin >> m[idx].a >> m[idx].b;
    }
    
    string exp;
    cin >> exp;
    bool error = false;
    stack<Matrics> s;
    int res = 0;
    for (int i = 0; i < exp.length(); ++i) {
        if (exp[i] == ')') {
            Matrics param2 = s.top();s.pop();
            Matrics param1 = s.top();s.pop();
            
            if (param1.b != param2.a) {
                error = true;
                break;
            }
            res += param1.a * param1.b * param2.b;
            s.push(Matrics(param1.a,param2.b));
            
        } else if(isalpha(exp[i])){
            s.push(m[exp[i] - 'A']);
        }
    }
    if(error) cout << "error\n";
    else cout << res << endl;
    
    
    
    return 0;
}
