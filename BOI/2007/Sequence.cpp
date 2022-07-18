#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int64_t> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    int64_t ans = 0;
    for (int i = 1; i < n; i++) {
        ans += max(v[i], v[i -1 ]);
    }
    cout << ans;
}
