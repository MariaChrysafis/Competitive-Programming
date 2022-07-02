#include <bits/stdc++.h>
 
using namespace std;

class MergeSortTree {
    vector<int> v;
    vector<vector<vector<int> > > levels;
public:
    vector<int> merge (vector<int> a, vector<int> b) {
        vector<int> tot;
        int j = 0;
        for (int i = 0; i < a.size(); i++) {
            while (j != b.size() && a[i] > b[j]) {
                tot.push_back(b[j++]);
            }
            tot.push_back(a[i]);
        }
        while (j != b.size()) {
            tot.push_back(b[j++]);
        }
        return tot;
    }
    int res (vector<int>& v, int x) {
        if (v[0] > x) return 0;
        int l = 0;
        int r = v.size() - 1;
        while (l != r) {
            int m = (l + r + 1)/2;
            if (v[m] <= x) {
                l = m;
            } else {
                r = m - 1;
            }
        }
        return l + 1;
    }
    int query (int level, int ind, int l, int r, int x) {
        //in the range [l...r], how many are <= x
        //[0, (1 << level) - 1]
        //[(1 << level) * ind, (1 << level) * (ind + 1) - 1]
        int left = (1 << level) * ind;
        int right = (1 << level) * (ind + 1) - 1;
        if (left >= l && right <= r) {
            return res(levels[level][ind], x);
        }
        if (left > r || right < l) {
            return 0;
        }
        return query(level - 1, 2 * ind, l, r, x) + query(level - 1, 2 * ind + 1, l, r, x);
    }
    int query (int l, int r, int x) {
        return query(levels.size() - 1, 0, l, r, x); 
    }
    MergeSortTree (vector<int> v) {
        this-> v = v;
        while ((1 << (int)log2(v.size()) != v.size())) {
            v.push_back(0);
        }
        int sz = log2(v.size());
        sz++;
        levels.resize(sz);
        for (int i = 0; i < v.size(); i++) {
            vector<int> dum;
            dum.push_back(v[i]);
            levels[0].push_back(dum);
        }
        for (int i = 1; i < levels.size(); i++) {
            for (int j = 0; j < levels[i - 1].size(); j += 2) {
                levels[i].push_back(merge(levels[i - 1][j], levels[i - 1][j + 1]));
            }
        }
        /*
        for (auto& v1: levels){
            for (auto& v2: v1) {
                for (int i: v2) {
                    cout << i << ' ';
                }
                cout << "| ";
            }
            cout << '\n';
        }
        */
    }
};

class DQuery {
    MergeSortTree mst;
public:
    vector<int> gen (vector<int> v) {
        map<int,int> oc;
        vector<int> vec(v.size());
        for (int i = 0; i < v.size(); i++) {
            if (!oc.count(v[i])) {
                vec[i] = -1;
            } else {
                vec[i] = oc[v[i]];
            }
            oc[v[i]] = i;
        }
        return vec;
    }
    int query (int l, int r) {
        return mst.query(l, r, l - 1);
    }
    DQuery (vector<int> v) : mst(gen(v)) {

    }
};

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    DQuery dq(v);
    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << dq.query(l - 1, r - 1) << '\n';
    }
}
