#include <bits/stdc++.h>
using namespace std;
//Range Set & Range Bitwise Or
class SegmentTree {
public:
    vector<int64_t> val;
    vector<int64_t> to_set;
    void push (int x) {
        if (to_set[x] == -1) {
            return;
        }
        to_set[2 * x + 1] = to_set[x];
        to_set[2 * x + 2] = to_set[x];
        val[2 * x + 1] = to_set[x];
        val[2 * x + 2] = to_set[x];
        to_set[x] = -1;
    }
    void update (int dt, int tl, int tr, int l, int r, int64_t x) {
        if (l <= tl && r >= tr) {
            to_set[dt] = val[dt] = x;
            return;
        }
        if (l > tr || r < tl) {
            return;
        }
        push(dt);
        update(2 * dt + 1, tl, (tl + tr) / 2, l, r, x);
        update(2 * dt + 2, (tl + tr)/2 + 1, tr, l, r, x);
        val[dt] = bitwiseOr(val[2 * dt + 1], val[2 * dt + 2]);
    }
    void update (int l, int r, int64_t x) {
        update(0, 0, (int)val.size()/2 - 1, l, r, x);
    }
    int64_t bitwiseOr (int64_t x, int64_t y) {
        if (x == -1) {
            return y;
        }
        if (y == -1) {
            return x;
        }
        return x | y;
    }
    int64_t query (int dt, int tl, int tr, int l, int r) {
        if (l <= tl && r >= tr) {
            return val[dt];
        }
        if (l > tr || r < tl) {
            return -1;
        }
        push(dt);
        return bitwiseOr(query(2 * dt + 1, tl, (tl + tr) / 2, l, r), query(2 * dt + 2, (tl + tr)/2 + 1, tr, l, r));
    }
    int64_t query (int l, int r) {
        return query(0, 0, (int)val.size()/2 - 1, l, r);
    }
    SegmentTree (int n) {
        n = (1 << ((int)log2(n) + 1));
        val.assign(2 * n, 0);
        to_set.assign(2 * n, -1);
    }
};
class Tree {
public:
    Tree (int n) {
        adj.resize(n), pre.resize(n), post.resize(n);
    }
    vector<vector<int > > adj;
    int cntr = 0;
    vector<int> pre, post;
    void dfs (int curNode, int prevNode) {
        pre[curNode] = cntr++;
        for (int i: adj[curNode]) {
            if (i != prevNode) {
                dfs (i, curNode);
            }
        }
        post[curNode] = cntr++;
    }
    void add_edge (int u, int v) {
        adj[u].push_back(v), adj[v].push_back(u);
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q;
    cin >> n >> q;
    SegmentTree st(2 * n);
    vector<int> color(n);
    for (int i = 0; i < n; i++) {
        cin >> color[i];
        color[i]--;
    }
    Tree myTree(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v; 
        cin >> u >> v;
        u--, v--;
        myTree.add_edge(u, v);
    }
    myTree.dfs(0, 0);
    for (int i = 0; i < n; i++) {
        st.update(myTree.pre[i], myTree.pre[i], ((int64_t)1 << color[i]));
        st.update(myTree.post[i], myTree.post[i], ((int64_t)1 << color[i]));
    }
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int v, c;
            cin >> v >> c;
            c--;
            v--;
            st.update(myTree.pre[v], myTree.post[v], ((int64_t)1 << c));
        } else {
            int v; 
            cin >> v;
            v--;
            cout << __builtin_popcountll(st.query(myTree.pre[v], myTree.post[v])) << '\n';
        }
    }
}
