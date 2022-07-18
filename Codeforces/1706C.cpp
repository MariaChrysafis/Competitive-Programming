#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

void solve () {
    int n;
    cin >> n;
    int64_t c[n];
    for (int i = 0; i < n; i++) {
       cin >> c[i];
    }
    int64_t cost[n];
    for (int i = 1; i < n - 1; i++) {
        int64_t mx = max(c[i - 1], c[i + 1]) + 1;
        cost[i] = max(mx - c[i], 0ll);
    }
    cost[0] = 0, cost[n - 1] = 0;

    if (n % 2 == 1) {
        int64_t ans = 0;
        for (int i = 1; i < n - 1; i += 2) {
            ans += cost[i];
        }
        cout << ans << '\n';
    } else {
        int64_t pref[n + 1][2];
        int cnt1[n + 1][2], cnt2[n + 1][2];
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j < 2; j++) {
                if (i <= 1) {
                    pref[i][j] = 0;
                    cnt1[i][j] = 0;
                    continue;
                } 
                if ((i - 1) % 2 == j) {
                    pref[i][j] = pref[i - 2][j] + cost[i - 1];
                    cnt1[i][j] = cnt1[i - 2][j] + (i - 1 >= 1 && i - 1 < n - 1);
                } else {
                    pref[i][j] = pref[i - 1][j];
                    cnt1[i][j] = cnt1[i - 1][j];
                }
            }
        }
        int64_t suf[n + 1][2];
        for (int i = n; i >= 0; i--) {
            for (int j = 0; j < 2; j++) {
                if (i >= n - 1) {
                    suf[i][j] = 0;
                    cnt2[i][j] = 0;
                    continue;
                }
                if (i % 2 == j) {
                    suf[i][j] = suf[i + 2][j] + cost[i];
                    cnt2[i][j] = cnt2[i + 2][j] + (i >= 1 && i < n - 1);
                } else {
                    suf[i][j] = suf[i + 1][j];
                    cnt2[i][j] = cnt2[i + 1][j];
                }
            }
        }
        int tot = n/2 - 1;
        int64_t ans = LLONG_MAX;
        for (int i = 0; i < n; i++) {
            for (int j1 = 0; j1 < 2; j1++) {
                for (int j2 = 0; j2 < 2; j2++) {
                    if (cnt1[i][j1] + cnt2[i + 1][j2] != tot) continue;
                    ans = min(ans, pref[i][j1] + suf[i + 1][j2]);
                }
            }
        }
        cout << ans << '\n';
    }

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
