//Author: Xujia Ji
//Data: 03/28/2018
//Reference: https://www.geeksforgeeks.org/evaluation-of-expression-tree/

#include <iostream>
#include <fstream>

using namespace std;
class node {
private:;
public:
    string info;
    node *left = nullptr, *right = nullptr;

    node(string x) {
        info = x;
    }
};
int toInt(string s) {
    int num = 0;
    for (int i = 0; i < s.length(); i++) {
        num = num * 10 + (int(s[i]) - 48);
    }
    return num;
}
int eval(node* root){
    if(!root)return 0;
    if(!root->left&&!root->right)return toInt(root->info);
    int l_val = eval(root->left);
    int r_val = eval(root->right);
    if(root->info == "+")return l_val+r_val;
    if(root->info == "-")return l_val-r_val;
    if(root->info == "-")return l_val-r_val;
    return l_val/r_val;
}


int main() {
    ifstream in;
    in.open("hw8inp.dat",ios::in);
    string line;
    node *q;
    if(in.is_open()){
        while(!in.eof()){
            getline(in,line);
            q = new node(line);
            cout<<line<<" is equal to "<<eval(q)<<endl;
        }
    }
    return 0;
}
