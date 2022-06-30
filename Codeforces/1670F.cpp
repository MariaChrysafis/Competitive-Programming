#include <bits/stdc++.h>
 
using namespace std;

const int64_t MOD = 1e9 + 7;
int n;
const int bits = 60;
map<int64_t,int64_t> dp[bits];
int64_t z;
int64_t combo[1001][1001];
int64_t solve (int x, int64_t y) {
    if (y < 0) {
        return 0;
    }
    if (x == -1) {
        return 1;
    }
    if (y/n >= (1ll << (x + 1))) {
        y = min(y, (1ll << (x + 1)) * n);
    }
    if (dp[x].count(y)) {
        return dp[x][y];
    }
    bool b = z & (1ll << x);
    int64_t res = 0;
    for (int cnt = b; cnt <= n; cnt += 2) {
        if (y - (1ll << x) * cnt < 0) break;
        res += (solve(x - 1, y - (1ll << x) * cnt) * combo[n][cnt]) % MOD;
        res %= MOD;
    }
    return (dp[x][y] = res);
}
int main () {
    int64_t l, r;
    cin >> n >> l >> r >> z;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            if (j == 0) {
                combo[i][j] =1;
            } else if (i < j) {
                combo[i][j] = 0;
            } else {
                combo[i][j] = (combo[i - 1][j] + combo[i - 1][j - 1]) % MOD;
            }
        }
    }
    cout << (solve(bits - 1, r) - solve(bits - 1, l - 1) + MOD) % MOD << '\n';
}
