//
//  main.cpp
//  ftpserver
//
//  Created by future on 16/4/6.
//  Copyright © 2016年 future. All rights reserved.
//


#include "ftpserver.hpp"
#include <cmath>



using namespace std;



int main(){
    std::ios::sync_with_stdio(false);
    ftpserver fserver("127.0.0.1",8888);
    fserver.run();


    
  
   
    
    
    return 0;
}