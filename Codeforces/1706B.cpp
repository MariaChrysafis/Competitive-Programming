#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

void solve () {
    int n;
    cin >> n;
    int c[n];
    map<int,vector<pair<int,int> > > myMap;
    int cur_l = -1, cur_r = -1;
    for (int i = 0; i < n; i++) {
        cin >> c[i];
        if (cur_l == -1 && cur_r == -1) {
            cur_l = cur_r = i;
        } else if (c[i] == c[i - 1]) {
            cur_r++;
        } else if (c[i] != c[i - 1]) {
            myMap[c[i - 1]].push_back(make_pair(cur_l, cur_r));
            cur_l = i, cur_r = i;
        }
    }
    myMap[c[n - 1]].push_back(make_pair(cur_l, cur_r));
    for (int i = 1; i <= n; i++) {
        myMap[i].push_back(make_pair(0, 0));
        myMap[i].pop_back();
    }
    for (auto& p: myMap) {
        vector<pair<int,int> > vec = p.second;
        if (vec.empty()) {
            cout << 0 << ' ';
            continue;
        }
        int tot = vec[0].second - vec[0].first + 1;
        int last_brick = vec[0].second;
        for (int i = 1; i < vec.size(); i++) {
            if (abs(last_brick - vec[i].first) % 2 == 0) {
                vec[i].first++;
            }
            tot += vec[i].second - vec[i].first + 1;
            last_brick = vec[i].second;
        }
        cout << tot << ' ';
    }
    cout << '\n';
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
