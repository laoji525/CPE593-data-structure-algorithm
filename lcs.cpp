/*
 * Author name: Xujia Ji
 */

#include <iostream>
#include <fstream>
using namespace std;

int LCS(string s, string t, int m, int n) {
    if (m == 0 || n == 0) {
        return 0;
    }
    if (s[m-1] == t[n-1])
        return 1 + LCS(s, t, m - 1, n - 1);
    else
        return max(LCS(s, t, m, n - 1), LCS(s, t, m - 1, n));
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

    int res = LCS(s, t,s.size(),t.size());
    printf("LCS is %d\n",res);

    return 0;
}