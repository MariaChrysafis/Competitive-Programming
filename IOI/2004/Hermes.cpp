#include <bits/stdc++.h>
using namespace std;
int delta = 1100;
int main() {
    int n;
    cin >> n;
    int64_t points[n + 1][2];
    points[0][0] = points[0][1] = delta;
    for (int i = 1; i <= n; i++) {
        cin >> points[i][0] >> points[i][1];
        points[i][0] += delta, points[i][1] += delta;
    }
    vector<vector<int64_t> > prev;
    prev.resize(2 * delta + 1);
    for (int i = 0; i <= 2 * delta; i++) {
        prev[i].resize(2);
        prev[i][0] = prev[i][1] = INT_MAX;
    }
    vector<vector<int64_t> > cur = prev;
    prev[delta][0] = prev[delta][1] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= 2 * delta; j++) {
            for (int k = 0; k < 2; k++) {
                cur[j][k] = prev[j][k] + abs(points[i][k] - points[i - 1][k]);
            }
        }
        for (int j = 0; j <= 2 * delta; j++) {
            for (int k = 0; k < 2; k++) {
                cur[points[i - 1][!k]][k] = min(cur[points[i - 1][!k]][k], prev[j][!k] + abs(j - points[i][k]));
            }
        }
        prev = cur;
    }
    int64_t myMin = INT_MAX;
    for (int j = 0; j <= 2 * delta; j++) {
        myMin = min(myMin, min(cur[j][0], cur[j][1]));
    }
    cout << myMin;
}
