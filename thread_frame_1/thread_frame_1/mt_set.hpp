//
//  mt_set.hpp
//  thread_frame_1
//
//  Created by future on 16/3/21.
//  Copyright © 2016年 future. All rights reserved.
//

#ifndef mt_set_hpp
#define mt_set_hpp

#include <mutex>
#include <set>
#include <string>

using namespace std;


class mt_set : virtual private mutex{
private:
    set<string,less<string>> s;
    
public:
    mt_set(void);
    mt_set(set<string,less<string>> X);
    set<string,less<string>> setUnion(set<string,less<string>> X);
    set<string,less<string>> intersection(set<string,less<string>> X);
    int membership(set<string,less<string>> X);
    set<string,less<string>> difference(set<string,less<string>> X);
};


#endif /* mt_set_hpp */
