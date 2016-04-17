//
//  main.cpp
//  stack_to_queue
//
//  Created by future on 16/4/16.
//  Copyright © 2016年 future. All rights reserved.
//

#include <iostream>
#include <stack>
#include <queue>

using namespace std;

class Solution
{
public:
    void push(int node) {
        stack1.push(node);
    }
    
    int pop() {
        if(stack2.empty()){
            int size = (int)stack1.size();
            for(int i = 0;i < size;++i){
                cout << stack1.top() << endl;
                stack2.push(stack1.top());stack1.pop();
            }
        }
        int ret = stack2.top();
        stack2.pop();
        return ret;
    }
    
private:
    stack<int> stack1;
    stack<int> stack2;
};

int main(int argc, const char * argv[]) {

    
    Solution s;
    while (1) {
        int n;
        cin >> n;
        if( n== 1){
            cin >> n;
            s.push(n);
        }else {
            cout << s.pop() << endl;
        }
    }
    
    
    return 0;
}


