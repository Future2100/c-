//
//  mt_set.cpp
//  thread_frame
//
//  Created by future on 16/3/18.
//  Copyright © 2016年 future. All rights reserved.
//



#include "mt_set.hpp"
#include <algorithm>
#include <string>

using namespace std;


//template<class T>
//mt_set<T>::mt_set(void){
//    S = nullptr;
//}
template<class T>
mt_set<T>::mt_set(set<T,less<T>> X){
    S = X;
}

template<class T> set<T,less<T>>
mt_set<T>::intersection(set<T, less<T> > X){
    set<T,less<T>> Temp;
    less<T> Order;
    lock();
    set_intersection(S.begin(), S.end(), X.begin(), X.end(), inserter(Temp, Temp.begin()),Order);
    unlock();
    return Temp;
}

template<class T> set<T,less<T>>
mt_set<T>::setUnion(set<T,less<T>> X){
    less<T> Order;
    set<T,less<T>> Temp;
    lock();
    set_union(S.begin(), S.end(), X.begin(), X.end(), inserter(Temp, Temp.begin()), Order);
    unlock();
    return Temp;
}


template<class T> int
mt_set<T>::membership(set<T,less<T>> X){
    return includes(S.begin(), S.end(), X.begin(), X.end());
}


template<class T> set<T,less<T>>
mt_set<T>::difference(set<T, less<T> > X){
    set<T,less<T>> Temp;
    less<T> Order;
    lock();
    set_difference(S.begin(), S.end(), X.begin(),X.end(), inserter(Temp, Temp.begin()), Order);
    unlock();
    return Temp;
}