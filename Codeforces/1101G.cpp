#include <bits/stdc++.h>
using namespace std;
class Space {
public:
    vector<int> tot;
    bool fine (int x) {
        for (int i: tot) {
            x = min(x, x ^ i);
        }
        return (x != 0);
    }
    void add (int x) {
        for (int i: tot) {
            x = min(x, x ^ i);
        }
        if (x != 0) {
            tot.push_back(x);
        }
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    int arr[n];
    int bxor = 0;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        bxor ^= arr[i];
    }
    if (bxor == 0) {
        cout << -1 << '\n';
        exit(0);
    }
    Space space;
    bxor = 0;
    int c = 0;
    for (int i = 0; i < n; i++) {
        bxor ^= arr[i];
        if (space.fine(bxor)) {
            space.add(bxor);
            bxor = 0;
            c++;
        }
    }
    cout << c;
}
