//
//  dice.cpp
//  aa
//
//  Created by future on 16/3/18.
//  Copyright © 2016年 future. All rights reserved.
//


/*
 赌圣atm晚年迷恋上了垒骰子，就是把骰子一个垒在另一个上边，不能歪歪扭扭，要垒成方柱体。
 经过长期观察，atm 发现了稳定骰子的奥秘：有些数字的面贴着会互相排斥！
 我们先来规范一下骰子：1 的对面是 4，2 的对面是 5，3 的对面是 6。
 假设有 m 组互斥现象，每组中的那两个数字的面紧贴在一起，骰子就不能稳定的垒起来。
 atm想计算一下有多少种不同的可能的垒骰子方式。
 两种垒骰子方式相同，当且仅当这两种方式中对应高度的骰子的对应数字的朝向都相同。
 由于方案数可能过多，请输出模 10^9 + 7 的结果。
 
 不要小看了 atm 的骰子数量哦～
 
 「输入格式」
 第一行两个整数 n m
 n表示骰子数目
 接下来 m 行，每行两个整数 a b ，表示 a 和 b 数字不能紧贴在一起。
 
 「输出格式」
 一行一个数，表示答案模 10^9 + 7 的结果。
 
 「样例输入」
 2 1
 1 2
 
 */


#include <iostream>
#include <map>

using namespace  std;



long counter(int n ,int j ,map<int,int> &mymap){
    if( n == 1){
        return 4;
    }
    else
    for (int i = 1; i < 7; ++i) {
        if(mymap.find((j>3?(j-3):(j)))->second != i ){
            return 20*counter(n-1, i , mymap);
        }
    }
    return 0;
}




int main(int argc,char *argv[]){
    int n,m;
    cin >> n >> m;
    map<int,int> mymap;
    int tempkey,tempvalue;
    for (int i = 0; i < m ; ++i) {
        cin >> tempkey >> tempvalue;
        mymap.insert(map<int,int>::value_type(tempkey,tempvalue));
    }
    long temp;
    for (int i = 0;i < 6; ++i) {
        temp += counter(n, i+ 1, mymap);
    }
    cout << temp << endl;
    
    
    
    return  0;
}
