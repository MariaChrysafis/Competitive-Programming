#include <bits/stdc++.h>
 
using namespace std;

void solve () {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        while (a[i] % 2 == 0) {
            a[i] /= 2;
        }
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
        while (b[i] % 2 == 0) {
            b[i] /= 2;
        }
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    multiset<int> ma, mb;
    for (int i: a) {
        ma.insert(i);
    }
    for (int i: b) {
        mb.insert(i);
    }
    while (true) {
        if (mb.empty() || ma.empty()) {
            break;
        }
        auto end_b = mb.rbegin();
        auto end_a = ma.rbegin();
        //cout << *end_b << " " << *end_a << '\n';
        if (*end_b < *end_a) {
            break;
        }
        if (*end_b == *end_a) {
            mb.erase(mb.find(*end_b));
            ma.erase(ma.find(*end_a));
            continue;
        }
        int x = *end_b;
        mb.erase(mb.find(*end_b));
        mb.insert(x/2);
    }
    if (ma == mb) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
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
