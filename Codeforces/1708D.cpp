#include <bits/stdc++.h>

using namespace std;
const int MOD = 1e9 + 7;

bool comp (pair<int64_t,int64_t> p1, pair<int64_t,int64_t> p2) {
    return (p1.second < p2.second);
}

bool valid (int64_t x, vector<pair<int64_t,int64_t> > arr, int64_t q) {
    sort(arr.begin(), arr.end());
    vector<pair<int,int> > tot;
    for (int i = 0; i < x; i++) {
        tot.push_back(arr[i]);
    }
    sort(tot.begin(), tot.end(), comp);
    for (int i = 0; i < tot.size(); i++) {
        if (q <= 0) {
            return false;
        }
        q -= (tot[i].first > q);
    }
    return true;
}

void solve () {
    int n;
    cin >> n;
    vector<int64_t> arr;
    int zero = 0;
    for (int i = 0; i < n; i++) {
        int64_t x;
        cin >> x;
        if (x != 0) arr.push_back(x);
        else zero++;
    }
    while (arr.size() != 1) {
        if (arr.empty()) {
            cout << 0 << '\n';
            return;
        }
        vector<int64_t> v = arr;
        arr.clear();
        if (zero) arr.push_back(v[0]), zero--;
        for (int i = 1; i < v.size(); i++) {
            if (v[i] != v[i - 1]) arr.push_back(v[i] - v[i - 1]);
            else zero++;
        }
        sort(arr.begin(), arr.end());
    }
    cout << arr[0] << '\n';

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
