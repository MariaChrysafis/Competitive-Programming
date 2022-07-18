#include <bits/stdc++.h>
using namespace std;

bool canDo (vector<pair<int,int> > v, int x) {
    if (x == 0) {
        return true;
    }
    for (auto& p: v) {
        while (p.first != 0 && (int)log2(p.first) == (int)log2(p.second)) {
            int bit = log2(p.first);
            p.first ^= (1 << bit), p.second ^= (1 << bit);
            if (x & (1 << bit)) {
                x ^= (1 << bit);
            }
        }
    }
    for (auto& p: v) {
        if (p.second != 0 && (1 << (int)log2(p.second)) > x) {
            return true;
        }
    }
    int cntr = 0;
    for (auto& p: v) {
        if (p.second != 0) {
            cntr += ((int)log2(p.second) == (int)log2(x));
        }
    }
    if (cntr >= 2) {
        return true;
    }
    for (auto& p: v) {
        if (p.second != 0 && (int)log2(p.second) == (int)log2(x)) {
            int bt = log2(p.second);
            p.first = 0;
            p.second -= (1 << bt);
            x -= (1 << bt);
            return canDo(v, x);
        }
    }
    return false;
}

bool canDo (vector<vector<pair<int,int>>> &vec, int x) {
    for (auto& v: vec) {
        if (!canDo(v, x)) {
            return false;
        }
    }
    return true;
}

int find_best (vector<vector<pair<int,int>>> &vec) {
    int tot = 0;
    for (int i = 30; i >= 0; i--) {
        if (canDo(vec, tot + (1 << i))) {
            tot += (1 << i);
        }
    }
    return tot;
}

int main() {
    int n, m;
    cin >> n >> m;
    int tot[m];
    for (int i = 0; i < m; i++) {
        cin >> tot[i];
    }
    vector<vector<pair<int,int>>> vec;
    for (int i = 0; i < m; i++) {
        vec.emplace_back();
        while (tot[i]--) {
            pair<int,int> p;
            cin >> p.first >> p.second;
            vec.back().push_back(p);
        }
    }
    cout << find_best(vec) << '\n';
    return 0;
}
