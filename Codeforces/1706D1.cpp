#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

void solve () {
    int n, K;
    cin >> n >> K;
    int arr[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    int ans = INT_MAX;
    for (int mx = 0; mx <= 3000; mx++) {
        int myMin = INT_MAX;
        bool fine = true;
        for (int i = 0; i < n; i++) {
            if (arr[i]/K > mx) {
                fine = false;
                break;
            }
            int l = 1;
            int r = K;
            while (l != r) {
                int m = (l + r)/2;
                if (arr[i]/m <= mx) {
                    r = m;
                } else {
                    l = m + 1;
                }
            }
            myMin = min(myMin, arr[i]/l);
        }
        if (!fine) continue;
        ans = min(ans, mx - myMin);
    }
    cout << ans << '\n';

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
