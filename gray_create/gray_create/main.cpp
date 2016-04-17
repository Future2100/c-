//
//  main.cpp
//  gray_create
//
//  Created by future on 16/3/28.
//  Copyright © 2016年 future. All rights reserved.
//

#include <iostream>
#include <vector>


std::vector<int> gray_create(int n){
    std::vector<int> vc;
    vc.clear();
    for(int i  = 0; i < (1 << n) ;++i){
        vc.push_back(i^(i >> 1));
    }
    return vc;
}



int main_gray(int argc, const char * argv[]) {

    std::vector<int> res = gray_create(10);
    for(auto au : res){
        std::cout << au << std::endl;
    }
    
    
    
    return 0;
}

#include <fstream>
int mainfd(){
    //printf("%d\n",8.0 / 5.0);
//    freopen("aa.in", "r", stdin);//0.006257000000000000408673
//    freopen("aa.out", "w", stdout);
//    
//    int a;
//    while (scanf("%d", &a) == 1) {
//        printf("%d",a);
//    }
    std::ifstream fin("aa.in");
    std::ofstream fout("aa.out");
    
    std::cin.rdbuf(fin.rdbuf());
    std::cout.rdbuf(fout.rdbuf());
    int a;
    while (std::cin >> a) {
        std::cout << a;
    }

    
    printf("%.24f\r\n",(double)clock()/CLOCKS_PER_SEC);
    
    return 0;
    
}


int mainhanxin(){
    
//    double i;
//    for (i = 0; i != 10; i += 0.1) {
//        printf("%.11f\r",i);
//    }

    int a,b,c;// a 3 b 5 c 7
    std::cin >> a>> b >> c;
    int i;
    for ( i = 10; i < 100; ++i) {
        int e = (i -a) % 3;
        int f = (i-b) % 5;
        int g = (i- c) % 7;
        //std::cout << e << f << g << std::endl;
        if(e == 0 && f == 0 && g == 0)
            std::cout << i << std::endl;
    }
    if( i== 100)
        std::cout << "No answer" << std::endl;
    
    
    return 0;
}


int mainh(){
    int n;
    double res = 1.0;
    std::cin >> n;
    for (int i = 2; i <= n; ++i) {
        res += 1.0 / i;
    }
    printf("%.3f",res);
    return  0;
}


int main(){
    double i = 3.0;
    double res = 1.0;
    int flag = -1;
    for (;(1.0/ i) < 0.000001 ; i += 2.0) {
        res += (1.0 / i)*flag;
        std::cout << res << std::endl;
        
        flag = -flag;
    }
    printf("%.11f\n",res);
    
    return 0;
}