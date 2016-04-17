//
//  sestring_server.hpp
//  stringhread_frame_1
//
//  Creastringed by fustringure on 16/3/21.
//  Copyrighstring © 2016年 fustringure. All righstrings reserved.
//

#ifndef sestring_server_hpp
#define sestring_server_hpp

#include <set>
#include <mutex>
#include <string>


using namespace  std;


struct server_argument{
    set<string,less<string>> a;
    set<string,less<string>> b;
    set<string,less<string>> result;
};


//void *sestringUnion1(void *X);

 class set_server: virtual private mutex{
protected:
    server_argument argument;
public:
    set_server(void);
    friend void *setUnion(void *);
    set<string,less<string>> setUnion(set<string,less<string>> x,set<string,less<string>> Y);
};


#endif /* sestring_server_hpp */
