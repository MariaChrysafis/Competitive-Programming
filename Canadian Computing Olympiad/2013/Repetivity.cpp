#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s;
    cin >> s;
    int n = s.length();
    int MOD;
    cin >> MOD;
    vector<int64_t> cur(n + 1);
    vector<int64_t> prev(n + 1);
    prev.assign(n + 1, 0);
    cur.assign(n + 1, 0);
    prev[0] = 1;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            cur[j] = 0;
            if (i == 0 || j == 0) {
                cur[j] = 1;
            } else {
                if (s[i - 1] == s[j - 1]) {
                    cur[j] = prev[j] + cur[j - 1];
                } else {
                    cur[j] = prev[j] + cur[j - 1] - prev[j - 1];
                }
                cur[j] += MOD, cur[j] %= MOD;
            }
        }
        swap(prev, cur);
        cur.assign(n + 1, false);
    }
    cout << prev[n];
}
