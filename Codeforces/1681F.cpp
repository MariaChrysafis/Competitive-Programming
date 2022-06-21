#include <bits/stdc++.h>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
using namespace std;
struct segmentTree {
    vector<int> vec;
    vector<int> setLater;

    void push(int v, int tl, int tr) {
        if (setLater[v] == -1) {
            return;
        }
        int tm = (tl + tr)/2;
        setLater[2 * v + 1] = setLater[v];
        vec[2 * v + 1] = setLater[v] * (tr - tm);
        setLater[2 * v] = setLater[v];
        vec[2 * v] = setLater[v] * (tm - tl + 1);
        setLater[v] = -1;
    }

    const int INF = 0;

    int upd(int dum, int tl, int tr, int l, int r, int val) {
        if (tr < l || tl > r) {
            return INF;
        }
        if (tl >= l && tr <= r) {
            setLater[dum] = val;
            return (vec[dum] = val * (tr - tl + 1));
        }
        push(dum, tl, tr);
        int mid = (tl + tr) >> 1;
        upd(2 * dum, tl, mid, l, r, val);
        upd(2 * dum + 1, mid + 1, tr, l, r, val);
        return (vec[dum] = vec[2 * dum] + vec[2 * dum + 1]);
    }

    void upd(int l, int r, int val) {
        upd(1, 0, (int) vec.size() / 2 - 1, l, r, val);
    }

    int get(int dum, int tl, int tr, int &l, int &r) {
        if (tl > r || tr < l) {
            return INF;
        }
        if (tl >= l && tr <= r) {
            return vec[dum];
        }
        push(dum, tl, tr);
        int tm = (tl + tr) >> 1;
        return get(dum * 2, tl, tm, l, r) + get(dum * 2 + 1, tm + 1, tr, l, r);
    }

    int get(int l, int r) {
        return get(1, 0, (int) vec.size() / 2 - 1, l, r);
    }

    void resz(int n) {
        int sz = ((1 << (int) ceil(log2(n))));
        vec.assign(sz * 2, 0);
        setLater.assign(sz * 2, -1);
    }

};
template<class T>
class SegmentTree {
public:

    SegmentTree (int N) {
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
private:
    vector<T> val;
    T ID = 0;
    T merge (T x, T y) {
        return x + y;
    }
    int N;
};

int cntr = 0;
int dfs (vector<vector<int> > & adj, vector<int>&parent, vector<int> &sub, vector<int>&pre, vector<int>&post, int curNode, int prevNode) {
    parent[curNode] = prevNode;
    sub[curNode] = 1;
    pre[curNode] = cntr++;
    for (int i: adj[curNode]) {
        if (i != prevNode) {
            sub[curNode] += dfs (adj, parent, sub, pre, post, i, curNode);
        }
    }
    post[curNode] = cntr++;
    return sub[curNode];
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<vector<int> > adj(n);
    map<int,vector<pair<int,int> > > myMap;
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        adj[u].push_back(v), adj[v].push_back(u);
        myMap[w].push_back(make_pair(u, v));
    }
    SegmentTree<int> st(2 * n);
    segmentTree str;
    str.resz(2 * n);
    vector<int> sub(n), pre(n), post(n), parent(n);
    dfs (adj, parent, sub, pre, post, 0, 0);
    int64_t ans = 0;
    for (auto& p: myMap) {
        vector<pair<int,int> > children;
        for (auto& e: p.second) {
            if (parent[e.first] == e.second) {
                swap(e.first, e.second);
            }
            children.push_back(make_pair(sub[e.second], e.second));
        }
        children.push_back(make_pair(sub[0], 0));
        sort(children.begin(), children.end());
        int64_t tot = 0;
        map<int,int> myMap;
        for (auto& e: children) {
            //place at e.second
            int x = st.query(pre[e.second], post[e.second]);
            //tot -= (sub[e.second] - x - 1) * (sub[e.second] - x)/2;
            myMap[e.second] = sub[e.second] - x;
            //cout << "GET " << sub[e.second] - x << '\n';
            st.update(pre[e.second], myMap[e.second]);
        }
        reverse(children.begin(), children.end());
        for (auto& e: children) {
            str.upd(pre[e.second], post[e.second], e.second);
        }
        for (auto& e: p.second) {
            assert(myMap.count(str.get(pre[e.second], pre[e.second])));
            assert(myMap.count(str.get(pre[e.first], pre[e.first])));
            tot += (int64_t)myMap[str.get(pre[e.second], pre[e.second])] * (int64_t)myMap[str.get(pre[e.first], pre[e.first])];
            //cout << myMap[str.get(pre[e.second], pre[e.second])] << "<->" << myMap[str.get(pre[e.first], pre[e.first])] << '\n';
        }
        for (auto& e: children) {
            st.update(pre[e.second], 0);
        }
        ans += tot;
    }
    cout << ans;
}
