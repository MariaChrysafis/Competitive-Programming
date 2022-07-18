#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

void solve () {
    int n, m;
    cin >> n >> m;
    string s;
    s.assign(m, 'B');
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        x--;
        x = min(x, m - 1 - x);
        if (s[x] != 'A') {
            s[x] = 'A';
        } else {
            s[m - 1 - x] = 'A';
        }
    }
    cout << s << '\n';
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
