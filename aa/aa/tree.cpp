//
//  tree.cpp
//  aa
//
//  Created by future on 16/3/17.
//  Copyright © 2016年 future. All rights reserved.
//

#include <stdio.h>
#include <stack>
#include <iostream>

using namespace std;

struct  Node{
    char key;
    Node *left = nullptr,*right = nullptr;
};

class BiTree{
private:
    Node *root;
    
    
public:
    BiTree(){
        CreateTree(&root);
    }
    
    virtual ~BiTree(){
        RecoverTree(root);
    }
    
    void CreateTree(Node **root){
        char temp;
        cin >> temp;
        if( temp == '#'){
            root = nullptr;
        }else{
            Node *tnode = new Node;
            tnode->key = temp;
            *root = tnode;
            CreateTree(&(*root)->left);
            CreateTree(&(*root)->right);
        }
    }
    
    void Display(){
        PreOrder(root);
    }
    
    void RecoverTree(Node *root){
        if(root){
            RecoverTree(root->right);
            RecoverTree(root->left);
            delete root;
        }
    }
    
    void PostOrder(){
        Node *temp = root;
        stack<Node*> temps;
        while (temp) {
            temps.push(temp);
            temp = temp->left;
        }
        while (!temps.empty()) {
            Node *s = temps.top();
            temps.pop();
            cout << s->key << " ";
            if(s->right){
                Node * ss = s->right;
                while (ss) {
                    temps.push(ss);
                    ss = ss->left;
                }
            }
        }
    }
    
    int getCount(){
        return count(root);
    }
    
    
private:
    void PreOrder(Node *root){
        if(root){
            cout << root->key << " ";
            PreOrder(root->left);
            PreOrder(root->right);
        }
    }
    int count(Node *root){
        int left  = 0,right = 0;
        if(root){
            
            if(root->left){
                left =   count(root->left) + 1;
            }
            if(root->right){
                right = count(root->right)  + 1;
            }
            return right + left;
        }
        return 0;
    }


    
};


int maintree(void){
    
    
    BiTree root;
    
    //root.Display();
    root.PostOrder();
    cout << root.getCount() << endl;
    
    
    return 0;
}