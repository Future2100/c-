//
//  main.cpp
//  bit_diff
//
//  Created by future on 16/3/25.
//  Copyright © 2016年 future. All rights reserved.
//

#include <iostream>

using namespace std;


int dif(int a,int b){
    char *aa = (char*)&a, *bb = (char*)&b;
    int counter = 0;
    for(int i = 0;i < 32;++i){
        cout << aa[i] << " " << bb[i] << endl;
        if(aa[i] != bb[i])
            counter ++;
    }
    return counter;
}


int aa(){
    #include <map>
    using namespace std;
    
    
    
}


int
main(int argc, const char * argv[]) {

    
    cout << dif(7, 15) << endl;
    
    

    return 0;
}
