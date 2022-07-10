#include <iostream>
#include <string>
#include <regex>
#include <vector>
using namespace std;
// T for Text, P for Patterm
vector <int> build_kmp(const string &P) {
    vector <int> f(P.size());
    int fp = f[0] = -1;
    for (int i = 1; i < P.size(); ++i) {
        while (~fp && P[fp + 1] != P[i])
            fp = f[fp];
        if (P[fp + 1] == P[i])
            ++fp;
        f[i] = fp;
    }
    
    return f;
}
vector <int> kmp_match(vector <int> fail, const string &P, const string &T)
{
    vector <int> res; // start from these points
    const int n = P.size();
    for (int j = 0, i = -1; j < T.size(); ++j) {
        while (~i && T[j] != P[i + 1]) 
            i = fail[i];
        if (P[i + 1] == T[j])
            ++i;
        if (i == n - 1) 
            res.push_back(j - n + 1), i = fail[i];
    }
    return res;
}
int main(){
    char control;
    string test_patterm = "a";
    string test_text = "abcdabcdabceabcd";
    // for testing
    cout << "Do you want to Enter by ys?(y/n)";
    cin >> control;
    if(control == 'y' || control == 'Y'){
        cout << "Enter text:";
        cin >> test_text;
        cout << "Enter patterm:";
        cin >> test_patterm;
    }
    
    vector<int> V = build_kmp(test_patterm);
    vector<int> Ans = kmp_match(V, test_patterm, test_text);
    cout << '\n';
    for(auto it = V.begin(); it != V.end(); ++it)
        cout << *it <<' ';
    cout << '\n';
    for(auto it = Ans.begin(); it != Ans.end(); ++it)
        cout << *it <<' ';
    return 0;
}