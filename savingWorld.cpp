#include <iostream>
#include <algorithm>
#include <string.h>


using namespace std;


int main() {
    int t;
    int count = 0;
    cin >> t;
    int d;
    string p;
    cout << endl;
    for (int i = 1; i <= t; i++) {
        count = 0;
        int total = 0;
        int current = 1;
        cin >> d >> p;
        for (char k: p) {
            if (k == 'C') {
                current *= 2;
            } else {
                total += current;
            }
        }
        if (total <= d) {
            cout << "Case #" << i << ": " << 0 << endl;
        } else {
            bool flag = true;
            while (flag) {
                if (p.back() == 'C') {
                    p.pop_back();
                    continue;
                }
                if (p.find('C') == -1) {
                    flag = false;
                    break;
                }
                int index = p.find_last_of('C');
                std::swap(p[index], p[index + 1]);
                count++;
                int total = 0;
                int current = 1;
                for (char k: p) {
                    if (k == 'C') {
                        current *= 2;
                    } else {
                        total += current;
                    }
                }
                if (total <= d) {
                    break;
                }
            }
            if(flag){
                cout << "Case #" << i << ": " << count<< endl;
            }else{
                cout << "Case #" << i << ": " << "IMPOSSIBLE"<< endl;
            }
        }


    }
}