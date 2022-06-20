#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
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


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<ll> a(n + 1), p(n + 1);
    for(int i = 0; i < n; i++){
        cin >> a[i + 1];
    }
    for(int i = 0; i < n; i++){
        cin >> p[i + 1];
    }
    a[0] = p[0] = 0;
    vector<ll> pref(n + 1), suf(n + 1);
    vector<ll> pref1(n + 1), suf1(n + 1);
    pref1[0] = 0, pref[0] = 0;
    for(int i = 1; i <= n; i++){
        pref[i] = pref[i - 1] + p[i];
        pref1[i] = pref1[i - 1] + p[i] * a[i];
    }
    suf[n] = p[n];
    suf1[n] = p[n] * a[n];
    for(int i = n - 1; i >= 0; i--){
        suf[i] = suf[i + 1] + p[i];
        suf1[i] = suf1[i + 1] + p[i] * a[i];
    }
    suf.push_back(0);
    suf1.push_back(0);
    //print(suf), print(pref);
    ll myMin = LLONG_MAX;
    ll bInd = -1;
    for(int i = 1; i <= n; i++){
        ll ans = 0;
        ans += a[i] * pref[i - 1];
        ans -= a[i] * suf[i + 1];
        ans -= pref1[i - 1];
        ans += suf1[i + 1];
        //cout << ans << " ";
        if(ans < myMin){
            myMin = ans;
            bInd = i;
        }
    }
    cout << bInd - 1 << endl;
}
