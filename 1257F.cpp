#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    map<int,int> cnt;
    set<int> s;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        s.insert(arr[i]);
        cnt[__builtin_popcount(arr[i]) % 2]++;
    }
    arr.clear();
    for (int i: s) {
        arr.push_back(i);
    }
    n = arr.size();
    if (cnt[0] && cnt[1]) {
        cout << -1;
        return 0;
    }
    for (int i = 0; i < (1 << 30); i += 2) {
        bool fine = true;
        int x = __builtin_popcount(arr[0] ^ i);
        for (int j = 0; j < n; j++) {
            if (__builtin_popcount(arr[j] ^ i) != x) {
                fine = false; 
                break;
            }
        }
        if (fine) {
            cout << i;
            exit(0);
        }
    }
    cout << -1 << '\n';
}
