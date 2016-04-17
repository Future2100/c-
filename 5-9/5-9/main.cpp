//
//  main.cpp
//  5-9
//
//  Created by future on 16/4/16.
//  Copyright © 2016年 future. All rights reserved.
//

#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

const int maxn = 10000 + 10;
const int maxm = 10 + 10;


string data[maxn][maxm];


map<string,int> IDCache;


bool ID(string& str,int col){//直接把两者的联合体传进来 str1  + "  " + str2
    if(!IDCache.count(str)){  IDCache[str] = col;return false;}
    return true;
}


int main(int argc, const char * argv[]) {

    int m,n;

    while (cin >> m >> n) {
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; j++) {
                cin >>data[i][j];
            }
        }
        for (int i = 0; i < m - 1 ; ++i) {
            for (int j = i + 1; j < m; ++j) {
                for (int k = 0; k < n; ++k) {
                    string temp = data[k][i] + "  " + data[k][j];
                    if (ID(temp, k + 1)) {
                        cout << "col (" << i + 1 << ","<<j + 1<<")" << endl;
                        cout << "row (" << IDCache[temp] << "," << k + 1 << ")"<< endl;
                    }
                }
            }
        }
        
        
        
        
    }
    
    
    return 0;
}
