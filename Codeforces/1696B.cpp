#include <bits/stdc++.h>
using namespace std;
void solve () {
    int n; 
    cin >> n;
    int cnt = 0;
    int ans = 0;
    int arr[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        if (arr[i] == 0) {
            ans += (cnt != 0);
            cnt = 0;
        } else {
            cnt++;
        }
    }
    ans += (cnt != 0);
    cout << min(ans, 2) << '\n';
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
