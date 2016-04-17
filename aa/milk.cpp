//
//  milk.cpp
//  aa
//
//  Created by future on 16/3/18.
//  Copyright © 2016年 future. All rights reserved.
//

#include <stdio.h>
#include <iostream>

using namespace std;

int mainmilk(int argc,char *argv[]){
    int n;
    cin >> n;
    int counter = n;
    while (n >= 3) {
        n =  n - 2;
        counter ++;
    }
    cout << counter << endl;
    
    return 0;
}