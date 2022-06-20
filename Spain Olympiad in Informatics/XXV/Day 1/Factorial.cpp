#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#define ll long long
using namespace std;
const int MAX =  40100;
vector<ll> primes;
vector<bool> isPrime;
bool query(ll a, ll b){
    cout << "? " << a << " " << b << endl;
    string s;
    cin >> s;
    if(s == "SI"){
        return true;
    }else{
        return false;
    }
}
const ll MOD = 999999733;
ll mult(ll a, ll b){
    return (a * b) % MOD;
}
ll binSearch(ll l, ll r){
    if(l == r){
        return l;
    }
    ll m = (l + r + 1)/2;
    if(query(primes[m], primes[m])){
        return binSearch(m, r);
    }else{
        return binSearch(l, m - 1);
    }
}
int main(){
    vector<ll> fact;
    fact.push_back(1);
    while(fact.size() != MAX){
        fact.push_back(mult(fact.size(), fact.back()));
    }
    isPrime.resize(MAX);
    for(int i = 0; i < isPrime.size(); i++){
        isPrime[i] = true;
    }
    isPrime[1] = isPrime[0] = false;
    for(int i = 2; i < isPrime.size(); i++){
        if(isPrime[i]){
            for(int j = 2 * i; j < isPrime.size(); j += i){
                isPrime[j] = false;
            }
        }
    }
    for(int i = 0; i < isPrime.size(); i++){
        if(isPrime[i]){
            primes.push_back(i);
        }
    }
    if(!query(2, 2)){
        cout << "! 1" << endl;
        return 0;
    }
    ll x = binSearch(0, primes.size() - 1);
    for(int i = primes[x]; i <= primes[x + 1]; i++){
        if(query(MOD - fact[i], MOD)){
            cout << "! " << i << endl;
            return 0;
        }
    }
}
