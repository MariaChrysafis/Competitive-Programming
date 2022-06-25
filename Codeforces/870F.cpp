#include <bits/stdc++.h>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
using namespace std;
int main() {
    long long n;
    cin >> n;
    vector<long long> p(n + 1);
    vector<long long> mu(n + 1);
    p.assign(n + 1, -1), mu.assign(n + 1, -1);
    for (long long i = 2; i <= n; i++) {
        if (p[i] == -1) {
            p[i] = i;
            for (long long j = i; j <= n; j += i) {
                if (p[j] == -1) {
                    p[j] = p[i];
                }
            }   
        }
    }
    mu[1] = 1;
    for (long long i = 2; i <= n; i++) {
        if (p[i/p[i]] == p[i]) {
            mu[i] = 0;
        } else {
            mu[i] = -mu[i/p[i]];
        }
    }
    long long edges = 0;
    for (long long i = 2; i <= n; i++) {
        long long pr = n/i;
        edges -= pr * (pr - 1)/2 * mu[i];
    }
    long long c = 1;
    for (long long i = 1; i <= n; i++) {
        c += (p[i] * 2 > n);
    }
    c = c * (n - c) + c * (c - 1)/2;
    vector<long long> cnt(n + 1);
    for (long long i = 2; i <= n; i++) {
        cnt[p[i]]++;
    }
    long long prev = 1;
    long long tot = 0;
    long long ans = 0;
    for (long long i = n; i >= 2; i--) {
        while ((prev + 1) * i <= n) {
            tot += cnt[++prev];
        }
        ans += tot * cnt[i];
        if (i * i <= n) ans -= cnt[i];
    }
    ans -= edges * 2;
    cout << ans + edges + 3 * ((n * (n - 1)/2) - ans/2 - edges - c) << '\n';
}
