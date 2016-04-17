//
//  main.cpp
//  test_1
//
//  Created by future on 16/4/12.
//  Copyright © 2016年 future. All rights reserved.
//

#include <iostream>
#include <cmath>


using namespace std;


int main(int argc,char* argv[]){
    double n;
    int m;
    double ret = 0.0;
    while(cin >> n >> m){
        for(int i = 0;i < m;++i){
 
            ret += n;
           n = sqrt(n);
        }
        printf("%.2f\n",ret);
        ret = 0.0;
        
    }
    
    return 0;
}