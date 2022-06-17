#include <bits/stdc++.h>
using namespace std;
int64_t compress1 (vector<int> &v, int64_t base, int64_t MOD) {
    int64_t x = 0;
    int64_t powr = 1;
    for (int i = 0; i < v.size(); i++) {
        x += (v[i] * powr) % MOD, x %= MOD;
        powr *= base, powr %= MOD;
    }
    return x;
}
pair<int64_t,int64_t> compress (vector<int> &v) {
    return make_pair(compress1(v, 1e8 + 7, 1e5 - 9), compress1(v, 1e8 + 9, 1e9 + 7));
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    set<int64_t> mySet[(int)1e5];
    for (int i = 0; i < n; i++) {
        vector<int> v;
        v.resize(6);
        for (int j = 0; j < 6; j++) {
            cin >> v[j];
        }
        vector<pair<int64_t,int64_t> > later;
        int t = 6;
        while (t--) {
            rotate(v.begin(), v.begin() + 1, v.end());
            pair<int64_t,int64_t> x = compress(v);
            later.push_back(x);
            if (mySet[x.first].count(x.second)) {
                cout << "Twin snowflakes found.\n";
                exit(0);
            }
        }
        reverse(v.begin(), v.end());
        t = 6;
        while (t--) {
            rotate(v.begin(), v.begin() + 1, v.end());
            pair<int64_t,int64_t> x = compress(v);
            later.push_back(x);
            if (mySet[x.first].count(x.second)) {
                cout << "Twin snowflakes found.\n";
                exit(0);
            }
        }
        for (auto& v1: later) {
            mySet[v1.first].insert(v1.second);
        }
    }
    cout << "No two snowflakes are alike.\n";

}
