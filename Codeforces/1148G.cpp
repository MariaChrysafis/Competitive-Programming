#include <bits/stdc++.h>
 
using namespace std;

const int MAX = 1e7 + 1;

int gcd (int u, int v) {
    if (!u || !v) return max(u, v);
    return gcd(max(u, v) % min(u, v), min(u, v));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    vector<bool> isPrime;
    isPrime.assign(MAX, true);
    vector<int64_t> fact(MAX);
    vector<int64_t> red(MAX);
    for (int i = 0; i < MAX; i++) {
        red[i] = i;
    }
    for (int64_t i = 2; i < MAX; i++) {
        if (isPrime[i]) {
            fact[i] = i;
            for (int64_t j = 2 * i; j < MAX; j += i)  {
                isPrime[j] = false;
                fact[j] = i;
                while (red[j] % (i * i) == 0) {
                    red[j] /= i;
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        arr[i] = red[arr[i]];
    }
    vector<int> cnt;
    vector<vector<int> > f(n);
    cnt.assign(MAX, 0);
    for (int i = 0; i < n; i++) {
        int x = arr[i];
        while (x != 1) {
            f[i].push_back(fact[x]);
            cnt[fact[x]]++;
            x /= fact[x];
        }
    }
    
    for (int i = 0; i < cnt.size(); i++) {
        if (cnt[i] >= k) {
            vector<int> v;
            for (int j = 0; j < arr.size(); j++) {
                if (arr[j] % i == 0) {
                    v.push_back(j);
                }
            }
            for (int j = 0; j < k; j++) {
                cout << v[j] + 1 << ' ';
            }
            exit(0);
        }
    }
    
    cnt.assign(MAX, 0);
    for (int i = 0; i < arr.size(); i++) {
        for (int j: f[i]) {
            cnt[j]++;
        }
    }
    vector<int> deg;
    deg.assign(n, false);
    int cntr = 0;
    for (int i = 0; i < n; i++) {
        int ans = 0;
        for (int j = 1; j < (1 << (int)f[i].size()); j++) {
            int c = 1;
            for (int k = 0; k < f[i].size(); k++) {
                if (j & (1 << k)) {
                    c *= f[i][k];
                }
            }
            ans -= cnt[c] * pow(-1, __builtin_popcount(j));
        }
        ans--;
        deg[i] = ans;
        if (deg[i] <= n - k) {
            vector<int> vec;
            vec.push_back(i);
            for (int j = 0; j < n; j++) {
                if (gcd(arr[i], arr[j]) == 1) {
                    vec.push_back(j);
                }
            }
            for (int j = 0; j < k; j++) {
                cout << vec[j] + 1 << ' ';
            }
            return 0;
        }
    }
}
