#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <algorithm>
#include <set>

#define ll long long
using namespace std;

void print(vector<ll> v){
    for(ll x: v) cout << x << " ";
    cout << '\n';
}

void print(vector<int> v){
    for(int x: v) cout << x << " ";
    cout << '\n';
}

const int MOD = 1e9 + 7;
ll mult(ll a, ll b){
    if(a * b < MOD) return a * b;
    return (a * b) % MOD;
}
ll sub(ll a, ll b){
    return (a - b + b * MOD) % MOD;
}
ll add(ll a, ll b){
    if(a + b < MOD) return a + b;
    return (a + b) % MOD;
}
ll binpow(ll a, ll b){
    ll ans = 1;
    ll res = a;
    while(b > 0){
        if(b & 1){
            ans = mult(ans, res);
        }
        res = mult(res, res);
        b /= 2;
    }
    return ans;
}
vector<ll> fact;
vector<ll> fact_inv;
ll inv(ll a){
    return binpow(a, MOD - 2);
}
ll combo(ll a, ll b){
    if(a < b) return 0;
    return mult(fact[a], mult(fact_inv[b], fact_inv[a - b]));
}

set<string> dictionary;
vector<string> pos;
vector<char> tiles;
void rec(string s){
    if(s.length() == 7){
        string str = "";
        for(int i = 0; i < s.length(); i++){
            if(s[i] == '1') str += tiles[i];
        }
        sort(str.begin(), str.end());
        pos.push_back(str);
        return;
    }
    rec(s + '1'), rec(s + '0');
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        sort(s.begin(), s.end());
        dictionary.insert(s);
    }
    tiles.resize(7);
    for(int i = 0; i < 7; i++){
        cin >> tiles[i];
    }
    rec("");
    int myMax = 0;
    for(string s: pos) {
        if(dictionary.count(s)){
            myMax = max(myMax, (int)s.length());
            if(s.length() > 3){
                myMax = max(myMax, (int)s.length() * 2);
            }
        }
    }
    cout << myMax << endl;
}
