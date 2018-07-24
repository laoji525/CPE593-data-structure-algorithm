/*
 * Xujia Ji(xji2@stevens.edu)
 * Ke Ye(kye@stevens.edu)
 */
#include <iostream>
#include <math.h>
#include <map>
#include <time.h>

using namespace std;


bool isPrime(int n) {
    for (int i = 3; i <= sqrt(n); i+=2) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

bool sumIsPrime(int n) {
    map<int, bool> a;
    a[2] = true;
    a[3] = true;
    a[5] = true;
    a[7] = true;
    a[11] = true;
    a[13] = true;
    a[17] = true;
    a[19] = true;
    a[23] = true;
    a[29] = true;
    a[31] = true;
    a[37] = true;
    a[41] = true;
    a[43] = true;
    a[47] = true;
    a[53] = true;
    a[59] = true;
    a[61] = true;
    a[71] = true;
    a[73] = true;
    a[79] = true;
    a[83] = true;
    a[89] = true;
    a[97] = true;
    a[101] = true;
    a[103] = true;
    a[107] = true;
    a[109] = true;
    a[113] = true;
    a[127] = true;
    a[131] = true;
    a[137] = true;
    a[139] = true;
    int sum = 0;
    while (n > 0) {
        sum = sum + n % 10;
        n = n / 10;
    }
    return a[sum];
}


bool NotHasTwo(int n) {
    while (n > 0) {
        if (n % 10 == 2) {
            return false;
        }
        n = n / 10;
    }
    return true;
}

int left_index(long& start) {
    int num = start;
    int index = -1;
    int index_temp = 0;
    while (num != 0) {
        if (num % 10 == 2) {
            index = index_temp;
            index_temp++;
        } else index_temp++;
        num /= 10;
    }

    if(index == 0){
        if(start / 10 % 10 == 1){
            int temp = start % 30;
            if(temp > 17 && 37 - temp >= 8)
                start += 25;
            else start += 5;
        }
        else{
            start += 5;
        }
    }
    else if(index >= 1){
        long diff = pow(10, index);
        start += diff - start % diff;
    }
    return index;

}

int wheel(long& start){
    int index = start % 30;
    if (index <= 7) {
        start += 7 - index;
        return 0;
    } else if (index <= 17) {
        start += 17 - index;
        return 1;
    } else {
        start += 37 - index;
        return 0;
    }
}




int init_start(long &start) {
    left_index(start);
    return wheel(start);
}

void modify_start(long& start, int inc, int& flag){
    if((start + inc) / 100 % 10 == (start / 100 % 10)){
        start += inc;
        if(inc == 10) flag = 1;
        else flag = 0;
        if(start / 10 % 10 == 2){
            if(inc == 10) {
                start += 20;
                flag = 0;

            }
            else {
                start += 10;
                flag = 1;
            }
        }
    }
    else{
//        start += inc;
        int temp = start / 100 % 10;
        if(temp == 1){
            start += 100 - start % 100 + 100;
            flag = wheel(start);
            return;
        }
        else if(temp == 9){
            long num = start / 1000;
            int index = 3;
            while(num != 0){
                if(num % 10 == 1){
                    long diff = pow(10, index);
                    start += diff - start % diff + diff;
                    flag = wheel(start);
                    return;
                }
                else if(num % 10 == 9) {
                    num /= 10;
                    index++;
                }
                else{
                    break;
                }
            }
            start += inc;
            flag = wheel(start);
            return;
        }
        else {
            start += inc;
            flag = wheel(start);
        }
    }
}

int find(long start, long end) {
    if (end < start)return 0;
    int count = 0;
    int flag = init_start(start);

    while (start <= end) {
//        if (NotHasTwo(start) && sumIsPrime(start)) {
//            cout << start << endl;
//            count++;
//        }
        if(isPrime(start) && sumIsPrime(start)){
            cout << start << endl;
            count++;
        }
        if (flag == 0) {
//            start += 10;
            modify_start(start, 10, flag);
//            flag = 1;
        } else {
//            start += 20;
            modify_start(start, 20, flag);
//            flag = 0;
        }
    }
    return count;
}


int main() {
    clock_t start_time = clock();
    int start, end, n = 0;
    cout << "first number\n";
    cin >> start;
    cout << "second number\n";
    cin >> end;
    n = find(start, end);
    cout << "number: " << n << endl;
    clock_t end_time = clock();
    cout << (double) (end_time - start_time) / CLOCKS_PER_SEC << endl;

}