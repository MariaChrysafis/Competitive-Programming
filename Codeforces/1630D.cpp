#include <bits/stdc++.h>
 
using namespace std;
int gcd (int a, int b) {
    if (!a || !b) return max(a, b);
    return gcd(max(a, b) % min(a, b), min(a, b));
}
pair<int64_t,int64_t> solver (vector<int64_t> a) {
    if (a.empty()) {
        return make_pair(0, 0);
    }
    int64_t dp[a.size()][2];
    dp[0][0] = a[0];
    dp[0][1] = -a[0];
    for (int i = 1; i < a.size(); i++) {
        dp[i][0] = dp[i][1] = -LLONG_MAX;
        for (int j = 0; j < 2; j++) {
            dp[i][j] = max(dp[i][j], dp[i - 1][j] + a[i]);
            dp[i][j] = max(dp[i][j], dp[i - 1][!j] - a[i]);
        }
    }
    return make_pair(dp[(int)a.size() - 1][0], dp[(int)a.size() - 1][1]);
}
void solve () {
    int n, k;
    cin >> n >> k;
    vector<int64_t> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    int g = 0;
    for (int i = 0; i < k; i++) {
        int x;
        cin >> x;
        g = gcd(g, x);
    }
    vector<vector<int64_t> > a(g);
    for (int i = 0; i < n; i++) {
        a[i % g].push_back(arr[i]);
    }
    pair<int64_t,int64_t> p = make_pair(0, 0);
    for (int i = 0; i < g; i++) {
        auto q = solver(a[i]);
        p.first += q.first, p.second += q.second;
    }
    cout << max(p.first, p.second) << '\n';
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
