#include <bits/stdc++.h>
 
using namespace std;

const int64_t M = 998244353;

struct modint {
    modint() : n(0) {}
    template <class T> modint(T n) { n %= M; if (n < 0) n += M; this->n = n; }
 
    modint & operator+=(const modint &r) { n += r.n; if (n >= M) n -= M; return *this; }
    modint & operator-=(const modint &r) { n -= r.n; if (n < 0) n += M; return *this; }
    modint & operator*=(const modint &r) { n = (int) ((long long) n * r.n % M); return *this; }
 
    modint & operator--() { if (--n == -1) n = M - 1; return *this; }
    modint & operator++() { if (++n == M) n = 0; return *this; }
    modint operator--(int) { modint t = *this; --*this; return t; }
    modint operator++(int) { modint t = *this; ++*this; return t; }
 
    modint operator-() const { return 0 - *this; }
    modint operator+() const { return *this; }
 
    int mod() const { return M; }
 
    friend modint operator+(modint l, const modint &r) { return l += r; }
    friend modint operator-(modint l, const modint &r) { return l -= r; }
    friend modint operator*(modint l, const modint &r) { return l *= r; }
    
    friend bool operator==(const modint &l, const modint &r) { return l.n == r.n; }
    friend bool operator!=(const modint &l, const modint &r) { return l.n != r.n; }
 
    friend ostream & operator<<(ostream &out, const modint &r) { return out << r.n; }
 
    int n;
};

modint binPow (modint x, int y) {
    modint ans = 1, res = x;
    while (y > 0) {
        if (y & 1) {
            ans *= res;
        }
        res *= res;
        y /= 2;
    }
    return ans;
}

modint inv (modint x) {
    return binPow(x, M - 2);
}

modint combo (vector<modint>& fact, int x, int y) {
    if (x < y) return 0;
    return fact[x] * inv(fact[x - y]) * inv(fact[y]);
}

int dist (pair<int,int> p1, pair<int,int> p2) {
    return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

vector<set<int> > adj;

class DisjointSetUnion {
public:
    vector<int> parent;
    vector<int> sz;
    DisjointSetUnion (int n) {
        for (int i = 0; i < n; i++) {
            sz.push_back(1), parent.push_back(i);
        }
    }
    int find_head (int x) {
        if (x == parent[x]) {
            return x;
        }
        return find_head(parent[x]);
    }
    void join (int u, int v) {
        u = parent[u], v = parent[v];
        if (u != v) {
            if (sz[u] >= sz[v]) {
                swap(u, v);
            }
            sz[v] += sz[u];
            parent[u] = v;   
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    adj.resize(n);
    vector<pair<int,int> > points;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        points.push_back(make_pair(x, y));
    }
    for (int i = 0; i < n; i++) {
        vector<pair<int,int> > distances;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                distances.push_back(make_pair(dist(points[i], points[j]), j));
            }
        }
        assert(distances.size() == n - 1);
        sort(distances.begin(), distances.end());
        for (int j = 0; j < distances.size(); j++) {
            if (distances[j].first == distances[0].first) {
                adj[i].insert(distances[j].second);
            }
        }
    }
    auto orig = adj;
    for (int i = 0; i < n; i++) {
        set<int> to_erase;
        for (int j: adj[i]) {
            if (!adj[j].count(i)) {
                to_erase.insert(j);
            }
        }
        for (int j: to_erase) {
            adj[i].erase(j);
        }
    }
    DisjointSetUnion dsu(n);
    for (int i = 0; i < n; i++) {
        for (int j: adj[i]) {
            dsu.join(i, j);
        }
    }
    vector<pair<int,bool> > vec;
    for (int i = 0; i < n; i++) {
        if (dsu.find_head(i) != i) {
            continue;
        }
        set<int> nodes;
        for (int j = 0; j < n; j++) {
            if (dsu.find_head(j) == dsu.find_head(i)) {
                nodes.insert(j);
            }
        } 
        bool clique = true;
        for (int i: nodes) {
            for (int j: orig[i]) {
                if (!nodes.count(j)) {
                    clique = false;
                }
            }
        }
        for (int i: nodes) {
            for (int j: nodes) {
                if (i != j && !adj[i].count(j)) {
                    clique = false;
                }
            }
        }
        if (nodes.size() == 1) clique = false;
        vec.push_back(make_pair(nodes.size(), clique));
    }
    vector<modint> fact;
    fact.push_back(1);
    while (fact.size() != n + 10) {
        fact.push_back(fact.back() * fact.size());
    }
    modint dp[vec.size() + 1][n + 1];
    for (int i = 1; i <= n; i++) {
        dp[0][i] = 0;
    }
    dp[0][0] = 1;
    for (int i = 1; i <= vec.size(); i++) {
        dp[i][0] = 0;
        for (int j = 1; j <= n; j++) {
            dp[i][j] = 0;
            if (j - vec[i - 1].first >= 0) {
                dp[i][j] += dp[i - 1][j - vec[i - 1].first] * combo(fact, n - (j - vec[i - 1].first), vec[i - 1].first) * fact[vec[i - 1].first];
            }
            if (vec[i - 1].second) {
                dp[i][j] += dp[i - 1][j - 1] * (n - j + 1);
            }
        }
    }
    modint tot = 0;
    for (int i = 0; i <= n; i++) {
        tot += dp[vec.size()][i];
    }
    cout << tot;
}
