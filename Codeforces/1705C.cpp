#include <bits/stdc++.h>

using namespace std;
void solve () {
    int64_t n, c, q;
    cin >> n >> c >> q;
    string s;
    cin >> s;
    vector<pair<pair<int64_t,int64_t>,pair<int64_t,int64_t> > > vec;
    int64_t tr = s.length() -1;
    vec.push_back(make_pair(make_pair(0, s.length() - 1), make_pair(0, s.length() - 1)));
    for (int64_t i = 0; i < c; i++) {
        int64_t l, r;
        cin >> l >> r;
        l--, r--;
        vec.push_back(make_pair(make_pair(tr + 1, tr + 1 + r - l), make_pair(l, r)));
        tr += r - l + 1;
        //cout << vec.back().first.first << " " << vec.back().first.second << " " << vec.back().second.first << " " << vec.back().second.second << '\n';
    }
    while (q--) {
        int64_t x;
        cin >> x;
        x--;
        for (int64_t i = vec.size() - 1; i >= 0; i--) {
            if (vec[i].first.first <= x && vec[i].first.second >= x) {
                x -= vec[i].first.first;
                x += vec[i].second.first;
            }
        }
        cout << s[x] << '\n';
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
