//
//  main.cpp
//  map
//
//  Created by future on 16/3/26.
//  Copyright © 2016年 future. All rights reserved.
//

#include <iostream>
#include <map>
#include <algorithm>


int mainmap(int argc, const char * argv[]) {
    
    std::map<char,int> testmap;
    testmap.insert(std::pair<char, int>('a',1000));
    testmap.insert(std::map<char, int>::value_type('c',3000));//map is a ordered container
    testmap['b'] = 2000;
    
    
    std::pair<std::map<char,int>::iterator,bool> ret =   testmap.insert(std::pair<char , int>('c',4000));
    if(ret.second == false){
        std::cout << "the value :" << ret.first->first << "has allready existed" << std::endl;
    }
    
    for (auto it = testmap.begin(); it != testmap.end(); ++it) {
        std::cout << it->first << "--->" << it->second << std::endl;
    }
    for_each(testmap.begin(),testmap.end(),[](std::map<char,int>::value_type a){//_f(*first)
        std::cout << a.first << "-->" << a.second << std::endl;
    });

    
    //----------------find ----------------------------------
    std::map<char,int>::iterator findret = testmap.find('a');
    if( findret == testmap.end()){
        std::cout << "not found" <<std::endl;
    }else {
        std::cout << findret->first << "---->" << findret->second << std::endl;
     }
    
    
    std::map<char,int>::mapped_type a =  testmap['i'];//if not this key will return 0
    std::cout << a << std::endl;
    
    
    //----------------------------erese
    
    testmap.erase(testmap.find('c'));
    testmap['a'] = 500;//if the key is existed ,then the value will be updated
    std::cout << testmap['a'] <<std::endl;
    
    
    
    return 0;
}
