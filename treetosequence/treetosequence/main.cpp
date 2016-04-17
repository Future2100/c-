//
//  main.cpp
//  treetosequence
//
//  Created by future on 16/4/17.
//  Copyright © 2016年 future. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;


 struct TreeNode {
 int val;
 struct TreeNode *left;
 struct TreeNode *right;
 TreeNode(int x) :
 val(x), left(NULL), right(NULL) {
 }
 };

class TreeToSequence {
public:
    static string toSequence(TreeNode* root) {
        // write code here
        string str ;
        if(root){
            str += "(";
            if(root->left)
                str += toSequence(root->left);
            if(root->right)
                str += toSequence(root->right);
            str += ")";
        }
        return str;
    }
};

int findMaxDivision(vector<int> A, int n) {
    int tong[500];
    memset(tong,0,sizeof(tong));
    for(int i = 0;i < n;++i)
        tong[A[i]] = 1;
    int max = -1, j = 0;
    for(int i = 2;i < 500;++i){
        if(tong[i] == 1 && (i - j) > max){
            max = i - j;
            j = i;
        }
    }
    return max;
}


vector<vector<int> > rotateMatrix(vector<vector<int> > mat, int n) {
    // write code here
    vector<vector<int> > ret;
    ret.resize(n);
    for (int i = 0; i < n; ++i) {
        ret[i].resize(n);
    }
    for(int i = 0;i < n;++i)
        for(int j = n -1;j >= 0;--j){
            ret[i][n - j - 1] = mat[j][i];
        }
    return ret;
}

int main(int argc, const char * argv[]) {

    
    vector<vector<int>> vc(3);
    for (int i = 0; i < 3; ++i) {
        vc[i].resize(3);
    }
    int counter = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; ++j) {
            vc[i][j] = counter++;
        }
    }
    
    vc = rotateMatrix(vc,3);
    
    
    
    return 0;
}
