/*
 * Author name: Xujia Ji
 * date: 02/06/2018
 */

#include <iostream>
#include <fstream>
using namespace std;

int editDist(string s, string t, int m, int n) {
    if (m == 0) return n;
    if (n == 0) return m;
    if (s[m - 1] == t[n - 1]) {
        return editDist(s, t, m - 1, n - 1);
    }
    return 1 + min(min(editDist(s, t, m - 1, n), editDist(s, t, m, n - 1)),editDist(s,t,m-1,n-1));
}

string loadFile(const char filename[]) {
    ifstream f(filename);
    string contents;
    /// read the string
    getline(f,contents);
    f.close();
    return contents;
}

int main(int argc, char* argv[]) {

    string s = loadFile(argv[1]);
    string t = loadFile(argv[2]);

    int res = editDist(s, t,s.size(),t.size());
    printf("Edit Distance is %d\n",res);

    return 0;
}