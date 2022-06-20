#include <bits/stdc++.h>
using namespace std;
void solve() {
    int n;
    cin >> n;
    vector<set<int> > adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].insert(v), adj[v].insert(u);
    }
    if (n == 1) {
        cout << 0 << '\n';
        return;
    }
    queue<int> q;
    int leaves = 0;
    for (int i = 0; i < adj.size(); i++) {
        //leaves += (adj[i].size() == 1);
        if (adj[i].size() == 1) {
            leaves++, q.push(i);
        }
    }
    if (leaves == 2) {
        cout << 1 << '\n';
        return;
    }
    int ans = INT_MAX;
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        if (adj[*adj[x].begin()].size() == 2) {
            adj[*adj[x].begin()].erase(x);
            q.push(*adj[x].begin());
            adj[x].clear();
        }
    }
    int x = 0;
    map<int,int> myMap;
    for (int j = 0; j < adj.size(); j++) {
        if (adj[j].size() == 1) {
            myMap[*adj[j].begin()]++;
        }
    }
    for (auto& p: myMap) {
        x += p.second - 1;
    }
    ans = min(ans, x);
    cout << ans << '\n';
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
