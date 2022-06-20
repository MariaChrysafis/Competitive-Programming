#include <bits/stdc++.h>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
using namespace std;
int ans = 1;
void chmax (int &a, int b) {
    a = max(a, b);
    ans = max(ans, a + 1);
}
void solve2 (vector<int>& arr) {
    map<int,int> dp[arr.size()];
    for (int i = 0; i < arr.size(); i++) {
        for (int j = i + 1; j < arr.size(); j++) {
            if ((arr[j] - arr[i]) % (j - i) == 0) {
                chmax(dp[j][(arr[j] - arr[i])/(j - i)], dp[i][(arr[j] - arr[i])/(j - i)] + 1);
            }
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int64_t n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    const int bs = 90;
    for (int dif = -bs; dif <= bs; dif++) {
        vector<int> v;
        for (int i = 0; i < n; i++) {
            v.push_back((arr[i] - dif * i));
        }
        sort(v.begin(), v.end());
        int cur = v[0];
        int cnt = 1;
        for (int i = 1; i < v.size(); i++) {
            if (cur == v[i]) {
                cnt++;
            } else {
                cnt = 1, cur = v[i];
            }
            ans = max(ans, cnt);
        }
    }
    for (int i = 0; i < n; i += 1000) {
        vector<int> new_arr;
        for (int j = 0; j < 2000 && i + j < n; j++) {
            new_arr.push_back(arr[i + j]);
        }
        solve2(new_arr);
    }
    cout << n - ans;
}
