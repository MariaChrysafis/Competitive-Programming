#include <bits/stdc++.h>
using namespace std;
const int MOD = 998244353;
struct Pair {
    int64_t sum;
    int64_t number;
    Pair (int64_t x, int64_t y) {
        sum = x, number = y;
    }
};
vector<int64_t> powr;
int x;
map<int64_t,pair<int64_t,int64_t> > myMap[(1 << 11)][20][2];
Pair rec (int64_t mask, int64_t r, int64_t d, bool first) {
    if (__builtin_popcount(mask) > x || r < 0 || d < 0) {
        return Pair(0, 0);
    }
    if (myMap[mask][d][first].count(r)) {
        return Pair(myMap[mask][d][first][r].first, myMap[mask][d][first][r].second);
    }
    if (r <= 9 && d == 1) {
        Pair ans = Pair(0, 0);
        for (int j = 0; j <= r; j++) {
            if (__builtin_popcount(mask | (1 << j)) <= x) {
                ans.number++, ans.sum += j;
            }
        }
        return ans;
    }
    int64_t starting_digit = r/powr[d - 1];
    Pair ans = Pair(0, 0);
    for (int dig = first; dig <= starting_digit; dig++) {
        Pair res = rec((mask | (1 << dig)), (starting_digit == dig ? r - powr[d - 1] * starting_digit :  powr[d - 1] - 1), d - 1, false);
        ans.number += res.number;
        ans.sum += ((res.number * dig) % MOD * (powr[d - 1] % MOD)) % MOD + res.sum;
        ans.sum %= MOD, ans.number %= MOD;
    }
    myMap[mask][d][first][r] = make_pair(ans.sum, ans.number);
    return Pair(ans.sum, ans.number);
}
int64_t solve (int64_t r) {
    if (r < 0) {
        return 0;
    }
    int64_t ans = rec(0, r, to_string(r).size(), true).sum;
    for (int d = 1; d <= to_string(r).size() - 1; d++) {
        ans = (ans + rec(0, powr[d] - 1, d, true).sum) % MOD;
    }
    return ans;
}
int main() {
    powr.push_back(1);
    for (int i = 1; i <= 18; i++) {
        powr.push_back(powr[i - 1] * 10ll);
    }
    int64_t l, r;
    cin >> l >> r >> x;
    int64_t ans = solve(r) - solve(l - 1) + MOD;
    cout << ans % MOD;
    return 0;
}
