//
//  main.cpp
//  c_str()
//
//  Created by future on 16/4/13.
//  Copyright © 2016年 future. All rights reserved.
//

#include <iostream>
#include <string>

using namespace std;


int* fun(int,int){
    return 0;
}

template <class T ,class U>
auto sum(T t,U u)->decltype(t + u){
    return u + t;
}

int fun1(){
    return 0;
}

struct AA{
    int a;
    double b;
    char c;
};

struct BB{
    double b;
    int a;
    short c;
    AA d;
    char e[2];
};


int main(int argc, const char * argv[]) {

//    string str = "hello world";
//    
//    const char *szStr = str.c_str();
//    cout << szStr << endl;
//    printf("%p\n",szStr);
//    str = "hasiqi";
//    cout << szStr << endl;
//    printf("%p\n",szStr);
//    int i = 0,&r = i;
//    auto &a = r;
//    cout << a << endl;
//    r = 20;
//    cout << a << endl;

    
//    
//    const int ci = 0;
//    decltype(ci) x = 0;
//
//    int a = 10,&r = a;
////     decltype(r) d = 10;
//
//    decltype(fun(10,10)) p = &a;
//    
//    int sz= fun1();
//    
//    
//     int *p2 = &sz;
    
    
    cout << sizeof( AA )<< endl;
    
    cout << sizeof (BB ) << endl;
    
    return 0;
}
