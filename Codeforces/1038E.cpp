#include <bits/stdc++.h>

using namespace std;
map<pair<int, int>, int> myMap;
vector <pair<int, int> > bs;

class DisjointSetUnion {
public:
    vector<int> parent;
    vector<int> compSize;
    const int n;
    int connectedComponents;

    int getConnectedComponents() const {
        return connectedComponents;
    }

public:
    DisjointSetUnion(int sz) : n(sz), connectedComponents(sz) {
        parent.resize(sz), compSize.resize(sz);
        for (int i = 0; i < n; i++) {
            parent[i] = i, compSize[i] = 1;
        }
    }

    int find_head(int x) const {
        int cur = x;
        while (cur != parent[cur]) {
            cur = parent[cur];
        }
        return cur;
    }

    void join(int x, int y) {
        x = find_head(x);
        y = find_head(y);
        if (x == y) {
            return;
        }
        if (compSize[x] > compSize[y]) {
            swap(x, y);
            //ensures that compSize[x1] <= compSize[y1]
        }
        parent[x] = y;
        compSize[y] += compSize[x];
        connectedComponents--;
    }

    bool comp(int x, int y) {
        return (find_head(x) == find_head(y));
    }
};

bool okay(int mask) {
    vector <pair<int, int> > edges;
    for (int i = 0; i < 6; i++) {
        if (mask & (1 << i)) {
            edges.push_back(bs[i]);
        }
    }
    DisjointSetUnion dsu(4);
    for (auto &p: edges) {
        dsu.join(p.first, p.second);
    }
    int c = 0;
    for (int i = 0; i < 4; i++) {
        c += (dsu.compSize[i] == 2);
    }
    return (c != 2);

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector < pair < int, pair < int, int > > > v1;
    map<int, int> tot;
    for (int i = 0; i < n; i++) {
        int c1, val, c2;
        cin >> c1 >> val >> c2;
        --c1, --c2;
        if (c1 != c2) v1.push_back(make_pair(val, make_pair(c1, c2)));
        else tot[c1] += val;
    }
    n = v1.size();
    int dp[n + 1][(1 << 4)][(1 << 6)];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < (1 << 4); j++) {
            for (int dum = 0; dum < (1 << 6); dum++) {
                dp[i][j][dum] = -INT_MAX;
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            bs.push_back(make_pair(i, j));
        }
    }
    for (int i = 0; i < bs.size(); i++) {
        myMap[bs[i]] = i, myMap[make_pair(bs[i].second, bs[i].first)] = i;
    }
    dp[0][0][0] = 0;
    int myMax = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < (1 << 4); j++) { //mask of xor
            for (int dum = 0; dum < (1 << 6); dum++) {
                dp[i][j][dum] = dp[i - 1][j][dum];
                for (int prev_j = 0; prev_j < (1 << 4); prev_j++) {
                    int x = (prev_j ^ ((1 << v1[i - 1].second.first) ^ (1 << v1[i - 1].second.second)));
                    if (x != j) {
                        continue;
                    }
                    for (int prev_dum = 0; prev_dum < (1 << 6); prev_dum++) {
                        x = (prev_dum | (1 << myMap[v1[i - 1].second]));
                        if (x != dum) continue;
                        dp[i][j][dum] = max(dp[i][j][dum], dp[i - 1][prev_j][prev_dum] + v1[i - 1].first);
                    }
                    int k = 0;
                    for (int d = 0; d < 6; d++) {
                        if ((1 << d) & dum) {
                            k |= (1 << bs[d].first);
                            k |= (1 << bs[d].second);
                        }
                    }
                    if (__builtin_popcount(j) <= 2 && okay(dum)) {
                        int ans = dp[i][j][dum];
                        for (int t = 0; t < 4; t++) {
                            if (k & (1 << t)) {
                                ans += tot[t];
                            }
                        }
                        myMax = max(myMax, ans);
                    }
                }
            }
        }
    }
    cout << max(myMax, max(max(tot[0], tot[1]), max(tot[2], tot[3])));
}
