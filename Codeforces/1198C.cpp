#include <bits/stdc++.h>
using namespace std;
void solve () {
    int n, m;
    cin >> n >> m;
    vector<pair<int,int> > edges;
    map<pair<int,int>,int> ind;
    vector<int> adj[3 * n];
    vector<int> nodes;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v), adj[v].push_back(u);
        ind[make_pair(u, v)] = i;
        edges.push_back(make_pair(u, v));
    }
    for (int i = 0; i < 3 * n; i++) {
        nodes.push_back(i);
    }
    int t = 10;
    while (t--) {
        random_shuffle(nodes.begin(), nodes.end());
        vector<bool> marked;
        marked.assign(3 * n, false);
        int c = 0;
        for (int i: nodes) {
            bool fine = true;
            for (int j: adj[i]) {
                if (marked[j]) {
                    fine = false;
                }
            }
            if (!fine) {
                continue;
            }
            marked[i] = true;
            c++;
        }
        if (c >= n) {
            vector<int> v;
            for (int i = 0; i < 3 * n; i++) {
                if (marked[i]) {
                    v.push_back(i);
                }
            }
            cout << "IndSet\n";
            for (int j = 0; j < n; j++) {
                cout << v[j] + 1 << ' ';
            }
            cout << '\n';
            return;
        }
    }
    t = 10;
    while (t--) {
        random_shuffle(edges.begin(), edges.end());
        vector<bool> marked;
        marked.assign(3 * n, false);
        vector<int> indices;
        for (int i = 0; i < edges.size(); i++) { 
            auto p = edges[i];
            if (marked[p.first] || marked[p.second]) {
                continue;
            }
            marked[p.first] = marked[p.second] = true;
            indices.push_back(i);
        }
        if (indices.size() >= n) {
            cout << "Matching\n";
            for (int j = 0; j < n; j++) {
                cout << ind[edges[indices[j]]] + 1 << ' ';
            }
            cout << '\n';
            return;
        }
        //cout << "GET " << indices.size() << '\n';
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int tc;
    cin >> tc;
    while (tc--) {
        solve();
    }
}
