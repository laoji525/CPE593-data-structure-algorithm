/*
 * Author: Xujia Ji
 * Date: 04/19/2018
 * Reference:
 * Thomas Wang, integer hash function, http://burtleburtle.net/bob/hash/integer.html
 * Ke Ye(kye@stevens.edu)
 */

#include <iostream>
#include <map>

using namespace std;
class HashMapLinearProbing {
private:
    class Bucket {
    public:
        string key;
        int val;
        bool present;

        Bucket() : key(), present(false) {}
    };

    Bucket *table;
    uint32_t size;
    uint32_t used;

    uint32_t hash(uint32_t a) {
        a = (a ^ 61) ^ (a >> 16);
        a = a + (a << 3);
        a = a ^ (a >> 4);
        a = a * 0x27d4eb2d;
        a = a ^ (a >> 15);
        return a & (size - 1);
    }
    map<int ,int> collision;

    void grow(){
        Bucket* old = table;
        table = new Bucket[2*size];
        for(uint32_t i = 0;i<size;++i)
            if(old[i].key != "")
                table[hash(old[i].val)] = old[i];
        delete [] old;
        for(int i = size; i < size * 2; i++)
            collision[i] = 0;
        collision[0] += size;
        size = 2*size;
    }

public:
    HashMapLinearProbing(uint32_t initialSize) : size(initialSize), used(0){
        table = new Bucket[initialSize];
        collision[0] = size;
        for(int i = 1; i < initialSize; i++)
            collision[i] = 0;
    }
    ~HashMapLinearProbing(){
        delete [] table;
    }
    void add(int n){
        if(2*used >= size)grow();
        used++;
        uint32_t temp = hash(n);
        int c = 1;
        while(table[temp].present){
            temp++;
            c++;
            if(temp == size)temp = 0;
        }
        table[temp].val = n;
        table[temp].present = true;
        collision[c]++;
        collision[0]--;

    }
    void displayHistogram() {
        for(auto c:collision){
            cout<<c.first<<" "<<c.second<<endl;
        }
    }
};

int main() {

    int n;
    cout<<"enter: ";
    cin>>n;
    HashMapLinearProbing a(n);
    for(int i = 0; i<n;i++){
        a.add(i);
    }
    cout<<endl;
    a.displayHistogram();
    return 0;
}