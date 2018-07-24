/*
 * Author: Xujia Ji
 * Date: 04/19/2018
 * Reference: Ke Ye(kye@stevens.edu)
 */
#include <iostream>
#include <list>
#include <fstream>
using namespace std;
class HashMapLinearChaining{
private:
    class Bucket{
    public:
        list<string> chain;
    };
    Bucket* table;
    uint32_t size;
    uint32_t hash(const string& word){
        int sum = 0;
        for(int i = 0; i < word.length();i++){
            sum = sum*26+word[i];
        }
        return sum & (size - 1);
    }

public:
    HashMapLinearChaining(uint32_t initialSize) : size(initialSize), table(new Bucket[initialSize]){

    }
    ~HashMapLinearChaining() {
        delete [] table;
    }
    bool contains(const string& word){
        uint32_t index = hash(word);
        for(auto l : table[index].chain){
            if(l == word)
                return true;
        }
        return false;
    }
    void add(string word){
        uint32_t index = hash(word);
        if(contains(word))return;
        table[index].chain.push_front(word);
    }
    void hist(){
        for(int i = 0;i<size;i++){
            cout << i << ' ' ;
            cout << table[i].chain.size() << endl;
        }
    }

};

int main() {
  ifstream words("dict.dat");
  string word;
  HashMapLinearChaining dict1(50000); // initial size
  while (!words.eof()) {
    words >> word;
    dict1.add(word); // add the word to the dictionary
  }
  dict1.hist(); // display histogram
  ifstream spell("words.dat");
  string s;
  while (!spell.eof()) {
    spell >> s;
    if (dict1.contains(s))
      cout  << s << " found!\n";
    else
      cout << s << " not found!\n";
  }
}
