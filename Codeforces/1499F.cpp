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

int n, k;
vector<vector<int> > adj;

vector<modint> dp1, dp2;
vector<modint> pref, suf;

void dfs (int curNode, int prevNode) {
    vector<vector<modint> > prev1, prev2;
    vector<int> children;
    for (int i: adj[curNode]) {
        if (i != prevNode) {
            children.push_back(i);
            dfs (i, curNode);
            prev1.push_back(dp1), prev2.push_back(dp2);
        }
    }
    dp1.assign(k + 1, 0), dp2.assign(k + 1, 0);
    pref.resize(children.size() + 1), suf.resize(children.size() + 1);
    pref[0] = 1, suf[children.size()] = 1;
    for (int d = 1; d <= k; d++) {
        if (k - d - 1 >= 0 && d - 2 >= 0) {
            for (int j = 0; j < children.size(); j++) {
                pref[j + 1] = (prev2[j][min(k - d - 1, d - 2)] + prev2[j][k]) * pref[j];
            }
            for (int j = (int)children.size() - 1; j >= 0; j--) {
                suf[j] = suf[j + 1] * (prev2[j][min(k - d - 1, d - 1)] + prev2[j][k]);
            }
        }
        for (int i = 0; i < children.size(); i++) {
            modint ans = prev1[i][d - 1];
            if (d == k || d == 1) {
                for (int j = 0; j < i; j++) {
                    if (min(k - d - 1, d - 2) >= 0) {
                        ans *= (prev2[j][min(k - d - 1, d - 2)] + prev2[j][k]);
                    } else {
                        ans *= prev2[j][k];
                    }
                }
                for (int j = i + 1; j < children.size(); j++) {
                    if (k - d - 1 >= 0) {
                        ans *= (prev2[j][min(k - d - 1, d - 1)] + prev2[j][k]);
                    } else {
                        ans *= prev2[j][k];
                    }
                }
            } else {
                ans *= pref[i] * suf[i + 1];
            }
            dp1[d] += ans;
        }
    }
    dp1[0] = 1;
    for (int j = 0; j < children.size(); j++) {
        dp1[0] *= prev2[j][k];
    }
    dp2[0] = dp1[0];
    for (int j = 1; j < dp2.size(); j++) {
        dp2[j] = dp2[j - 1] + dp1[j];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> k;
    adj.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v), adj[v].push_back(u);
    }
    dfs(0, 0);
    cout << dp2[k];
}
