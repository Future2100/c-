//
//  main2.cpp
//  shared_ptr
//
//  Created by future on 16/4/13.
//  Copyright © 2016年 future. All rights reserved.
//

#include <iostream>
#include <vector>
#include <memory>
#include <scoped_allocator>
#include <tuple>



using namespace std;

int main3(int argc,char *argv[]){
    using vs = vector<shared_ptr<int>>;
    
    vs v(10);
    int i = 0;
    for (auto beg = v.begin(); beg != v.end(); ++beg) {
        (*beg) = make_shared<int>(i++);
        cout << *beg << endl;//operator <<  equal to get()
    }
    
    cout << endl;
    shared_ptr<int> p = v[9];
    *p = 100;
    cout << *v[9] << endl;
    
    
    return 0;
}


int main23(int argc,char *argv[]){
    
//    auto aa = make_shared<int>(10);
////    shared_ptr<int> m1 = aa;
//    cout << boolalpha;
//    cout << aa.unique() << endl;
//    shared_ptr<int> m2 = aa;
//    cout << aa.unique() << endl;
//    auto_ptr<string> aa(new string("hello"));
//    auto_ptr<string> bb(aa);//aa会转让其对new string("hello")的所有权，导致aa指向null
//    
//    cout << *aa << endl;
//    cout << *bb << endl;
//    

    string str1 = "hello";
    cout << str1 << endl;
    string str2(std::move(str1));//move 构造函数
    
    
    cout << str1 << endl;
    cout << str2 << endl;
    
    
    tuple<int,string,double> tp = {2,"he",2.2};
    
    cout << get<0>(tp) << get<1>(tp) << get<2>(tp) << endl;
    
    //string &str3 = ref("hello");
    std::unique_ptr<int> p1(new int(42));
    std::unique_ptr<int> p2 = std::move(p1); // 移交unique指针
    auto sp = std::make_shared<int>(42);
    std::weak_ptr<int> wp = sp;
    {
        auto sp1 = wp.lock(); // 提升shared_ptr
        std::cout << sp.use_count() << std::endl;
    }
    sp.reset();
    
    if (wp.expired())
        std::cout << "expired" << std::endl;
    
    return 0;
}




