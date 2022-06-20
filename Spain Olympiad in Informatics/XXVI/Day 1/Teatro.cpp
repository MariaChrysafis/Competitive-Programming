#include <bits/stdc++.h>
using namespace std;
int solve () {
    int n;
    cin >> n;
    vector<int> v[2];
    set<int> s;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        s.insert(x);
        cin >> x;
        v[x % 2].push_back(x);
    }
    if (s.size() != 1) {
        cout << "NO\n";
        return 0;
    }
    s.clear();
    for (int j = 0; j < 2; j++) {
        sort(v[j].begin(), v[j].end());
        for (int i: v[j]) s.insert(i);
        for (int i = 1; i < v[j].size(); i++) {
            if (v[j][i] != v[j][i - 1] + 2) {
                cout << "NO\n";
                return 0;
            }
        }
    }
    if (v[0].empty() || v[1].empty()) {
        cout << "SI\n";
        return 0;
    }
    if (!s.count(1)) {
        cout << "NO\n";
        return 0;
    }
    if (s.count(2)) cout << "SI\n";
    else cout << "NO\n";
    return 0;
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
