#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;
int64_t binPow (int64_t x, int64_t y) {
    int64_t res = x, ans = 1;
    while (y > 0) {
        if (y & 1) {
            ans *= res, ans %= MOD;
        }
        res *= res, res %= MOD;
        y /= 2;
    }
    return ans;
}
int64_t inv (int64_t x) {
    return binPow(x, MOD - 2);
}
vector<int64_t> fact;
int64_t combo (int x, int y) {
    if (x < y) return 0;
    return (fact[x] * inv((fact[x - y] * fact[y]) % MOD)) % MOD;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    fact.push_back(1);
    while (fact.size() != (int)5e5) {
        fact.push_back(fact.back() * fact.size());
        fact.back() %= MOD;
    }
    int n;
    cin >> n;
    int64_t arr[n + 1];
    int64_t ans = 0;
    for (int i = 0; i <= n; i++) {
        cin >> arr[i];
        ans += combo(arr[i] + i, i + 1);
        ans %= MOD;
    }
    cout << ans;
}
