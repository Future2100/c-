//
//  mt_set.cpp
//  thread_frame_1
//
//  Created by future on 16/3/21.
//  Copyright © 2016年 future. All rights reserved.
//


#include "mt_set.hpp"
#include <algorithm>
#include <string>

using namespace std;



mt_set::mt_set(void){

}

mt_set::mt_set(set<string,less<string>> x){
    s = x;
}


set<string,less<string>> mt_set::intersection(set<string, less<string>> X){
    set<string,less<string>> Temp;
    less<string> Order;
    lock();
    set_intersection(s.begin(), s.end(), X.begin(), X.end(), inserter(Temp, Temp.begin()),Order);
    unlock();
    return Temp;
}

 set<string,less<string>>
mt_set::setUnion(set<string,less<string>> X){
    less<string> Order;
    set<string,less<string>> Temp;
    lock();
    set_union(s.begin(), s.end(), X.begin(), X.end(), inserter(Temp, Temp.begin()), Order);
    unlock();
    return Temp;
}


int
mt_set::membership(set<string,less<string>> X){
    return includes(s.begin(), s.end(), X.begin(), X.end());
}


set<string,less<string>>
mt_set::difference(set<string, less<string> > X){
    set<string,less<string>> Temp;
    less<string> Order;
    lock();
    set_difference(s.begin(), s.end(), X.begin(),X.end(), inserter(Temp, Temp.begin()), Order);
    unlock();
    return Temp;
}
