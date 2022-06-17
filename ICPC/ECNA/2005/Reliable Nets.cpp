#include <bits/stdc++.h>
#define ll int64_t
#define pll pair<ll,ll>
using namespace std;
class Graph {
    vector<vector<int> > adj;
    vector<vector<int> > new_adj;
    vector<bool> hasVisited;
    vector<pair<int,int> > edges;
    vector<int> parent;
    vector<int> sub;
    vector<int> depth;
    void dfs (int curNode) {
        hasVisited[curNode] = true;
        for (int i: adj[curNode]) {
            if (!hasVisited[i]) {
                new_adj[i].push_back(curNode), new_adj[curNode].push_back(i);
                parent[i] = curNode;
                depth[i] = depth[curNode] + 1;
                dfs (i);
            }
        }
    }
public:
    void add_edge (int u, int v) {
        edges.push_back(make_pair(u, v));
        adj[u].push_back(v), adj[v].push_back(u);
    }
    Graph (int n) {
        new_adj.resize(n), adj.resize(n), hasVisited.assign(n, false), parent.assign(n, -1), sub.resize(n), depth.resize(n);
    }
    void fill (int curNode, int prevNode) {
        for (int i: new_adj[curNode]) {
            if (i != prevNode) {
                fill (i, curNode);
                sub[curNode] += sub[i];
            }
        }
    }
    bool read() {
        depth[0] = 0;
        dfs (0); 
        for (int i = 0; i < adj.size(); i++) {
            if (!hasVisited[i]) {
                return false;
            }
        }
        for (auto& p: edges) {
            if (parent[p.first] == p.second || parent[p.second] == p.first) {
                continue;
            }
            if (depth[p.first] > depth[p.second]) {
                swap(p.first, p.second);
            }
            sub[p.first] += -1;
            sub[p.second] += 1;
        }
        fill (0, 0);
        for (int i = 1; i < (int)adj.size(); i++) {
            if (sub[i] == 0) {
                return false;
            }
        }
        return true;
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int c = 0;
    while (true) {
        c++;
        int n, m;
        cin >> n >> m;
        if (!n) {
            exit(0);
        }
        vector<pair<pair<int,int> , int> > edges;
        for (int i = 0; i < m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            u--, v--;
            edges.push_back(make_pair(make_pair(u, v), w));
        }
        int ans = INT_MAX;
        for (int i = 0; i < (1 << (int)edges.size()); i++) {
            if (__builtin_popcount(i) <= n - 1) continue;
            Graph gr(n);
            int tot = 0;
            for (int j = 0; j < edges.size(); j++) {
                if (i & (1 << j)) {
                    tot += edges[j].second;
                    gr.add_edge(edges[j].first.second, edges[j].first.first);
                }
            }
            if (gr.read()) {
                ans = min(ans, tot);
            }
        }
        if (ans == INT_MAX) {
            cout << "There is no reliable net possible for test case " << c << ".\n";
        } else {
            cout << "The minimal cost for test case " << c << " is " << ans << ".\n";
        }
    }
}
