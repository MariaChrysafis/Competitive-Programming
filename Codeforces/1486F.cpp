#include <bits/stdc++.h>
using namespace std;
class Tree {
public:
    vector<vector<int> > adj, dp;
    vector<int> pre, post;
    int cntr = 0;
    void add_edge (int u, int v) {
        adj[u].push_back(v), adj[v].push_back(u);
    }
    bool isAncestor (int u, int v) {
        return (pre[u] <= post[v] && post[u] >= post[v]);
    }
    void dfs (int curNode, int prevNode) {
        dp[curNode][0] = prevNode;
        for (int i = 1; i < dp[curNode].size(); i++) {
            dp[curNode][i] = dp[dp[curNode][i - 1]][i - 1];
        }
        pre[curNode] = cntr++;
        for (int i: adj[curNode]) {
            if (i != prevNode) {
                dfs (i, curNode);
            }
        }
        post[curNode] = cntr++;
    }
    int lca (int u, int v) {
        if (isAncestor(u, v)) {
            return u;
        }
        if (isAncestor(v, u)) {
            return v;
        }
        for (int i = dp[0].size() - 1; i >= 0; i--) {
            if (!isAncestor(dp[u][i], v)) {
                u = dp[u][i];
            }
        }
        return dp[u][0];
    }
    int goDown (int u, int v) {
        for (int i = dp[0].size() - 1; i >= 0; i--) {
            if (!isAncestor(dp[v][i], u)) {
                v = dp[v][i];
            }
        }
        return v;
    }
    Tree (int n) {
        adj.resize(n), pre.resize(n), post.resize(n), dp.assign(n, vector<int>(20));
    }
};
int propogate (Tree& myTree, vector<int64_t>& mark, int curNode, int prevNode) {
    for (int i: myTree.adj[curNode]) {
        if (i != prevNode) {
            mark[curNode] += propogate(myTree, mark, i, curNode);
        }
    }
    return mark[curNode];
}
int main () {
    int n;
    cin >> n;
    Tree myTree(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        myTree.add_edge(--u, --v);
    }
    myTree.dfs(0, 0);
    map<pair<int,int>,int64_t> c[n];
    map<int,int64_t> d[n];
    vector<int64_t> mark;
    mark.assign(n, false);
    vector<int64_t> dummy = mark;
    vector<int64_t> md = mark;
    vector<int64_t> cor = mark;
    vector<int64_t> a = mark;
    vector<int64_t> b = mark;
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        if (u == v) {
            dummy[u]++;
            continue;
        }
        if (myTree.isAncestor(v, u)) {
            swap(u, v);
        }
        if (myTree.isAncestor(u, v)) {
            ++b[v];
            ++d[u][myTree.goDown(u, v)];
            mark[myTree.goDown(u, v)]--;
            mark[v]++;
            if (myTree.dp[u][0] != u) {
                md[myTree.dp[u][0]]--;
            }
            md[v]++;
        } else {
            int lca = myTree.lca(u, v);
            ++b[u], ++b[v];
            int new_v = myTree.goDown(lca, v);
            int new_u = myTree.goDown(lca, u);
            ++c[lca][make_pair(min(new_u, new_v), max(new_u, new_v))];
            mark[myTree.goDown(lca, u)]--;
            mark[myTree.goDown(lca, v)]--;
            mark[v]++, mark[u]++;
            if (myTree.dp[lca][0] != lca) {
                md[myTree.dp[lca][0]] -= 2;
            }
            md[v]++, md[u]++;
            cor[lca]++;
        }
    }
    propogate(myTree, mark, 0, 0);
    propogate(myTree, md, 0, 0);
    for (int i = 0; i < cor.size(); i++) {
        md[i] -= cor[i];
    }
    int64_t ans = 0;
    for (int i = 0; i < n; i++) {
        //B and D
        for (auto& p: d[i]) {
            ans += p.second * b[i];
        }
        //C and B
        for (auto& p: c[i]) {
            ans += p.second * b[i];
        }
        //C and C
        int64_t tot = 0;
        for (auto& p: c[i]) {
            tot += p.second;
        }
        map<int,int64_t> dum;
        for (auto& p: c[i]) {
            dum[p.first.first] += p.second;
            dum[p.first.second] += p.second;
        }
        int64_t res = 0;
        for (auto& p: c[i]) {
            res += p.second * (tot - dum[p.first.first] - dum[p.first.second] + p.second);
        }
        ans += res/2;
        //C and D
         tot = 0;
        for (auto& p: d[i]) {
            tot += p.second;
        }
        for (auto& p: c[i]) {
            ans += (tot - d[i][p.first.first] - d[i][p.first.second]) * p.second;
        }
        //D and D
        tot = 0;
        for (auto& p: d[i]) {
            ans += tot * p.second;
            tot += p.second;
        }
        //A
        tot = 0;
        for (int j: myTree.adj[i]) {
            if (j != myTree.dp[i][0]) {
                a[j] = mark[j];
                tot += a[j];
            }
        }
        //A and C
        for (auto& p: c[i]) {
            ans += p.second * (tot - a[p.first.second] - a[p.first.first]);
        }
        //A and D
        for (auto& p: d[i]) {
            ans += p.second * (tot - a[p.first]);
        }
    }
    for (int i = 0; i < dummy.size(); i++) {
        ans += dummy[i] * md[i];
        ans += (dummy[i] - 1) * dummy[i]/2;
    }
    cout << ans << '\n';
}
