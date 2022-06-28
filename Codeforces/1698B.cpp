#include <bits/stdc++.h>
 
using namespace std;
int cntr = 0;
int L, R;
int get (vector<int>& arr, int x) {
    return (arr[x] + (x >= L && x <= R));
}
int update (vector<int>& arr, vector<bool>& okay, int i) {
    if (i <= 0 || i >= (int)arr.size() - 1) return 0;
    int b1 = (get(arr, i) > get(arr, i - 1) + get(arr, i + 1));
    int b2 = okay[i];
    return b1 - b2;
}
void solve () {
    int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    int cntr = 0;
    for (int i = 1; i < n - 1; i++) {
        cntr += (arr[i] > arr[i - 1] + arr[i + 1]);
    }
    if (k == 1) {
        cout << (n - 1)/2 << '\n';
        return;
    }
    cout << cntr << '\n';
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
