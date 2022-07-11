#include <bits/stdc++.h>
using namespace std;
set<int> mySet;
vector<int> v;
int okay (int l, int r, int x, int bt) {
    while (l != r) {
        if ((v[l] & (1 << bt)) == (v[r] & (1 << bt))) {
            bt--;
            continue;
        }
        int left = l;
        int right = r;
        while (left != right) {
            int mid = (left + right + 1)/2;
            if (v[mid] & (1 << bt)) {
                right = mid - 1;
            } else {
                left = mid;
            }
        }
        if (x & (1 << bt)) {
            r = left;
        } else {
            l = left + 1;
        }
        bt--;
    }
    return l;
}
void solve (int l, int r, int bt, int k) {
    for (int i = l ; i <= r; i++) {
        int ind = okay(l, r, v[i], 30);
        if ((v[ind] ^ v[i]) >= k) {
            mySet.insert(v[ind]), mySet.insert(v[i]);
            return;
        } 
    }
    mySet.insert(v[l]);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    cin >> n >> k;
    v.resize(n);
    map<int,int> m;
    set<int> ms;
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        m[v[i]] = i;
        ms.insert(v[i]);
    }
    if (k == 0) {
        cout << v.size() << '\n';
        for (int i = 0; i < v.size(); i++) {
            cout << i + 1 << ' ';
        }
        exit(0);
    }
    v.clear();
    for (int i: ms) {
        v.push_back(i);
    }
    map<int,vector<int> > sieve;
    int mask = 0;
    for (int i = log2(k) + 1; i <= 30; i++) {
        mask += (1 << i);
    }
    for (int i = 0; i < v.size(); i++) {
        sieve[v[i] & mask].push_back(i);
    }
    for (auto& p: sieve) {
        solve(p.second[0], p.second.back(), 30, k);
    }
    if (mySet.size() <= 1) {
        cout << "-1\n";
        exit(0);
    }
    cout << mySet.size() << '\n';
    for (int j: mySet) {
        cout << m[j] + 1 << ' ';
    }
}
