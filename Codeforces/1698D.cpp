#include <bits/stdc++.h>
 
using namespace std;
int query (int l, int r) {
    cout << "? " << l + 1 << " " << r + 1 << '\n';
    cout.flush();
    int sz = r - l + 1;
    int tot = 0;
    for (int i = 0; i < sz; i++) {
        int x;
        cin >> x;
        tot += (x >= l + 1 && x <= r + 1);
    }
    return tot;
}
int rec (int l, int r) {
    if (l == r) {
        return l + 1;
    }
    int ans = query(l, (l + r)/2);
    if (ans % 2 == 1) {
        return rec(l, (l + r)/2);
    } else {
        return rec((l + r)/2 + 1, r);
    }
}
void solve () {
    int n;
    cin >> n;
    int x = rec(0, n - 1);
    cout << "! " << x << '\n';
    cout.flush();
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
