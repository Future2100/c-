//
//  main.cpp
//  5-2-3
//
//  Created by future on 16/4/6.
//  Copyright © 2016年 future. All rights reserved.
//

//find out all different words

#include <iostream>
#include <string>
#include <set>
#include <sstream>

using namespace std;


set<string> dict;//string 集合


int main(int argc, const char * argv[]) {
    ios::sync_with_stdio(false);//关闭和流的通报
    
    string s,buf;
    while (cin >> s) {
        for (int i = 0; i < s.length(); ++i) {
            if(isalpha(s[i])) s[i]  = tolower(s[i]);
            else s[i] = ' ';
        }
        stringstream ss(s);
        while (ss >> buf) {
            dict.insert(buf);
        }
    }
    for (auto at : dict) {
        cout << at << endl;
    }
    
    
    
    return 0;
}
