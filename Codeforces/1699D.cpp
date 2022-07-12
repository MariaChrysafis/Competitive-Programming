#include <bits/stdc++.h>
using namespace std;
void solve () {
    int n;
    cin >> n;
    vector<int> v(n);
    set<int> s;
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        s.insert(v[i]);
    }
    bool dp[n][n]; //can we remove everything from x...y?
    for (int len = 1; len <= n; len++) {
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;
            if (len % 2 == 1) {
                dp[i][j] = false;
                continue;
            } 
            if (len == 2) {
                dp[i][j] = (v[i] != v[j]);
                continue;
            }
            dp[i][j] = false;
            if (v[i] != v[j] && dp[i + 1][j - 1]) {
                dp[i][j] = true;
                continue;
            }
            if (v[i] != v[i + 1] && dp[i + 2][j]) {
                dp[i][j] = true;
                continue;
            }
            if (v[j] != v[j - 1] && dp[i][j - 2]) {
                dp[i][j] = true;
                continue;
            }
            for (int prev = i + 1; prev <= j; prev++) {
                if (dp[i][prev - 1] && dp[prev][j]) {
                    dp[i][j] = true;
                    break;
                }
                if (prev - i > 100) break;
            }
        }
    }
    map<int,vector<int> > oc;
    for (int i = 0; i < v.size(); i++) {
        oc[v[i]].push_back(i);
    }
    int myMax = 0;
    for (int x: s) {
        int pref[n];
        for (int i = 0; i < n; i++) {
            pref[i] = -INT_MAX;
        }
        if (v[0] == x) {
            pref[0] = 1;
        }
        for (int i = 1; i < n; i++) {
            if (v[i] == x) {
                pref[i] = pref[i - 1] + 1;
            }
            for (int prev: oc[x]) {
                prev++;
                if (prev < i && dp[prev][i] && v[prev - 1] == x) {
                    pref[i] = max(pref[i], pref[prev - 1]);
                }
            }
            if (dp[0][i] && pref[i] < 0) {
                pref[i] = 0;
            }
        }
         myMax = max(myMax, pref[n - 1]);
    }
    cout << myMax << '\n';
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
