//
//  queen.cpp
//  aa
//
//  Created by future on 16/3/17.
//  Copyright © 2016年 future. All rights reserved.
//

#include <stdio.h>
#include <cmath>
#include <cstdlib>
#include <iostream>


using namespace std;

bool canPlace(int queenInRow[] ,int k,int i,int n){
    for (int j = 0; j < k; j++) {
        if((queenInRow[j] == i) || abs(queenInRow[j] -i) == abs(j-k)){
            return false;
        }
    }
    return true;
}

void PrintResult(int *arr,int n){
    for (int i  = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void nQueens(int queenInRow[],int k,int n){
    for (int i = 0; i < n; ++i) {
        if(canPlace(queenInRow, k, i, n)){
            queenInRow[k] = i;
            if( k == n - 1){
                PrintResult(queenInRow,n);
            }
            else{
                nQueens(queenInRow, k + 1, n);
            }
        }
    }
}


int mainqueen(int argc,char *argv[]){
    int n;
    cin >> n;
    int *queenInRow = new int[n];
    nQueens(queenInRow, 0, n);
    delete []queenInRow;
    return 0;
}