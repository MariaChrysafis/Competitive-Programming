#include <bits/stdc++.h>
using namespace std;
class SparseTableMax {
    vector<vector<int> > dp;
public:
    int query (int l, int r) {
        int sz = log2(r - l + 1);
        return max(dp[l][sz], dp[r - (1 << sz) + 1][sz]);
    }
    SparseTableMax (vector<int> v) {
        dp.resize(v.size());
        for (int i = 0; i < v.size(); i++) {
            dp[i].resize(20);
            dp[i][0] = v[i];
        }
        for (int j = 1; j < 20; j++) {
            for (int i = 0; i < v.size(); i++) {
                dp[i][j] = max(dp[i][j - 1], dp[min(i + (1 << (j - 1)), (int)v.size() - 1)][j - 1]);
            }
        }
    }
};
class SparseTableMin {
    vector<vector<int> > dp;
public:
    int query (int l, int r) {
        int sz = log2(r - l + 1);
        return min(dp[l][sz], dp[r - (1 << sz) + 1][sz]);
    }
    SparseTableMin (vector<int> v) {
        dp.resize(v.size());
        for (int i = 0; i < v.size(); i++) {
            dp[i].resize(20);
            dp[i][0] = v[i];
        }
        for (int j = 1; j < 20; j++) {
            for (int i = 0; i < v.size(); i++) {
                dp[i][j] = min(dp[i][j - 1], dp[min(i + (1 << (j - 1)), (int)v.size() - 1)][j - 1]);
            }
        }
    }
};
void solve () {
    int n;
    cin >> n;
    vector<int> arr(n);
    map<int,int> m;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        m[arr[i]] = i;
    }
    SparseTableMax stmax(arr);
    SparseTableMin stmin(arr);
    int cur = 0;
    int ans = 0;
    while (cur != n - 1) {
        //cout << cur << '\n';
        ans++;
        if (arr[cur] < arr[cur + 1]) {
            int l = cur;
            int r = n - 1;
            while (l != r) {
                int m = (l + r + 1)/2;
                if (stmin.query(cur, m) == arr[cur]) {
                    l = m;
                } else {
                    r = m - 1;
                }
            }
            //[cur...l]
            int a = stmax.query(cur, l);
            cur = m[a];
        } else {
            int l = cur;
            int r = n - 1;
            while (l != r) {
                //cout << l << "<->" << r << '\n';
                int m = (l + r + 1)/2;
                if (stmax.query(cur, m) == arr[cur]) {
                    l = m;
                } else {
                    r = m - 1;
                }
            }
            //[cur...l]
            int a = stmin.query(cur, l);
            cur = m[a];
        }
    }
    cout << ans << '\n';
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
