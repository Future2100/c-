//
//  unordered_map.cpp
//  map
//
//  Created by future on 16/3/26.
//  Copyright © 2016年 future. All rights reserved.
//

#include <iostream>
#include <unordered_map>
#include <string>


int main(int argc,char *argv[]){
    
    std::unordered_map<std::string, int > umap = {{"mm",23},
        {"futh",22},{"dad",40}};
    std::string str;
    std::cout << "find who?" << std::endl;
    std::cin >> str;
    auto it = umap.find(str);
    
    if(it != umap.end()){
        std::cout << it->second << std::endl;
        it ++;
        std::cout << it->second << std::endl;
    } else {
        std::cout << "not found" << std::endl;
    }
    for(auto a : umap){
        std::cout << a.first << "==>" << a.second << std::endl;
    }
    
    
    return  0;
}



