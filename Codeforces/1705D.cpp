#include <bits/stdc++.h>

using namespace std;
vector<int64_t> find_dif (string s) {
    vector<int64_t> v;
    for (int i = 1; i < s.length(); i++) {
        if (abs(s[i] - s[i - 1]) == 1) {
            v.push_back(i);
        }
    }
    return v;
}
void solve () {
    int n;
    cin >> n;
    string s, t;
    cin >> s >> t;
    vector<int64_t> vs = find_dif(s), vt = find_dif(t);
    if (vs.size() != vt.size() || s[0] != t[0] || s.back() != t.back()) {
        cout << "-1\n";
        return;
    }
    int64_t ans = 0;
    for (int i = 0; i < vs.size(); i++) {
        ans += abs(vs[i] - vt[i]);
    }
    cout << ans << '\n';
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
