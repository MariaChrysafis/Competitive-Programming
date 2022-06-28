#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <cassert>
#include <ctime>
#include <cstdlib>
 
using namespace std;
const int MOD = 1e9;
#define ll long long
 
template<class T>
struct SegmentTree {
    void resz (int N) {
        N = (1 << ((int)floor(log2(N - 1)) + 1));
        this->N = N;
        val.assign(2 * N, ID);
    }

    void update (int x, T y) {
        x += N - 1;
        val[x] = y;
        while (x != 0) {
            x = (x - 1)/2;
            val[x] = merge(val[2 * x + 1], val[2 * x + 2]);
        }
    }

    T query (int ind, const int l, const int r, int tl, int tr) {
        if (tl >= l && tr <= r) {
            return val[ind];
        }
        if (tr < l || tl > r) {
            return ID;
        }
        return merge(query(2 * ind + 1, l, r, tl, (tl + tr)/2), query(2 * ind + 2, l, r, (tl + tr)/2 + 1, tr));
    }

    T query (int l, int r) {
        return query(0, l, r, 0, N - 1);
    }
    vector<T> val;
    T ID = 0;
    T merge (T x, T y) {
        return x + y;
    }
    int N;
};
 
struct HeavyLightDecomposition {
    vector<vector<int> > adj;
    vector<int> sub;
    vector<int> id;
    vector<int> topchain;
    vector<int> depth;
    vector<int> parent;
    SegmentTree <int64_t> st;
    vector<vector<int> > dp;
    vector<int> en;
    vector<int> ex;
    int cntr = 0;
    const int lg2 = 30;
 
    void add_edge(int u, int v) {
        adj[u].push_back(v), adj[v].push_back(u);
    }
 
    void rec(int curNode, int prevNode) {
        parent[curNode] = prevNode;
        en[curNode] = cntr++;
        if (prevNode != -1) {
            depth[curNode] = depth[prevNode] + 1;
        } else {
            depth[curNode] = 0;
        }
        sub[curNode] = 1;
        for (int i: adj[curNode]) {
            if (i != prevNode) {
                rec(i, curNode);
                sub[curNode] += sub[i];
            }
        }
        ex[curNode] = cntr++;
    }
 
    void resz (int n) {
        adj.resize(n);
        sub.resize(n);
        id.resize(n);
        topchain.assign(n, -1);
        parent.resize(n);
        st.resz(n + 1);
        ex.resize(n), en.resize(n);
    }
 
    void dfs(int curNode, int prevNode) {
        id[curNode] = cntr++;
        vector<pair<int, int> > vec;
        for (int i: adj[curNode]) {
            if (i != prevNode) {
                vec.push_back(make_pair(sub[i], i));
            }
        }
        dp[curNode].resize(32);
        dp[curNode][0] = max(prevNode, 0);
        for (int i = 1; i < dp[curNode].size(); i++) {
            dp[curNode][i] = dp[dp[curNode][i - 1]][i - 1];
        }
        if (!vec.empty()) {
            sort(vec.begin(), vec.end());
            reverse(vec.begin(), vec.end());
            topchain[vec[0].second] = topchain[curNode];
            for (int i = 1; i < vec.size(); i++) {
                topchain[vec[i].second] = vec[i].second;
            }
            for (auto &p: vec) {
                dfs(p.second, curNode);
            }
        }
    }
 
    int64_t f (int a, int b) {
        if (topchain[a] == topchain[b]) {
            return st.query(id[b], id[a]);
        }
        if (topchain[a] != a) {
            return f(dp[topchain[a]][0], b) + st.query(id[topchain[a]], id[a]);
        } else {
            return f(parent[a], b) + st.query(id[a], id[a]);
        }
    }

    int goUp (int u, int v) {
        for (int i = lg2; i >= 0; i--) {
            if (!isAncestor(dp[u][i], v)) {
                u = dp[u][i];
            }
        }
        return u;
    }
 
    bool isAncestor(int u, int v) {
        return (en[u] <= en[v] && ex[u] >= ex[v]);
    }
 
    int leastCommonAncestor(int u, int v) {
        if (isAncestor(u, v)) {
            return u;
        }
        if (isAncestor(v, u)) {
            return v;
        }
        for (int i = lg2; i >= 0; i--) {
            if (!isAncestor(dp[u][i], v)) {
                u = dp[u][i];
            }
        }
        return dp[u][0];
    }
 
    void upd(int ind, int x) {
        st.update(id[ind], x);
    }
};

HeavyLightDecomposition hlda, hldb;

vector<vector<pair<int,pair<int,int> > > > queries;

vector<int> a, b;

void dfs (int curNode, int prevNode) {
    a[curNode] = b[curNode] = 0;
    for (int i: hlda.adj[curNode]) {
        if (i != prevNode) {
            dfs(i, curNode);
            a[curNode] += b[i];
        }
    }
    b[curNode] = a[curNode];
    hlda.upd(curNode, a[curNode]);
    for (auto& p: queries[curNode]) {
        int cost = p.first;
        int u = p.second.first;
        int v = p.second.second;
        //cout << u << " " << v << " " << curNode << '\n';
        if (u == curNode) {
            swap(u, v);
        }
        int tot = 0;
        if (v == curNode) {
            tot = hlda.f(u, curNode) + cost;
            tot -= hldb.f(u, curNode) - hldb.f(curNode, curNode);
        } else {
            tot = hlda.f(u, curNode) + hlda.f(v, curNode) - hlda.f(curNode, curNode) + cost;
            tot -= hldb.f(u, curNode) + hldb.f(v, curNode) - 2 * hldb.f(curNode, curNode);
            if (hldb.f(u, curNode) != hldb.f(u, hldb.goUp(u, curNode)) - hldb.f(curNode, curNode)) {
                for (int i = 0; i < b.size(); i++) {
                    cout << hldb.st.query(hldb.id[i], hldb.id[i]) << ' ';
                }
                cout << '\n';
                cout << hldb.f(u, curNode) << '\n';
                cout << u + 1 << " " << curNode + 1 << " " << hldb.goUp(u, curNode) + 1 << '\n';
                exit(0);
            }
            assert(hldb.f(u, curNode) == hldb.f(u, hldb.goUp(u, curNode)) - hldb.f(curNode, curNode));
        }
        b[curNode] = max(b[curNode], tot);
    }
    hldb.upd(curNode, b[curNode]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, Q;
    cin >> N >> Q;
    vector<pair<int, int> > vec;
    hlda.resz(N), hldb.resz(N);
    assert(hlda.adj == hldb.adj);
    for (int i = 1; i < N; i++) {
        int u;
        cin >> u;
        --u;
        hlda.add_edge(u, i);
        hldb.add_edge(u, i);
    }
    hlda.depth.resize(N), hldb.depth.resize(N);
    hlda.dp.resize(N), hldb.dp.resize(N);
    hlda.rec(0, -1), hldb.rec(0, -1);
    hlda.topchain[0] = hldb.topchain[0] = 0;
    hlda.cntr = hldb.cntr = 0;
    hlda.dfs(0, -1), hldb.dfs(0, -1);
    a.resize(N), b.resize(N);
    queries.resize(N);
    while (Q--) {
        int u, v, c;
        cin >> u >> v >> c;
        u--, v--;
        queries[hlda.leastCommonAncestor(u, v)].push_back(make_pair(c, make_pair(u, v)));
    }
    dfs(0, 0);
    cout << b[0];

}
