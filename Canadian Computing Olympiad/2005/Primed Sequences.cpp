#include <bits/stdc++.h>
#define ll int64_t
#define pll pair<ll,ll>
using namespace std;

ll binpower(ll base, ll e, ll mod) {
    ll result = 1;
    base %= mod;
    while (e) {
        if (e & 1)
            result = (ll)result * base % mod;
        base = (ll)base * base % mod;
        e >>= 1;
    }
    return result;
}
bool check_composite(ll n, ll a, ll d, int s) {
    ll x = binpower(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; r++) {
        x = (ll)x * x % n;
        if (x == n - 1)
            return false;
    }
    return true;
};
bool MillerRabin(int n) { // returns true if n is prime, else returns false.
    if (n < 2)
        return false;

    int r = 0;
    int d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }

    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == a)
            return true;
        if (check_composite(n, a, d, r))
            return false;
    }
    return true;
}
int gcd (int a, int b) {
    if (!a || !b) return max(a, b);
    return gcd(max(a, b) % min(a, b), min(a, b));
}
void solve ()  {
    int n;
    cin >> n;
    int arr[n];
    int g = 0;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        g = gcd(g, arr[i]);
    }
    if (g != 1) {
        cout << "This sequence is anti-primed.\n";
        return;
    }
    int pref[n + 1];
    pref[0] = 0;
    for (int i = 1; i <= n; i++) {
        pref[i] = pref[i - 1] + arr[i - 1];
    }
    int myMin = INT_MAX;
    for (int sz = 2; sz <= n; sz++) {
        for (int i = 0; i + sz - 1 < n; i++) {
            int ans = pref[i + sz] - pref[i];
            if (ans % 2 != 0 && ans % 3 != 0 && MillerRabin(ans)) {
                cout << "Shortest primed subsequence is length " << sz << ": ";
                for (int k = i; k <= i + sz - 1; k++) {
                    cout << arr[k] << ' ';
                }
                cout << '\n';
                return;
            }
        }
    }
    cout << "This sequence is anti-primed.\n";
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
