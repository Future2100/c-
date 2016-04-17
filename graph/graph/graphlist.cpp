//
//  graphlist.cpp
//  graph
//
//  Created by future on 16/3/14.
//  Copyright © 2016年 future. All rights reserved.
//

#include "graphlist.hpp"
#include <iostream>


using namespace std;


graphlist::graphlist(){
    cout << "plese input vertex counter :";
    cin >> graphsize;
    header = new vertex[graphsize];
    for(int i = 0; i < graphsize ;++i){
        cout << "please input vertex name(char): "<<endl;
        cin >> header[i].varname;
        header[i].adjacent = nullptr;
    }
    
    int e,from,to,weight;
    cout << "please input edge counter : ";
    cin >> e;
    for(int i = 0; i < e;++i){
        cin >> from >> to >> weight;
        edge * temp = new edge;
        temp->link = nullptr;
        temp->veradj = to;
        temp->cost = weight;
        edge * tempheader= header[from].adjacent;
        if(!tempheader){
            header[from].adjacent = temp;
        }
        else {
            while (tempheader->link) {
                tempheader = tempheader->link;
            }
            tempheader->link = temp;
        }
        
    }
}

graphlist::~graphlist(){//析构函数中释放内存
    for(int i = 0; i < graphsize ;++i){
        edge *p = header->adjacent;
        while (p) {
            header[i].adjacent = p->link;
            delete p;
            p = header[i].adjacent;
        }
    }
    delete []header;
}

#include <stack>

using std::stack;

void graphlist::dfs(int v,int *visited){//visited need to initialize

    stack<int> s;
    s.push(v);
    visited[v] = 1;
    while(!s.empty())
    {
        int temp = s.top();
        s.pop();
        cout << header[temp].varname << " ";

        edge *e = header[temp].adjacent;
        while (e ){
            if(visited[e->veradj] == 0){
                s.push(e->veradj);
                visited[e->veradj] = 1;
            }
            e = e->link;
        }
    }
}

/*
 
 plese input vertex counter :7
 please input vertex name(char):
 A
 please input vertex name(char):
 B
 please input vertex name(char):
 C
 please input vertex name(char):
 D
 please input vertex name(char):
 E
 please input vertex name(char):
 F
 please input vertex name(char):
 G
 please input edge counter : 9
 
 0 1 2
 1 2 3
 2 3 4
 2 4 4
 3 4 2
 4 5 1
 0 6 1
 6 5 2
 5 0 2*/
#include <queue>
using std::queue;

void graphlist::bfs(int v, int *visited){
    queue<int> q;
    q.push(v);
    visited[v] = 1;
    while (!q.empty()) {
        int var = q.front();
        q.pop();
        cout << header[var].varname << " ";
        edge *tempe = header[var].adjacent;
        while (tempe) {
            if(visited[tempe->veradj] == 0){
                q.push(tempe->veradj);
                visited[tempe->veradj] = 1;
            }
            tempe = tempe->link;
        }
    }
}


void graphlist::depthfirstsearch(int v){
    cout << "depthfirstsearch : "<<endl;
    int *visited = new int[graphsize];
    memset(visited,0,sizeof(int)*graphsize);
    for (int i = 0; i < graphsize;++ i) {
        if(visited[i] == 0){
            dfs(i, visited);
        }
    }
    cout << endl;
    delete []visited;
}
void graphlist::borderfirstsearch(int v){
    cout << "borderfirstsearch :" << endl;
    int *visited = new int[graphsize];
    memset(visited,0,sizeof(int)*graphsize);
    for (int i = 0; i < graphsize;++ i) {
        if(visited[i] == 0){
            bfs(i, visited);
        }
    }
    cout << endl;
    delete []visited;
}


void graphlist::toporder(int n){
    
    int *count = new int[graphsize];
    memset(count,0,sizeof(int)*graphsize);
    for(int i = 0 ; i < graphsize;++i){//计算每个顶点的入度，在O（n+e）复杂度内完成的
        edge *tempe = header[i].adjacent;
        while (tempe) {
            count[tempe->veradj] = count[tempe->veradj] + 1;
            tempe = tempe->link;
        }
    }
    int top = -1;
    for(int i = 0;i < graphsize;++i){
        if(count[i] == 0){
            count[i] = top;
            top = i;
        }
    }
    //--------------------begin toporder-----------------------------------------
    for(int i = 0; i < graphsize ; ++ i){
        if(top == -1){//如果有环的存在，那么将没有count == 0，所以top不变，还是-1
            cout << "there is a cycle in network" << endl;
            return ;
        }
        else {
            int j = top;
            top = count[top];
            cout << header[j].varname << " ";
            edge *temp = header[j].adjacent;
            while (temp) {
                int k = temp->veradj;
                count[k] = count[k] - 1;
                if(count[k] == 0){//如果入度为0，那么加入桟中，只要是入度为0的点都是可以马上输出的
                    count[k] = top;
                    top = k;
                }
                temp = temp->link;
            }
        }
    }
    
    delete [] count;
    
}

#define MAX 0x1000

void graphlist::dshortestpath(int v){
    cout << "dshortestpath" << endl;
    int path[graphsize];
    int s[graphsize];
    int dist[graphsize];
    for(int i = 0;i < graphsize;++i){
        path[i] = -1;//路径
        s[i] = 0;//记录是否被访问过
        dist[i] = MAX;
    }
    dist[v] = 0;
    s[v] = 1;
    edge* p = header[v].adjacent;
    int u = v;
    for(int i = 0; i < graphsize -1;++i){
        while(p){
            int k = p->veradj;
            int ret = (s[k] != 1 && ((dist[u] + p->cost) < dist[k]));
            if(ret){//如果发现比当前小的dist，更新
                dist[k] = dist[u] + p->cost;
                path[k] = u;
            }
            p = p->link;
        }
        int ldist = MAX;
        for(int j = 0;j < graphsize ; ++j){
            if(dist[j] > 0 && dist[j] < ldist && s[j] == 0){
                ldist = dist[j];
                u = j;
            }
        }
        s[u] = 1;
        cout << "vertex\t\t" << "path"<<endl;
        cout << header[u].varname << "\t\t\t" << path[u] + 1 << endl;
        p = header[u].adjacent;
    }
    cout << endl;
}

/*
 6
 please input edge counter : 10
 0 1 12
 0 2 5
 0 3 8
 1 2 5
 2 3 6
 1 4 20
 2 4 10
 2 5 8
 3 5 4
 4 5 9

*/