/*
 * Author name: Xujia Ji
 * date: 02/12/2018
 * citation: Ke Ye（kye@stevens.edu）
 */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void loadfile(vector<int> &vec) {
    ifstream file("hw3.dat");
    int n;
    int temp;
    file >> n;
    do{
        file >> temp;
        vec.push_back(temp);
    }while(--n != 0);
    file.close();
}

void Insertion_sort(vector<int> &vec){
    for(int i = 1; i < vec.size(); i++){
        int temp = vec[i];
        for(int j = i - 1; j >= 0; j--){
            if(vec[j] > temp)
                vec[j + 1] = vec[j];
            else{
                vec[j + 1] = temp;
                break;
            }
        }
    }
}


int main() {

    vector<int> num_vec;
    loadfile(num_vec);
    for(int i : num_vec){
        printf("%d ",i);
    }
    printf("\n");
    Insertion_sort(num_vec);
    for(int i : num_vec){
        printf("%d ",i);
    }
}
