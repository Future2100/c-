//
//  main1.cpp
//  shared_ptr
//
//  Created by future on 16/4/13.
//  Copyright © 2016年 future. All rights reserved.
//

#include <stdio.h>
#include <iostream>

class shared {
private:
    std::shared_ptr<int> p_;
    
public:
    shared(std::shared_ptr<int>& p_):p_(p_){}
    
    void print(){
        std::cout << "counter : " <<p_.use_count() << std::endl;
    }
};

int main2(int argc,char *argv[]){
    
    std::shared_ptr<int> p(new int[10]);
    std::cout << p.use_count() << std::endl;
    shared sh(p);// 2
    sh.print();
    
    shared sh1(p);
    sh1.print();
    
    
    
    return  0;
}


