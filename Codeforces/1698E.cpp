#include <bits/stdc++.h>
using namespace std;
const int MOD = 998244353;
void solve () {
    int n, s;
    cin >> n >> s;
    vector<int> a(n), b(n);
    vector<pair<int,int> > pos;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pos.push_back(make_pair(a[i], i));
    }
    set<int> used;
    for (int i = 0; i < n; i++) {
        cin >> b[i];
        used.insert(b[i]);
    }
    for (int i = 0; i < n; i++) {
        if (b[i] != -1 && a[i] >= b[i] && abs(a[i] - b[i]) > s) {
            cout << 0 << '\n';
            return;
        }
    }
    int pref[n + 1];
    pref[0] = 0;
    for (int i = 1; i <= n; i++) {
        pref[i] = pref[i - 1] + !used.count(i);
    }
    used.erase(-1);
    sort(pos.begin(), pos.end());
    int c = 0;
    int64_t res = 1;
    reverse(pos.begin(), pos.end());
    for (auto& p: pos) {
        if (used.count(b[p.second])) {
            continue;
        }
        int l = max(p.first - s, 1);
        int r = n;
        int okay = pref[r] - pref[l - 1];
        res *= okay - c++;
        res %= MOD;
    }
    cout << res << '\n';
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int tc;
    cin >> tc;
    while (tc--) {
        solve();
    }
}
