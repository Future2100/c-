//
//  main.cpp
//  gethostbyname
//
//  Created by future on 16/3/23.
//  Copyright © 2016年 future. All rights reserved.
//

#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>

using namespace std;


int main(int argc, const char * argv[]) {

    
    struct hostent *hent = gethostbyname("uosuchname.invalid.xfdsafdksfsdkfj;s");
    if( hent == nullptr){
        cout << hstrerror(h_errno) << endl;// by  this way ,we can know details error
        //h_error is the gethostbyname function speacial has it
        cout << "gethostbyname failed!" << endl;
        exit(1);
    }
    cout << "official hostname : " << hent->h_name << endl;
    for(auto alias = hent->h_aliases;*alias;++alias){
        cout << "alias : " << *alias << endl;
    }
    char buf[128];
    switch (hent->h_addrtype) {
        case AF_INET:
            for(auto b = (hent->h_addr_list); *b != nullptr;++b){
                cout <<"addr :" << inet_ntop(hent->h_addrtype, *b, buf, sizeof( buf )) << endl;
            }
            break;
            
        default:
            break;
    }
    
    
    return 0;
}
