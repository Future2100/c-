//
//  main.cpp
//  heap_sort
//
//  Created by future on 16/4/13.
//  Copyright © 2016年 future. All rights reserved.
//

#include <iostream>


using namespace std;

void FindMaxInHeap(int arr[], const int size) {
    for (int j = size - 1; j > 0; --j) {
        int parent = j / 2;
        int child = j;
        if (j < size - 1 && arr[j] < arr[j+1]) {
            ++child;
        }
        if (arr[child] > arr[parent]) {
            int tmp = arr[child];
            arr[child] = arr[parent];
            arr[parent] = tmp;
        }
    }
}

void HeapSort(int arr[], const int size) {
    for (int j = size; j > 0; --j) {
        FindMaxInHeap(arr, j);
        int tmp = arr[0];
        arr[0] = arr[j - 1];
        arr[j - 1] = tmp;
    }
}

int main(int argc, const char * argv[]) {
    int arr[] = {2, 5, 3, 2, 3, 0, 8, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    HeapSort(arr, n);
    for (int j = 0; j < n; ++j) {
        cout << arr[j] << ", ";
    }
    cout << endl;       return 0;
}
