#include <bits/stdc++.h>
using namespace std;

struct SegmentTree {
    vector<int64_t> val;
    int N;
    int64_t query (int dum, int tl, int tr, int l, int r) {
        if (tl >= l && tr <= r) {
            return val[dum];
        }
        if (tl > r || tr < l) {
            return 0;
        }
        return query(2 * dum + 1, tl, (tl + tr)/2, l, r) + query(2 * dum + 2, (tl + tr)/2 + 1, tr, l, r);
    }
    int64_t query (int l, int r) {
        return query(0, 0, N - 1, l, r);
    }
    void update (int x, int y) {
        val[x += N - 1] = y;
        while (x != 0) {
            x = (x - 1)/2;
            val[x] = val[2 * x + 1] + val[2 * x + 2];
        }
    }
    SegmentTree (int n) {
        N = (1 << (int)log2(n)) * 2;
        val.assign(2 * N, 0);
    }
};

const int MOD = 998244353;

int64_t binPow (int64_t x, int y) {
    int64_t ans = 1, res = x;
    while (y > 0) {
        if (y & 1) {
            ans *= res, ans %= MOD;
        }
        res *= res, res %= MOD, y /= 2;
    }
    return ans;
}

int64_t inv (int64_t x) {
    return binPow(x, MOD - 2);
}

int64_t frac (int64_t x, int64_t y) {
    return (x * inv(y)) % MOD;
}

int64_t mult (int64_t x, int64_t y) {
    return (x * y) % MOD;
} 

int64_t blank (int n) {
    int64_t fact = 1;
    for (int i = 1; i <= n; i++) {
        fact *= i, fact %= MOD;
    }
    fact *= n, fact %= MOD, fact *= inv(4), fact %= MOD, fact *= n - 1, fact %= MOD;
    return fact;
}

vector<int> remove_negatives (vector<int> p) {
    vector<int> q;
    for (int i = 0; i < p.size(); i++) {
        if (p[i] >= 0) {
            q.push_back(p[i]);
        }
    }
    return q;
}

int64_t inversions (vector<int> p) {
    int n = p.size();
    p = remove_negatives(p);
    SegmentTree st(n + 2);
    int64_t ans = 0;
    for (int i = 0; i < p.size(); i++) {
        ans += st.query(p[i] + 1, n + 1);
        ans %= MOD;
        st.update(p[i], 1);
    }
    return ans;
}

int solve (vector<int> p) {
    vector<int64_t> fact;
    fact.push_back(1);
    while (fact.size() != p.size() + 1) {
        fact.push_back((fact.back() * fact.size()) % MOD);
    }
    set<int> s;
    for (int i: p) {
        s.insert(i);
    }
    s.erase(-1);
    int64_t c = inversions(p) % MOD;
    c *= fact[p.size() - s.size()];
    c %= MOD;
    int n = p.size();
    int pref[n + 1];
    pref[0] = 0;
    for (int i = 1; i <= n; i++) {
        pref[i] = pref[i - 1] + 1 - (bool)s.count(i);
    }
    int neg = 0;
    int tot_neg = n - s.size();
    c += blank(tot_neg);
    c %= MOD;
    for (int i = 0; i < p.size(); i++) {
        neg += (p[i] == -1);
        if (p[i] != -1) {
            c += mult(tot_neg - neg, mult(fact[tot_neg - 1], pref[p[i]]));
            c += mult(mult(fact[tot_neg - 1], neg), pref[n] - pref[p[i]]);
            c %= MOD;
        }
    }
    c = frac(c, fact[tot_neg]);
    return c;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }
    cout << solve(p) << '\n';
}
