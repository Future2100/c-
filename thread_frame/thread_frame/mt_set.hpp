//
//  mt_set.hpp
//  thread_frame
//
//  Created by future on 16/3/18.
//  Copyright © 2016年 future. All rights reserved.
//

#ifndef mt_set_hpp
#define mt_set_hpp

#include <mutex>
#include <set>
#include <string>

using namespace std;


template<class T> class mt_set : virtual private mutex{
private:
    set<T,less<T>> S;
    
public:
    mt_set(void);
    mt_set(set<T,less<T>> X);
    set<T,less<T>> setUnion(set<T,less<T>> X);
    set<T,less<T>> intersection(set<T,less<T>> X);
    int membership(set<T,less<T>> X);
    set<T,less<T>> difference(set<T,less<T>> X);
};

#endif /* mt_set_hpp */
