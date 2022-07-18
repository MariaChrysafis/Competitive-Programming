#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    int64_t arr[n][2];
    int64_t sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> arr[i][0] >> arr[i][1];
    }
    for (int i = 0; i < n; i++) {
        if (arr[i][0] == arr[(i + 1) % n][0] || arr[i][1] == arr[(i + 1) % n][1]) {
            sum += abs(arr[i][0] - arr[(i + 1) % n][0]) + abs(arr[i][1] - arr[(i + 1) % n][1]);
        }
    }
    int64_t area = 0;
    for (int i = 0; i < n; i++) {
        area += arr[i][0] * arr[(i + 1) % n][1] - arr[(i + 1) % n][0] * arr[i][1];
    }
    area = abs(area);
    area = 2 * area - sum;
    cout << area/2;
    if (area % 2) {
        cout << ".5";
    }
}
