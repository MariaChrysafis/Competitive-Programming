#include <bits/stdc++.h>
 
using namespace std;

struct segmentTree {
    vector<int64_t> vec;
    vector<int64_t> addLater;
    vector<pair<int, int> > rng;
 
    void push(int v) {
        int64_t sz = rng[v].second - rng[v].first + 1;
        addLater[2 * v + 1] += addLater[v];
        vec[2 * v + 1] += addLater[v] * sz / 2;
        addLater[2 * v] += addLater[v];
        vec[2 * v] += addLater[v] * sz / 2;
        addLater[v] = 0;
    }
 
    void upd(int dum, int tl, int tr, int l, int r, int64_t val) {
        if (tr < l || tl > r) {
            return;
        }
        if (tl >= l && tr <= r) {
            addLater[dum] += val;
            vec[dum] += val * (rng[dum].second - rng[dum].first + 1);
            return;
        }
        push(dum);
        int mid = (tl + tr) >> 1;
        upd(2 * dum, tl, mid, l, r, val);
        upd(2 * dum + 1, mid + 1, tr, l, r, val);
        vec[dum] = vec[2 * dum] + vec[2 * dum + 1];
    }
 
    void upd(int l, int r, int64_t val) {
        upd(1, 0, (int) vec.size() / 2 - 1, l, r, val);
    }
 
    int64_t get(int dum, int tl, int tr, int &l, int &r) {
        if (tl > r || tr < l) {
            return 0;
        }
        if (tl >= l && tr <= r) {
            return vec[dum];
        }
        push(dum);
        int tm = (tl + tr) >> 1;
        return get(dum * 2, tl, tm, l, r) + get(dum * 2 + 1, tm + 1, tr, l, r);
    }
 
    int64_t get(int l, int r) {
        return get(1, 0, (int) vec.size() / 2 - 1, l, r);
    }
 
    void build(int dum, int l, int r) {
        rng[dum] = make_pair(l, r);
        if (l == r) {
            return;
        }
        int m = (l + r) / 2;
        build(2 * dum, l, m);
        build(2 * dum + 1, l, m);
    }
 
    void resz(int n) {
        int sz = ((1 << (int) ceil(log2(n))));
        vec.resize(sz * 2);
        addLater.resize(sz * 2);
        rng.resize(addLater.size());
        build(1, 0, (int) vec.size() / 2 - 1);
    }
 
};

int main() {
    int n, q;
    cin >> n >> q;
    set<pair<pair<int,int>,int> > intervals; //left interval, right interval, value
    for (int i = 0; i < n; i++) {
        intervals.insert(make_pair(make_pair(i, i), i + 1));
    }
    segmentTree st;
    st.resz(n);
    int tot = 0;
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int l, r, x;
            cin >> l >> r >> x;
            l--, r--;
            auto it = intervals.upper_bound(make_pair(make_pair(l + 1, -1), -1));
            it--;
            vector<pair<pair<int,int>,int> > vec;
            while (true) {
                if (it == intervals.end() || (*it).first.first > r) {
                    break;
                }
                vec.push_back(*it);
                it++;
            }
            for (auto& p: vec) {
                intervals.erase(p);
                if (p.first.first < l) {
                    intervals.insert(make_pair(make_pair(p.first.first, l - 1), p.second));
                    p.first.first = l;
                } 
                if (p.first.second > r) {
                    intervals.insert(make_pair(make_pair(r + 1, p.first.second), p.second));
                    p.first.second = r;
                }
                st.upd(p.first.first, p.first.second, abs(p.second - x));
                tot += (p.first.second - p.first.first + 1) * abs(p.second - x);
            }
            intervals.insert(make_pair(make_pair(l, r), x));
        } else {
            int l, r;
            cin >> l >> r;
            cout << st.get(l - 1, r - 1) << '\n';
        }
    }
}
