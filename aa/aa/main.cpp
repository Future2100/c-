//
//  main.cpp
//  aa
//
//  Created by future on 16/3/17.
//  Copyright © 2016年 future. All rights reserved.
//

#include <iostream>


int main1(int argc, const char * argv[]) {
  
    int n;
    std::cin >> n;
    int *arr = new int[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }
    int maxcount = 0;
    int value  = arr[0];

    int temp = 0;
    for(int i = 1 ;i < n;++i){
        if(arr[i-1] < arr[i]){
            if(temp > maxcount){
                maxcount = temp;
                value = arr[i - 1];
            }
            temp = 0;
        }else {
            temp++;
        }
    }
    std::cout << value;
    delete []arr;
    return 0;
}
