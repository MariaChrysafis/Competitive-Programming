#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, x;
    cin >> n >> x;
    int arr[n];
    map<int,int> cnt;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        arr[i] %= x;
        cnt[arr[i]]++;
    }
    if ((cnt.count(0) && cnt[0] * 2 > n) || (x % 2 == 0 && cnt.count(x/2) && cnt[x/2] * 2 > n)) {
        cout << -1;
        exit(0);
    }
    if (n == 1) {
        cout << -1;
        exit(0);
    }
    bool fine = true;
    for (auto& p: cnt) {
        if ((x - p.first) % x == p.first) {
            if (p.second > 1) {
                fine = false;
            } 
            continue;
        }
        if (cnt.count((x - p.first) % x)) {
            fine = false;
        }
    }
    if (fine) {
        cout << 1;
        exit(0);
    }
    if (n == 3) {
        cout << -1;
        exit(0);
    }
    for (auto& p: cnt) {
        if (p.second == 1 && cnt.count((x - p.first) % x) && cnt[(x - p.first) % x] + p.second == n) {
            cout << -1;
            exit(0);
        }
    }
    int ans = max(cnt[0], 2);
    if (x % 2 == 0) {
        ans = max(cnt[x/2], ans);
    }
    cout << ans;
}
