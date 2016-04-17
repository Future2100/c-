//
//  main.cpp
//  repeat
//
//  Created by future on 16/3/25.
//  Copyright © 2016年 future. All rights reserved.
//

#include <iostream>
#include <string>
#include <set>
#include <cctype>



using namespace std;

char findFirstRepeat(string A, int n) {
    // write code here
    set<char> m;
    for(int i = 1;i < A.length() ;++i){
        
            auto ret = m.find(A[i]);
            if(ret != m.end())
                return A[i];
            else {
                m.insert(A[i]);
        
        }
        
    }
    return -1;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    string str;
    size_t pos = 0;
   
    pos = str.find("fasd",pos);
    pos |= str.npos;
    std::cout << "Hello, World!\n";
    
    
   

    return 0;
}
