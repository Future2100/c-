//
//  main.cpp
//  d
//
//  Created by future on 16/3/25.
//  Copyright © 2016年 future. All rights reserved.
//

#include <iostream>
#include <vector>

bool valid[505];


void input(){
    memset(valid, 0, sizeof(valid));
    int n;
    scanf("%d",&n);
    int t;
    for (int i = 0; i < n; ++i) {
        scanf("%d",&t);
        valid[t] = true;
    }
}


const int INF = 0x7fffffff;

int offset, gap;

void CalcGap(int n, int arr[]) {
    int _max = -INF, _min = INF;
    for (int i = 0; i < n; ++i) {
        _max = std::max(_max, arr[i]);
        _min = std::min(_min, arr[i]);
    }
    offset = _min;
    gap = (_max - _min + n - 1) / n;
}

int FindBucket(int x) {
    return  (x - offset) / gap;
}

int Solve(int n, int arr[]) {
    std::vector<int> bucket_min(n, INF), bucket_max(n, -INF);
    std::vector<bool> valid(n, false);
    CalcGap(n, arr);
    int answer = 0;
    for (int i = 0; i < n; ++i) {
        int bucket_num = FindBucket(arr[i]);
        bucket_min[bucket_num] = std::min(bucket_min[bucket_num], arr[i]);
        bucket_max[bucket_num] = std::max(bucket_max[bucket_num], arr[i]);
        valid[bucket_num] = true;
    }
    for (int i = 0; i < n; ++i) {
        if (valid[i]) answer = std::max(answer, bucket_max[i] - bucket_min[i]);
    }
    int last = 0;
    for (int i = 1; i < n; ++i) {
        if (valid[i]) {
            answer = std::max(answer, bucket_min[i] - bucket_max[last]);
            last = i;
        }
    }
    return answer;
}

int main(int argc, const char * argv[]) {
    
    input();
    int answer = 0,last = 1000;
    for(int i = 2;i <= 500;++i){
        if(valid[i]){
            answer = std::max(answer, i- last);
            last = i;
        }
    }
    printf("%d",answer);
    
    
    return 0;
}
