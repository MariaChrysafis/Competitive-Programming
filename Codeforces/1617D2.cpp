#include <bits/stdc++.h>
 
using namespace std;

vector<int> arr;

int query (int a, int b, int c) {
    cout << "? " << a + 1 << " " << b + 1 << " " << c + 1 << '\n';
    int x;
    cin >> x;
    return x;
    //exit(0);
    //cout << "? " << a + 1 << " " << b + 1 << " " << c + 1 << '\n';
    int cnt[2];
    cnt[0] = cnt[1] = 0;
    cnt[arr[a]]++, cnt[arr[b]]++, cnt[arr[c]]++;
    if (cnt[0] > cnt[1]) {
        return 0;
    } else {
        return 1;
    }
}
void solve () {
    int n = arr.size();
    cin >> n;
    int res[n/3];
    for (int i = 0; i <= 0; i++) {
        res[i] = query(3 * i, 3 * i + 1, 3 * i + 2);
    }
    vector<int> v;
    v.assign(n, -1);
    for (int i = 1; i < n/3; i++) {
        res[i] = query(3 * i, 3 * i + 1, 3 * i + 2);
        if (res[i] != res[i - 1]) {
            int l0 = 3 * (i - 1);
            int l1 = 3 * (i - 1) + 1;
            int l2 = 3 * (i - 1) + 2;
            int r0 = 3 * i;
            int r1 = 3 * i + 1;
            int r2 = 3 * i + 2;
            if (query(l1, l2, r0) == res[i - 1] && query(l1, l2, r1) == res[i - 1]) {
                v[l1] = v[l2] = res[i - 1], v[l0] = !(query(l0, l1, r0) == res[i - 1] && query(l0, l1, r1) == res[i - 1]) ^ res[i - 1];
            } else if (query(l0, l2, r0) == res[i - 1] && query(l0, l2, r1) == res[i - 1]) {
                v[l0] = v[l2] = res[i - 1], v[l1] = !res[i - 1];
            } else {
                v[l1] = v[l0] = res[i - 1], v[l2] = !res[i - 1];
            }
            int one_index = -1, zero_index = -1;
            for (int j = 0; j < n; j++) {
                if (v[j] == 0) zero_index = j;
                else if (v[j] == 1) one_index = j;
            }
            for (int j = i; j >= 0; j--) {
                if (v[3 * j] != -1) continue;
                int ind = (res[j] ? zero_index : one_index);
                assert(ind != -1);
                int q01 = query(ind, 3 * j, 3 * j + 1);
                int q12 = query(ind, 3 * j + 1, 3 * j + 2);
                if (q01 != v[ind]) {
                    v[3 * j] = v[3 * j + 1] = !v[ind];
                    if (q12 == v[ind]) v[3 * j + 2] = v[ind];
                    else v[3 * j + 2] = !v[ind];
                }
                if (q12 != v[ind]) {
                    v[3 * j + 1] = v[3 * j + 2] = !v[ind];
                    if (q01 == v[ind]) v[3 * j] = v[ind];
                    else v[3 * j] = !v[ind];
                }
                if (q12 == v[ind] && q01 == v[ind]) {
                    v[3 * j + 2] = v[3 * j] = !v[ind], v[3 * j + 1] = v[ind];
                }
                assert(v[3 * j + 1] != -1 && v[3 * j] != -1 && v[3 * j + 2] != -1);
                if (v[3 * j] == 0) zero_index = 3 * j;
                else one_index = 3 * j;
                if (v[3 * j + 1] == 0) zero_index = 3 * j + 1;
                else one_index = 3 * j + 1;
                if (v[3 * j + 2] == 0) zero_index = 3 * j + 2;
                else one_index = 3 * j + 2;
            }
            for (int j = 3 * (i + 1); j < n; j++) {
                v[j] = query(one_index, zero_index, j);
            }
            break;
        }
    }
    vector<int> tot;
    for (int j = 0; j < v.size(); j++) {
        if (!v[j]) {
            tot.push_back(j + 1);
        }
    }
    cout << "! " << tot.size() << ' ';
    for (int j: tot) cout << j << ' ';
    cout << '\n';
}
int main () { //
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    exit(0);
}
