#include <bits/stdc++.h>
using namespace std;
int main() {
    int Q, M, K;
    cin >> Q >> M >> K;
    vector<int> n(M), r(K);
    for (int i = 0; i < M; i++) cin >> n[i];
    for (int i = 0; i < K; i++) cin >> r[i];
    sort(n.begin(), n.end());
    reverse(n.begin(), n.end());
    sort(r.begin(), r.end());
    reverse(r.begin(), r.end());
    set<int> ss;
    ss.insert(0);
    int s_n = 0;
    for (int i = 0; i < M; i++) {
        s_n += n[i];
        ss.insert(s_n);
    }
    set<int> sr;
    int s_r = 0;
    sr.insert(0);
    for (int i = 0; i < K; i++) {
        s_r += r[i];
        sr.insert(s_r);
    }
    int s_val[s_n + 1];
    s_val[0] = 0;
    for (int i = 1; i <= s_n; i++) {
        s_val[i] = s_val[i - 1] + 1;
        s_val[i] -= (bool)ss.count(i - 1);
        s_val[i] += (bool)ss.count(i);
    }
    int r_val[s_r + 1];
    r_val[0] = 0;
    for (int i = 1; i <= s_r; i++) {
        r_val[i] = r_val[i - 1] + 1;
        r_val[i] -= (bool)sr.count(i - 1);
    }
    int ans = 0;
    for (int j = 0; j <= Q; j++) {
        ans = max(ans, r_val[min(j, s_r)] + s_val[min(Q - j, s_n)]);
    }
    bitset<150000> bs;
    bs.set(0);
    for (int i = 0; i < M; i++) {
        bs |= (bs << n[i]);
    }
    for (int i = 0; i <= Q; i++) {
        if (bs[i]) {
            ans = max(ans, i);
        }
    }
    cout << ans << '\n';
}
