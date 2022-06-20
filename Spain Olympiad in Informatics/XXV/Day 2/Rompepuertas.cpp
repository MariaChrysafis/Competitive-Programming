#include <iostream>
#include <vector>
#define ll long long
using namespace std;
vector<ll> read(ll n){
    vector<ll> v(n);
    for(int i = 0; i < n; i++){
        cin >> v[i];
    }
    return v;
}
int main(){
    ll n, m;
    cin >> n >> m;
    vector<ll> arr = read(n);
    vector<ll> f = read(m);
    ll left = 0;
    ll right = 0;
    ll cur = 0;
    for(int i = 0; i < m; i++){
        //cout << cur << " " << right << endl;
        while(right != n && cur + arr[right] <= f[i]){
            cur += arr[right];
            right++;
        }
        left = right;
        cur = 0;
    }
    cout << right << endl;
}
