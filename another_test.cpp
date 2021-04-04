#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T> using vec = vector<T>;
template<typename T> using Prior = priority_queue<T>;
template<typename T> using prior = priority_queue<T, vector<T>, greater<T>>;
 
#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define al(a) a.begin(),a.end()
#define F first
#define S second
#define REP(i, n) for(int i = 0; i < n; i++)
#define REP1(i, n) for(int i = 1; i <= n; i++)
#define eb emplace_back
#define pb push_back
#define mp(a, b) make_pair(a, b)
#define debug(x) cout << " > " << #x << ": " << x << endl;
#define devec(v) cout << " > " << #v << ": "; for (auto i : v) cout << i << ' '; cout << endl;
#define devec2(v) cout << " > " << #v << ":\n"; for (auto i : v) { for (auto k : i) cout << ' ' << k; cout << endl; }
 
const int INF = 1e9;
const int nINF = -1e9;
const ll llINF = 4*1e18;
const int MOD = 1e9+7;
 
ll& pmod(ll& a, ll b) { a = (a+b) % MOD; return a; }
ll& pmod(ll& a, ll b, ll c) { a = (a+b) % c; return a; }
ll& mmod(ll& a, ll b) { a = (a-b+MOD) % MOD; return a; }
ll& mmod(ll& a, ll b, ll c) { a = (a-b+c) % c; return a; }
ll& tmod(ll& a, ll b) { a = (a*b) % MOD; return a; }
ll mul(ll a, ll b) { return (a*b) % MOD; }
ll mul(ll a, ll b, ll c) { return (a*b) % c; }
ll POW(ll a, ll b) { ll res=1; do { if(b%2) tmod(res,a); tmod(a,a); } while (b>>=1); return res; }
ll FAC(ll a) { ll res = 1; REP1(i, a) tmod(res, i); return res; }
 
template<typename T1, typename T2>
ofstream operator<<(ofstream& out, pair<T1, T2> a) { cout << a.F << ' ' << a.S; return out; }
int T, N;
void init(){

}
#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
struct BigInteger{
    static const int BASE = 100000000;
    static const int WIDTH = 8;
    vector<int> s;

    BigInteger(long long num = 0) { *this = num; }
    BigInteger operator= (long long num)   {
        s.clear();
        do{
            s.push_back(num % BASE);
            num /= BASE;
        } while (num > 0);
        return *this;
    }

    BigInteger operator= (const string& str){
        s.clear();
        long long x, len = (str.length() - 1) / WIDTH + 1;
        for (int i = 0; i < len;i++){
            int end = str.length() - i * WIDTH;
            int start = max(0, end - WIDTH);
            sscanf(str.substr(start, end - start).c_str(), "%d", &x);
            s.push_back(x);
        }
        return *this;
    }

    BigInteger operator+ (const BigInteger b) const{
        BigInteger c;
        c.s.clear();
        for(int i=0,g=0;;i++){
            if(g== 0 && i >=s.size() && i >=b.s.size())
                break;
            int x = g;
            if(i<s.size()) x+=s[i];
            if(i<b.s.size()) x+=b.s[i];
            c.s.push_back(x % BASE);
            g = x/ BASE;
        }
        return c;
    }
    BigInteger operator* (const BigInteger b)const{
        BigInteger c;
        c.s.clear();
        long long mul;
        for (int i = 0;i < s.size(); i++)
        {
            long long carry = 0;
            for (int g = 0; g < b.s.size();g++){
                mul = (long long)(s[i]) * (long long)(b.s[g]);
                mul += carry;
                if(i + g < c.s.size()){
                    c.s[i+g] += mul % BASE;
                }else{
                    c.s.push_back(mul % BASE);
                }
                carry = mul / BASE;
            }
        }
        for (int i = 0; i < c.s.size(); i++){
            if(c.s[i] >= BASE){
                if(i + 1 < c.s.size()){
                    c.s.push_back(c.s[i] / BASE);
                }else{
                    c.s[i + 1] += c.s[i] / BASE;                    
                }
                c.s[i] %= BASE;
            }
        }
        return c;
    }
    BigInteger operator+=(const BigInteger& b){
        *this = *this + b;
        return *this;
    }
    bool operator< (const BigInteger& b) const{
        if(s.size() != b.s.size()) return s.size() < b.s.size();
        for(int i=s.size() -1 ; i>=0;i--)
            if(s[i] != b.s[i]) return s[i] < b.s[i];
        return false; // Equal
    }
    bool operator> (const BigInteger& b) const{return b < *this;}
    bool operator<= (const BigInteger& b) const {return !(b<*this);}
    bool operator>=(const BigInteger& b) const {return !(*this < b);}
    bool operator!=(const BigInteger& b) const {return b< *this || *this < b;}
    bool operator==(const BigInteger& b)const {return !(b<*this) && !(*this<b);}
    void printoutVec(){
        for (int i = s.size()-1; i >= 0; i--)
            cout << s[i] << " ";
        cout << endl;
    }
};
ostream& operator<< (ostream &out, const BigInteger& x){
    out << x.s.back();
    for (int i = x.s.size() - 2;i >= 0;i--){
        char buf[20];
        sprintf(buf,"%08d",x.s[i]);
        for(int j = 0;j<strlen(buf);j++) out << buf[j];
    }
    return out;
}
istream& operator>> (istream &in, BigInteger & x){
    string s;
    if(!(in >> s)) return in;
    x= s;
    return in;
}
int main(){
    BigInteger R;
    BigInteger R2;
    cout << 52565555565 * 44554755 << endl;
    cin >> T;
    while(T--){
        cin >> R;
        cout << R << endl;
        cin >> R2;
        cout << R2 << endl;
        cout << R2 + R << endl;
        cout << R2 * R << endl;
        R.printoutVec();
        R2.printoutVec();
        (R2 * R).printoutVec();
    }
    return 0;
}