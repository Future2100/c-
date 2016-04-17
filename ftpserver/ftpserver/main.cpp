//
//  main.cpp
//  ftpserver
//
//  Created by future on 16/4/6.
//  Copyright © 2016年 future. All rights reserved.
//

#include <iostream>
#include "ftpserver.hpp"



int main(){
    
    
    
    ftpserver fserver(8888);
    fserver.run();
    
    
    return 0;
}