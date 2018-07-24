/*
 * Author name: Xujia Ji
 * date: 02/12/2018
 * Citation: Ke Ye（kye@stevens.edu）
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
using namespace std;

int partition(vector<int> &num, int left, int right) {
    int i = left;
    int j = right;

    srand((unsigned)time(NULL));
    int pivot = left + rand() % (right - left);

    int key = num[pivot];
    swap(num[left], num[pivot]);

    while (i < j) {
        while (i < j && num[j] >= key)
            j--;

        while (i < j && num[i] <= key)
            i++;
        swap(num[i], num[j]);
    }

    swap(num[left], num[i]);
    return i;
}


void quick_Sort(vector<int> &num, int left, int right) {
    if(left >= right) return;
    int pivot = partition(num, left, right);
    quick_Sort(num, left, pivot - 1);
    quick_Sort(num, pivot + 1, right);
}


void loadfile(vector<int> &num) {
    ifstream file("hw3.dat");
    int num_count;
    file >> num_count;
    do {
        int temp;
        file >> temp;
        num.push_back(temp);
    } while (--num_count != 0);
    file.close();
}


int main() {
    vector<int> num_vec;
    loadfile(num_vec);
    quick_Sort(num_vec, 0, num_vec.size() - 1);
    for(int i : num_vec){
        printf("%d ",i);
    }
}