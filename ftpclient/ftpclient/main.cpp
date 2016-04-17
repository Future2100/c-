//
//  main.cpp
//  ftpclient
//
//  Created by future on 16/4/7.
//  Copyright © 2016年 future. All rights reserved.
//

#include <iostream>
#include "ftpclient.hpp"

int main(int argc, const char * argv[]) {

    std::ios::sync_with_stdio(false);
    
    ftpclient cl("127.0.0.1",8888);
    cl.myconnect();
    cl.run();
    
    return 0;
}
