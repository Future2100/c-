//
//  filereceiver.hpp
//  ftpclient
//
//  Created by future on 16/4/8.
//  Copyright © 2016年 future. All rights reserved.
//

#ifndef filereceiver_hpp
#define filereceiver_hpp

#include <cstdio>
#include <vector>

using std::vector;

class mysocket;

const int SLICE = 1024 * 1024 * 5;


class filereceiver{
private:

    char *mmaddr;
    int  recvport ;
    size_t  filesize;
    vector<mysocket*> recvsock;
    
public:
    filereceiver(const char *,size_t ,int);
    void recv();
    
};



#endif /* filereceiver_hpp */
