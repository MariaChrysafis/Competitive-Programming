#include <bits/stdc++.h>
#define ll int64_t
#define pll pair<ll,ll>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<int> vec;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        double d;
        cin >> d;
        vec.push_back((int)(100 * d));
    }
    sort(vec.begin(), vec.end());
    int myMin = 0.0;
    for (int i = 0; i < vec.size(); i++) {
        int d = vec[(i + 1) % n] - vec[i];
        int dist;
        if (i + 1 != n) dist = abs(d);
        else dist = 36000 - abs(d);
        myMin = max(myMin, dist);
    }
    if (n == 1) {
        cout << 0;
        return 0;
    }
    double d = myMin;
    d /= 100;
    cout << ceil((360.0 - d) * 12);
}
