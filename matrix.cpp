/*
 * Author: Xujia Ji
 * Data: 04/15/2018
 * Citation: Ye Ke (yek@stevens.edu)
 */
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;

class matrix{
private:
    int rows;
    int cols;
    double* m;
public:
    matrix(int r, int c):rows(r),cols(c){
        m = new double [rows*cols];
        for (int i = 0; i<rows*cols;i++){
            m[i] = 0;
        }
    }
    ~matrix(){
        delete [] m;

    }
    matrix(matrix&& orig){
        rows = orig.rows;
        cols = orig.cols;
        m = orig.m;
        orig.m = nullptr;
    }
    matrix(const matrix& orig): rows(orig.rows),cols(orig.cols){
        m = new double[rows*cols];
        for(int i = 0; i<rows*cols;i++){
            m[i] = orig.m[i];
        }
    }
    double& operator[](int i) const {
        return m[i];
    }
    double operator[](int i){return m[i];}

    void load(){
        for (int i = 0; i < rows; i++) {
            if (i == 0) {
                m[0] = 2;
                m[1] = 1;
                continue;
            }
            if (i == rows - 1) {
                m[i * cols + cols - 1] = 2;
                m[i * cols + cols - 2] = 1;
                continue;
            }
            m[i * cols + (i - 1)] = 1;
            m[i * cols + i] = 4;
            m[i * cols + (i + 1)] = 1;
        }
    }
    vector<double> solve(vector<double> &b){
        vector<double> d;
        for(int i = 0; i < cols - 1; i++){
            double div = -1.0 * m[(i + 1) * cols + i] / m[i * cols + i];
            for(int j = i; j < cols; j++){
                m[(i + 1) * cols + j] += m[i * cols + j] * div;
            }
            b[i + 1] += b[i] * div;
        }
        int index = 0;
        for(int i = rows - 1; i >= 0; i--, index++){
            d.push_back(b[i] / m[i * cols + i]);
            if(i == 0) break;
            b[i - 1] += -1.0 * d[index];
        }
        for(int i = 0; i < d.size() / 2; i++)
            swap(d[i], d[d.size() - 1 -i]);
        return d;
    }


};
int main() {
    ifstream in("hw9.dat");
    int n;
    in>>n;
    vector<double> x;
    vector<double> y;
    vector<double> b;
    vector<double> d;
    double temp;
    for(int i = 0; i <= n;i++){
        in>>temp;
        x.push_back(temp);
        in>>temp;
        y.push_back(temp);
    }
    in.close();
    int s = y.size();
    for(int i = 0; i<s;i++){
        if(i == 0){
            b.push_back(3*(y[1]-y[0]));
            continue;
        }
        else if(i == s){
            b.push_back(3*(y[s-1]-y[s - 1 - 1]));
            continue;
        }
        b.push_back(3*y[i+1]-y[i-1]);
    }
    n++;
    matrix m(s,s);
    m.load();
    d = m.solve(b);
    for(int i = 0; i<n;i++)
        cout << d[i] <<endl;

    for(int i = 0; i < d.size() - 1; i++){
        double a_temp = y[i];
        double b_temp = d[i];
        double c_temp = 3 * (y[i + 1] - y[i]) - 2 * d[i] - d[i + 1];
        double d_temp = 2 * (y[i] - y[i + 1]) + d[i] + d[i + 1];

        double dx = x[i + 1] - x[i];
        double t = 0;
        for(int j = 0; j< 10 ; t += 0.1, j++){
            double y = a_temp  + b_temp * t + c_temp * t * t + d_temp * t * t * t;
            double c_x = t * dx + x[i];
            cout << setiosflags(ios::left);
            cout << setw(4) << i << ' ' << setw(4) << t << ' ' << setw(4) << c_x << ' '<< setw(4) << y << endl;
        }
    }
    return 0;
}