#include <bits/stdc++.h>
 
using namespace std;

vector<int64_t> fact;

vector<int> kth_smallest (int N, int64_t k) {
    vector<int64_t> fact;
    fact.push_back(1);
    for (int i = 0; i < N; i++) {
        fact.push_back(fact.back() * (i + 1));
    }
    vector<bool> marked;
    marked.assign(N, true);
    vector<int> v;
    int n = N;
    while (n >= 1) {
        int cntr = 0;
        for (int i = 0; i < N; i++) {
            cntr += marked[i];
            if (marked[i] && cntr - 1 == k/fact[n - 1]) {
                v.push_back(i);
                marked[v.back()] = false;
                k -= k/fact[n - 1] * fact[n - 1];
                n--;
                break;
            }
        }
    }
    for (int i = 0; i < v.size(); i++) {
        v[i]++;
    }
    return v;
}

int sz = 18;

int64_t sum (vector<int>& perm, int x, int n) {
    if (x == -1) {
        return 0;
    }
    int64_t l = min(x, n - sz);
    int64_t ans = l * (l + 1)/2;
    for (int i = 0; i < perm.size(); i++) {
        if (n - sz + i <= x - 1) {
            ans += perm[i];
        }
    }
    return ans;
}

int main () {

    int n, q;
    cin >> n >> q;
    int64_t x = 0;
    vector<pair<int64_t,pair<int,int> > > vec;
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int l, r;
            cin >> l >> r;
            l--, r--;
            vec.push_back(make_pair(x, make_pair(l, r)));
        } else {
            int a; cin >> a;
            x += a;
        }
    }
    sz = min(n, sz);
    for (auto& p: vec) {
        vector<int> perm = kth_smallest(sz, p.first);
        for (int i = 0; i < perm.size(); i++) {
            perm[i] += n - sz;
        }
        cout << sum(perm, p.second.second + 1, n) - sum(perm, p.second.first, n) << '\n';
        
    }
}
