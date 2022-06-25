#include <bits/stdc++.h>
using namespace std;
void solve () {
    int64_t n, m;
    cin >> n >> m;
    vector<int64_t> a(n);
    vector<pair<int64_t,int64_t> > vec;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        int64_t res = a[i];
        int64_t cntr = 1;
        while (a[i] % m == 0) {
            res /= m;
            cntr *= m;
            a[i] /= m;
        }
        if (!vec.empty() && vec.back().first == res) {
            vec.back().second += cntr;
        } else {
            vec.push_back(make_pair(res, cntr));
        }
    }
    vector<int64_t> powr;
    powr.push_back(1);
    while (true) {
        powr.push_back(powr.back() * m);
        if (powr.back() > (int64_t)1e9) {
            powr.pop_back();
            break;
        }
    }
    int64_t k;
    cin >> k;
    vector<int64_t> b(k);
    for (int i = 0; i < k; i++) {
        cin >> b[i];
    }
    int64_t c = 0;
    for (int i = 0; i < k; i++) {
        c += (vec[c].second == 0);
        if (c == vec.size()) {
            cout << "No\n";
            return;
        }
        if (b[i] % vec[c].first != 0) {
            cout << "No\n";
            return;
        }
        int64_t res = b[i]/vec[c].first;
        bool fine = false;
        for (int j = 0; j < powr.size(); j++) {
            if (powr[j] == res) {
                vec[c].second -= res;
                fine = true;
            }
        }
        if (!fine) {
            cout << "No\n";
            return;
        }
    }
    for (auto& p: vec) {
        if (p.second != 0) {
            cout << "No\n";
            return;
        }
    }
    cout << "Yes\n";
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
