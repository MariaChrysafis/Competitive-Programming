#include <bits/stdc++.h>
using namespace std;
void solve () {
    int n, z;
    cin >> n >> z;
    int arr[n];
    int ans = 0;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        ans = max(ans, z | arr[i]);
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
