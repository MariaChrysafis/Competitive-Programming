#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

vector<uint64_t> powr;

map<uint64_t,uint64_t> myMap[2521][(1 << 10)];

int64_t rec (uint64_t m, int mask, uint64_t r) {
    if (r < 0) {
        return 0;
    }
    if (mask & (1 << 2)) {
        if (mask & (1 << 8)) mask ^= (1 << 2);
        if (mask & (1 << 4)) mask ^= (1 << 2);
    }
    if (mask & (1 << 4)) {
        if (mask & (1 << 8)) mask ^= (1 << 4);
    }
    if (mask & 1) {
        mask ^= 1;
    }
    if (r <= 9) {
        int cntr = 0;
        for (int i = 0; i <= r; i++) {
            bool fine = true;
            for (int j = 1; j <= 9; j++) {
                if ((mask & (1 << j)) || i == j) {
                    if ((m + i) % j != 0) {
                        fine = false;
                    }
                }
            }
            cntr += fine;
        }
        return cntr;
    }
    if (myMap[m][mask].count(r)) {
        return myMap[m][mask][r];
    }
    int digits = to_string(r).size();
    uint64_t starting_digit = r/powr[digits - 1];
    uint64_t ans = 0;
    for (int dig = 0; dig <= starting_digit; dig++) {
        uint64_t x = powr[digits - 1];
        x--;
        uint64_t new_r;
        if (dig != starting_digit) {
            new_r = x;
        } else {
            new_r = r - starting_digit * powr[digits - 1];
        }
        assert(new_r != r);
        uint64_t addition = dig * powr[digits - 1];
        ans += rec((m + addition) % 2520, (mask | (1 << dig)), new_r);
    }
    return (myMap[m][mask][r] = ans);
}

uint64_t solve (uint64_t l, uint64_t r) {
    return rec(0, 0, r) - rec(0, 0, l - 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    powr.push_back(1);
    for (int i = 0; i <100; i++) {
        powr.push_back(powr.back() * (uint64_t)10);
    }
    int t;
    cin >> t;
    while (t--) {
        uint64_t l, r;
        cin >> l >> r;
        cout << solve(l, r) << '\n';
    }
}
