#include <bits/stdc++.h>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
using namespace std;
int cntr;
map<pair<int,int>,int> m;
void dfs (vector<vector<int> > &adj, vector<int>&pre, vector<int>&depth, int curNode, int prevNode) {
    depth[curNode] = depth[prevNode] + 1;
    pre[curNode] = cntr++;
    m[make_pair(curNode, prevNode)] = cntr - 1;
    for (int i: adj[curNode]) {
        if (i != prevNode) {
            dfs (adj, pre, depth, i, curNode);
        }
    }
}
void solve () {
    int n;
    cin >> n;
    n = (1 << n);
    int root = 0;
    vector<vector<int> > adj(n);
    vector<pair<int,int> > edges;
    map<pair<int,int> ,int> myMap;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        myMap[make_pair(u, v)] = myMap[make_pair(v, u)] = edges.size();
        edges.push_back(make_pair(u, v));
        adj[u].push_back(v), adj[v].push_back(u);
    }
    vector<int> pre;
    pre.assign(n, false);
    cntr = 0;
    vector<int> depth;
    depth.assign(n, 0);
    cout << 1 << '\n';
    dfs(adj, pre, depth, root, root);
    for (int i = 0; i < n; i++) {
        if (depth[i] % 2 == 1) {
            cout << n + pre[i] << ' ';
        } else {
            cout << pre[i] << ' ';
        }
    }
    cout << '\n';
    for (auto& p: edges) {
        if (depth[p.first] < depth[p.second]) {
            swap(p.first, p.second);
        }
        //p.first is parent of p.second
        cout << pre[p.first] + n * !(depth[p.first] % 2) << ' ';
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
