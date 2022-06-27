#include <bits/stdc++.h>
using namespace std;
int dfs (vector<vector<int> > &adj, vector<int>&sub, int curNode, int prevNode) {
    for (int i: adj[curNode]) {
        if (i != prevNode) {
            sub[curNode] += dfs(adj, sub, i, curNode);
        }
    }
    return sub[curNode];
}
void find_centroid (vector<vector<int> > &adj, vector<int>& sub, vector<int>& centroids, int curNode, int prevNode) {
    int n = adj.size();
    bool fine = !(n - sub[curNode] > n/2);
    for (int i: adj[curNode]) {
        if (i != prevNode) {
            find_centroid(adj, sub, centroids, i, curNode);
            if (sub[i] > n/2) {
                fine = false;
            }
        }
    }
    if (fine) {
        centroids.push_back(curNode);
    }
}
bool check (vector<vector<int> > &adj, int curNode) {
    queue<pair<int,int> > q;
    q.push(make_pair(curNode, 0));
    vector<int> depth;
    depth.assign(adj.size(), -1);
    while (!q.empty()) {
        pair<int,int> p = q.front();
        q.pop();
        if (depth[p.first] != -1) {
            continue;
        }
        depth[p.first] = p.second;
        for (int i: adj[p.first]) {
            q.push(make_pair(i, p.second + 1));
        }
    }
    vector<vector<int> > d;
    for (int i = 0; i < adj.size(); i++) {
        while (d.size() <= depth[i]) {
            vector<int> dummy;
            d.push_back(dummy);
        }
        d[depth[i]].push_back(i);
    }
    for (int i = 0; i < d.size(); i++) {
        set<int> s;
        for (int j: d[i]) {
            s.insert(adj[j].size());
        }
        if (s.size() > 1) {
            return false;
        }
    }
    return true;
}
vector<int64_t> id;
vector<bool> okay;
vector<int> leaves;
vector<int64_t> powr;
const int MOD = 1e9 + 7;
int first = -1;
void rec (vector<vector<int> >&adj, vector<int>& sub, int curNode, int prevNode) {
    okay[curNode] = true;
    vector<pair<int,int> > nodes;
    set<int> s;
    leaves[curNode] = -10;
    for (int i: adj[curNode]) {
        if (i != prevNode) {
            rec(adj, sub, i, curNode);
            nodes.push_back(make_pair(id[i], i));
            s.insert(id[i]);
            if (!okay[i]) {
                okay[curNode] = false;
            }
            if (leaves[curNode] == -10) {
                leaves[curNode] = leaves[i];
            } else {
                leaves[curNode] = -1;
            }
        }
    }
    if (leaves[curNode] == -10) {
        leaves[curNode] = curNode;
    }
    if (s.size() > 1) {
        okay[curNode] = false;
        if (first == -1) {
            first = curNode;
        }
    } 
    sort(nodes.begin(), nodes.end());
    id[curNode] = 1;
    for (auto& p: nodes) {
        id[curNode] = ((powr[sub[p.second] + 1] * id[curNode]) % MOD + id[p.second]) % MOD;
    }
    id[curNode] *= 2, id[curNode] %= MOD;
    //cout << curNode + 1 << " <-> " << id[curNode] << '\n';
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<vector<int> > adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v), adj[v].push_back(u);
    }
    vector<int> sub; 
    sub.assign(n, 1);
    int leaf = 0;
    for (int i = 0; i < n; i++) {
        if (adj[i].size() == 1) {
            leaf = i;
        }
    }
    dfs(adj, sub, leaf, leaf);
    assert(sub[leaf] == n);
    vector<int> centroids;
    
    find_centroid(adj, sub, centroids, leaf, leaf);
    for (int i: centroids) {
        if (check(adj, i)) {
            cout << i + 1 << '\n';
            exit(0);
        } 
    }
    
    id.resize(n);
    powr.push_back(1);
    while (powr.size() != n + 5) {
        powr.push_back(powr.back() * 2);
        powr.back() %= MOD;
    }
    okay.resize(n);
    leaves.assign(n, 0);
    rec(adj, sub, leaf, leaf);
    if (check(adj, leaf)) {
        cout << leaf + 1 << '\n';
        exit(0);
    }
    set<int> s;
    for (int i = first; i <= first; i++) {
        if (!okay[i]) {
            map<int,pair<int,int> > myMap;
            for (int j: adj[i]) {
                if (leaves[j] != -1) {
                    myMap[id[j]].first++;
                    myMap[id[j]].second = leaves[j];
                }
            }
            for (auto& p: myMap) {
                if (p.second.first == 1 && !s.count(p.second.second)) {
                    s.insert(p.second.second);
                    if (check(adj, p.second.second)) {
                        cout << p.second.second + 1 << '\n';
                        exit(0);
                    }
                }
            }

        }
    }
    cout << -1;
}
