#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    string grid[n];
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }
    if (grid[0][0] != grid[n - 1][m - 1]) {
        cout << 0;
        exit(0);
    }
    vector<vector<int64_t> > prev(n);
    for (int i = 0; i < n; i++) {
        prev[i].assign(n, false);
    }
    vector<vector<int64_t> > cur = prev;
    prev[0][n - 1] = 1;
    int64_t ans = 0;
    for (int moves = 0; moves < n + m; moves++) {
        for (int x1 = 0; x1 < n; x1++) {
            for (int x2 = 0; x2 < n; x2++) {
                if (x1 + 1 < n && x2 - 1 >= 0) cur[x1 + 1][x2 - 1] += prev[x1][x2];
                if (x1 + 1 < n) cur[x1 + 1][x2] += prev[x1][x2];
                if (x2 - 1 >= 0) cur[x1][x2 - 1] += prev[x1][x2];
                cur[x1][x2] += prev[x1][x2];
            }
        }
        for (int x1 = 0; x1 < n; x1++) {
            for (int x2 = 0; x2 < n; x2++) {
                int y1 = moves + 1 - x1;
                int y2 = m - 1 - (moves + 1 - (n - 1 - x2));
                if (y1 < 0 || y2 < 0 || y1 >= m || y2 >= m || grid[x1][y1] != grid[x2][y2]) {
                    cur[x1][x2] = 0;
                    continue;
                }
                if (moves + 1 == (n + m)/2 - 1) {
                    if ((n + m) % 2 == 0) ans += cur[x1][x2] * (abs(x1 - x2) + abs(y1 - y2) == 0);
                    else ans += cur[x1][x2] * (abs(x1 - x2) + abs(y1 - y2) == 1);
                }
                if (ans >= MOD) ans -= MOD;
            }
        }
        swap(prev, cur);
        for (int x1 = 0; x1 < n; x1++) {
            for (int x2 = 0; x2 < n; x2++) {
                cur[x1][x2] = 0;
                prev[x1][x2] %= MOD;
            }
        }
    }
    cout << ans;
}
