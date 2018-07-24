/*
 * Author: Xujia Ji
 * Data: 03/28/2018
*/
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Trie {
private:
    class Node {
    public:
        Node *next[26];
        bool isWord;
        string content;


    };

    Node *root;
public:


    Trie() {
        root = new Node();
    }

    ~Trie() {
        deleteD(root);
    }

    void insert(string word) {
        Node *p = root;
        for (int i = 0; i < word.length(); i++) {
            int k = word[i] - 'a';
            if (p->next[k] == nullptr) {
                p->next[k] = new Node();
            }
            p = p->next[k];
        }
        p->isWord = true;
        p->content = word;
    }

    bool contains(string word) {
        Node *p = root;
        for (int i = 0; i < word.length(); i++) {
            int index = word[i] - 'a';
            if (p->next[index] == nullptr) {
                return false;
            }
            p = p->next[index];
        }
        return p->isWord;
    }

    bool containsPrefix(string prefix) {
        Node *p = root;
        for (int i = 0; i < prefix.length(); i++) {
            int index = prefix[i] - 'a';
            if (p->next[index] == nullptr) {
                return false;
            }
            p = p->next[index];
        }
        return true;
    }

    void deleteD(Node *root) {
        for (int i = 0; i < 26; i++) {
            if (root->next[i] != nullptr) {
                deleteD(root->next[i]);
            }
        }
        delete root;
    }
};



int main() {
    Trie dictTrie;
    ifstream infile("dict.txt");
    std::string word;
    if (infile.is_open()) {
        while (!infile.eof()) {
            getline(infile, word);
            dictTrie.insert(word);
        }
    }
    infile.close();


    ifstream file2;
    file2.open("hw5.txt",ios::in);
    std::string word2;
    if(file2.is_open()){
        while(!file2.eof()){
            getline(file2,word2);
            cout<<word2<<" "<<dictTrie.contains(word2)<<endl;
        }
    }
    file2.close();
    std::string p;
    cout<<"enter a prefix:  ";
    cin>>p;
    cout<<endl;
    if(dictTrie.containsPrefix(p)){
        cout<<"Dictionary contains prefix "<<p<<endl;
    } else{
        cout<<"Dictionary does not contain prefix "<<p<<endl;
    }


}