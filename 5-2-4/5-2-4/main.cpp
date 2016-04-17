//
//  main.cpp
//  5-2-4
//
//  Created by future on 16/4/6.
//  Copyright © 2016年 future. All rights reserved.
//



//Ananagrams


#include <iostream>
#include <map>
#include <cctype>
#include <string>
#include <vector>
#include <algorithm>


using namespace std;



map<string,int> cnt;
vector<string> words;

string repr(const string &s){
    string ans = s;
    for (int i = 0; i < ans.length(); ++i) {
        ans[i] = tolower(ans[i]);
    }
    sort(ans.begin(), ans.end());
    return ans;//将字符串标准化，就不同在意他的顺序了，只在意他的元素是否相同和个数是否相等
}

int main(int argc, const char * argv[]) {
    string s;
    while(cin >> s){
        if(s[0] == '#')break;
        words.push_back(s);
        string r = repr(s);
        if(!cnt.count(r)) cnt[r] = 0;
        cnt[r]++;
    }
    vector<string> ans;
    for (int i = 0; i < words.size(); ++i) {
        if(cnt[repr(words[i])] == 1)  ans.push_back(words[i]);
    }
    sort(ans.begin(), ans.end());
    for(auto a : ans)
        cout << a << "\n";

    return 0;
}
