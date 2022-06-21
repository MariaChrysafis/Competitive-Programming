#include <bits/stdc++.h>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
using namespace std;
int solve (vector<int> v, int l, int r, int bit) {
    if (bit == -1) {
        return 0;
    }
    int mask = 0;
    for (int i = 18; i >= bit; i--) {
        mask += (1 << i);
    }
    map<int,int> c;
    for (int i = 0; i < v.size(); i++) {
        c[v[i] & mask]++;
    }
    map<int,int> b;
    for (int i = l; i <= r; i++) {
        b[i & mask]++;
    }
    if (c != b) {
        for (int i = 0; i < v.size(); i++) {
            v[i] ^= (1 << bit);
        }
        return solve(v, l, r, bit - 1) ^ (1 << bit);
    }
    return solve(v, l, r, bit - 1);

}
void f (int tc) {
    int l, r;
    cin >> l >> r;
    int n = r - l + 1;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    cout << solve(v, l, r, 18) << '\n';
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        f(tc);
    }
}
