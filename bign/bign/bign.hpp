//
//  bign.cpp
//  bign
//
//  Created by future on 16/3/30.
//  Copyright © 2016年 future. All rights reserved.
//
#ifndef __bign__header___
#define __bign__header___


#include <iostream>
#include <string>

using namespace  std;

const int maxn = 1000;
struct bign{
    int x[maxn];
    size_t len;
    bign(){
        memset(x, 0, sizeof(x));
        len = 1;
    }
    
    bign(int num){
        *this = num;
    }
    
    bign(const char *str){
        *this = str;
    }
    
   bign operator =(const char *num ){
        len = strlen(num);
        for(int i = 0;i < len;++i)
            x[len - i -1] = num[i] - '0';
        return *this;
    }
    
    bign operator=(const int num){
        char buf[maxn];
        sprintf(buf, "%d",num);
        *this = buf;
        return *this;
    }
    
    string str()const {
        string res;
        for(int  i = 0;i <len;++i)
            res = (char)(x[i] + '0') + res;
        if( res == "")
            res = "0";
        return res;
    }
    
    bign operator + (const bign &b) const{        
        bign c;
        c.len = 0;
        for(int i =0,g = 0;g  || i < max(len,b.len);++i){
            if(i < len) g += x[i];
            if(i < b.len) g+= b.x[i];
            c.x[c.len++] = g % 10;
            g /= 10;
        }
        
        return c;
    }
    bign operator *(const bign &b) const{
        bign c;
        c.len = len + b.len;
        for(int i = 0;i < len;++i){
            for(int  j = 0; j < b.len;++j){
                c.x[i + j] += x[i] * b.x[j];
            }

        }
        for(int i = 0;i < c.len;++i){
            if(c.x[i] % 10)
                c.x[i + 1] += c.x[i] / 10,c.x[i] = c.x[i] % 10;
        }
        if( c.x[c.len -1] == 0)
            c.len--;
        return c;
    }
    
    int& operator[](int num){
        return this->x[num];
    }
    int operator[](int num) const{
        return this->x[num];
    }
    
//    bign operator -(const bign &b) const {
//        bign c;
//        c.len= max(len,b.len);
//        for(int i = 0;i < min(len,b.len);++i){
//            c[i] = x[i] - b[i];
//        }
//        for(int i = 0 ;i < c.len;++i){
//            if(c[i] < 0)
//                c[i + 1] -= 1,c[i] = -c[i];
//        }
//        return c;
//    }
    
    bign operator += (const bign &b) {
        *this = *this + b;
        return *this;
    }
    
    bool operator < (const bign &b)const{
        if(len != b.len) return len < b.len;
        for(int i = (int)len -1; i >= 0;--i)
            if(x[i] != b.x[i])
                return x[i] < b.x[i];
        return false;
    }
    bool operator > (const bign &b)const {
        return b < *this;
    }
    bool operator <= (const bign &b) const{
        return !(b < *this);
    }
    bool operator >= (const bign &b) const{
        return !(*this < b);
    }
    bool operator != (const bign &b) const {
        return  b < *this || *this > b;
    }
    bool operator == (const bign &b) const {
        return !(b <*this) && !(*this < b);
    }
    
    
};

ostream& operator<< (ostream &out,const     bign& x){
    out << x.str();
    return out;
}


istream& operator >> (istream &in , bign  &x){
    string str;
    in >> str;
    x = str.c_str();
    return in;
}


#endif


