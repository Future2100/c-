//
//  graphlist.hpp
//  graph
//
//  Created by future on 16/3/14.
//  Copyright © 2016年 future. All rights reserved.
//

#ifndef graphlist_hpp
#define graphlist_hpp

#include <stdio.h>

struct edge{
    int veradj;
    int cost;
    edge *link;
};

struct vertex{
    char varname;
    edge *adjacent;
};

class graphlist{
private:
    vertex *header;
    int graphsize;
    
public:
    graphlist();
    virtual ~graphlist();
    
    void depthfirstsearch(int v);
    void borderfirstsearch(int v);
    void toporder(int n);
    void dshortestpath(int v);

protected:
    void dfs(int v,int *visited);
    void bfs(int v,int *visited);
};




#endif /* graphlist_hpp */
