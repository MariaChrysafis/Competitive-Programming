#include <bits/stdc++.h>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
using namespace std;
const int MOD = 998244353;
int64_t binPow (int64_t x, int64_t y) {
    int64_t ans = 1;
    int64_t res = x;
    while (y > 0) {
        if (y & 1) {
            ans *= res, ans %= MOD;
        }
        res *= res, res %= MOD;
        y /= 2;
    }
    return ans;
} 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    string s;
    cin >> s;
    int q = 0;
    for (char c: s) {
        q += (c == '?');
    }
    pair<int,int> dp[n][n];
    for (int i = n - 1; i >= 0; i--) {
        dp[i][i] = make_pair(q, 0);
        if (i + 1 != n) {
            if (s[i] == '?' && s[i + 1] == '?') dp[i][i + 1] = make_pair(q - 1, 0);
            else if (s[i + 1] == '?') dp[i][i + 1] = make_pair(q - 1, (1 << (s[i] - 'a')));
            else if (s[i] == '?') dp[i][i + 1] = make_pair(q - 1, (1 << (s[i + 1] - 'a')));
            else if (s[i] == s[i + 1]) dp[i][i + 1] = make_pair(q, 0);
            else dp[i][i + 1] = make_pair(-1, -1);
        }
        for (int j = i + 2; j < n; j++) {
            assert(j - 1 >= i + 1);
            dp[i][j] = dp[i + 1][j - 1];
            if (s[i] == '?' && s[j] == '?') dp[i][j].first--;
            else if (s[i] == '?') dp[i][j].first--, dp[i][j].second |= (1 << (s[j] - 'a'));
            else if (s[j] == '?') dp[i][j].first--, dp[i][j].second |= (1 << (s[i] - 'a'));
            else if (s[i] != s[j]) dp[i][j] = make_pair(-1, -1);
        }
    }
    const int sz = 17;
    vector<vector<int>> res((1 << sz), vector<int>(sz + 1));
    vector<vector<int>> tot((1 << sz), vector<int>(sz + 1));
    for (int i = 0; i < (1 << sz); i++) {
        for (int j = 0; j <= sz; j++) {
            res[i][j] = 0;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (dp[i][j].first < 0) continue;
            for (int k = 0; k <= sz; k++) {
                res[dp[i][j].second][k] += binPow(k, dp[i][j].first), res[dp[i][j].second][k] %= MOD;
            }
        }
    }
    for (int i = 0; i < (1 << sz); i++) {
        for (int j = 0; j <= sz; j++) {
            tot[i][j] = res[i][j];
        }
    }
    for (int k = 0; k <= sz; k++) {
        for (int i = 0; i < sz; i++) {
            for (int mask = 0; mask < (1 << sz); mask++) {
                if (mask & (1 << i)) {
                    tot[mask][k] += tot[mask ^ (1 << i)][k], tot[mask][k] %= MOD;
                }
            }
        }
    }
    cin >> q;
    while (q--) {
        string str;
        cin >> str;
        int mask = 0;
        for (int i = 0; i < str.length(); i++) {
            mask |= (1 << (str[i] - 'a'));
        }
        cout << tot[mask][__builtin_popcount(mask)] << '\n';
    }
}
