//
//  main.cpp
//  丑数
//
//  Created by future on 16/4/11.
//  Copyright © 2016年 future. All rights reserved.
//

#include <iostream>
#include <queue>
#include <set>
#include <vector>
using namespace  std;


using LL = long long;

const int coeff[] = {2,3,5};


int main(int argc, const char * argv[]) {
    
    
    
    
    
    priority_queue<LL,vector<LL>,greater<LL>> pq;
    set<LL> s;
    pq.push(1);
    s.insert(1);
    for (int i = 1; ; ++i) {
        LL x = pq.top();pq.pop();
        if(i == 1500){
            cout << x << endl;
            break;
        }
        for (int j = 0; j < 3; ++j) {
            LL x2 = x * coeff[j];
            if(!s.count(x2)) { s.insert(x2),pq.push(x2);}
        }
    }
    
    
    
    
    return 0;
}
