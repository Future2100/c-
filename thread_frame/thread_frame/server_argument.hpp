//
//  server_argument.h
//  thread_frame
//
//  Created by future on 16/3/21.
//  Copyright © 2016年 future. All rights reserved.
//

#ifndef server_argument_h
#define server_argument_h


#include <set>
#include <iostream>

#include "mt_set.hpp"
#include "ct_thread.hpp"

using namespace std;


template<class T> struct server_argument{
    set<T,less<T>> A;
    set<T,less<T>> B;
    set<T,less<T>> Result;
};


extern void *setUnion(void *X);

template<class T> class set_server: virtual private mutex{
protected:
    server_argument<T> Argument;
public:
    set_server(void);
    //friend void *intersection(void *X);
    friend void *setUnion(void *X);
    //friend void *difference(void *X);
    // friend void *membership(void *X);
    //set<T,less<T>> intersect(set<T,less<T>> X,set<T,less<T>> Y);
    set<T,less<T>> setUnion(set<T,less<T>> x,set<T,less<T>> Y);
    //set<T,less<T>> difference(set<T,less<T>> X,set<T,less<T>> Y);
    //int membership(set<T,less<T>> X,set<T,less<T>> Y);
};




template<class T>
set_server<T>::set_server(){
    
}


void *setUnion(void *X){
    set_server<string> *Server;
    Server = static_cast<set_server<string>*>(X);
    mt_set<string> SafeSet(Server->Argument.A);
    Server->Argument.Result = SafeSet.setUnion(Server->Argument.B);
    return nullptr;
}


template<class T>
set<T,less<T>> set_server<T>::setUnion(set<T,less<T>> X,set<T,less<T>> Y){
    lock();
    ct_thread thread;
    Argument.A = X;
    Argument.B = Y;
    thread.begin(::setUnion, this);
    thread.wait();
    unlock();
    return Argument.Result;
}








#endif /* server_argument_h */
