#include <bits/stdc++.h>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
using namespace std;
vector<int> most_frequent (vector<int>& v) {
    map<int,int> oc;
    for (int i: v) {
        ++oc[i];
    }
    priority_queue<int> pq;
    for (auto& p: oc) {
        pq.push(p.second);
    }
    int c = 0;
    vector<int> val(v.size() + 1);
    val[0] = pq.top();
    while (++c < val.size()) {
        int x = pq.top();
        pq.pop(), pq.push(x - 1), val[c] = pq.top();
    }
    return val;
}
void update (vector<int>& v, int sz) {
    map<int,int> oc;
    for (int i: v) {
        oc[i]++;
    }
    priority_queue<pair<int,int> > pq;
    for (auto& p: oc) {
        pq.push(make_pair(p.second, p.first));
    }
    int op = 0;
    while (op++ != v.size() - sz) {
        pair<int,int> p = pq.top();
        pq.pop(), pq.push(make_pair(p.first - 1, p.second)), oc[p.second]--;
    }
    v.clear();
    vector<pair<int,int> > vec;
    for (auto& p: oc) {
        vec.push_back(make_pair(p.second, p.first));
    }
    sort(vec.begin(), vec.end());
    reverse(vec.begin(), vec.end());
    v.clear();
    for (auto& p: vec) {
        while (p.first--) {
            v.push_back(p.second);
        }
    }
}
vector<vector<int> > generate (vector<int>& v, pair<int,int> p) {
    vector<vector<int> > arr(p.first, vector<int>(p.second));
    int x = 0;
    for (int i = 0; i < p.first; i++) {
        pair<int,int> cur = make_pair(i, 0);
        int cntr = p.second;
        while (cntr--) {
            arr[cur.first][cur.second] = v[x++];
            cur.first++, cur.first %= p.first;
            cur.second++, cur.second %= p.second;
        }
    }
    return arr;
}
bool valid (vector<vector<int> > arr) {
    map<int,set<int> > x, y;
    for (int i = 0; i < arr.size(); i++) {
        for (int j = 0; j < arr[0].size(); j++) {
            if (x[arr[i][j]].count(j)) {
                return false;
            }
            if (y[arr[i][j]].count(i)) {
                return false;
            }
            x[arr[i][j]].insert(j), y[arr[i][j]].insert(i);
        }
    }
    return true;
}
void print (vector<vector<int> > &v) {
    for (int i = 0; i < v.size(); i++) {
        for (int j: v[i]) {
            cout << j << ' ';
        }
        cout << '\n';
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    vector<int> vec = most_frequent(v);
    pair<int,int> p;
    p = make_pair(0,  0);
    for (int i = 1; i <= (n + 1)/2; i++) {
        int l = 0;
        int r = n/i;
        while (l != r) {
            int m = (l + r + 1)/2;
            if (vec[n - m * i] <= min(m, i)) {
                l = m;
            } else {
                r = m - 1;
            }
        }
        if (l == 0) {
            continue;
        }
        if (p.first * p.second < i * l) {
            p = make_pair(i, l);
        }
    }
    cout << p.first * p.second << '\n';
    swap(p.first, p.second);
    update(v, p.first * p.second);
    n = v.size();
    vector<vector<int> > arr = generate(v, p);
    if (valid(arr)) {
        cout << p.first << " " << p.second << '\n';
        print(arr);
        exit(0);
    }
    swap(p.first, p.second);
    cout << p.first << " " << p.second << '\n';
    arr = generate(v, p);
    print(arr);
    exit(0);
    for (int i: v) {
        cout << i << ' ';
    }
    cout << '\n';
    exit(0);
}
