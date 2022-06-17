#include <bits/stdc++.h>
#define ll int64_t
#define pll pair<ll,ll>
using namespace std;
class DisjointSetUnion {
protected:
    vector<int> parent;
    vector<int> compSize;
    const int n;
public:
    DisjointSetUnion(int sz) : n(sz) {
        parent.resize(sz), compSize.resize(sz);
        for (int i = 0; i < n; i++) {
            parent[i] = i, compSize[i] = 1;
        }
    }

    int find_head(int x) const {
        int cur = x;
        while (cur != parent[cur]) {
            cur = parent[cur];
        }
        return cur;
    }

    void join(int x, int y) {
        x = find_head(x), y = find_head(y);
        if (x == y) {
            return;
        }
        if (compSize[x] > compSize[y]) {
            swap(x, y);
        }
        parent[x] = y;
        compSize[y] += compSize[x];
    }

    stack<pair<pair<int,int>,pair<int,int> > > myStack;

    void join1 (int x, int y) {
        x = find_head(x), y = find_head(y);
        if (x == y) {
            return;
        }
        if (compSize[x] > compSize[y]) {
            swap(x, y);
        }
        myStack.push(make_pair(make_pair(x, parent[x]), make_pair(y, compSize[y])));
        parent[x] = y;
        compSize[y] += compSize[x];
    }

    void revert () {
        while (!myStack.empty()) {
            parent[myStack.top().first.first] = myStack.top().first.second;
            compSize[myStack.top().second.first] = myStack.top().second.second;
            myStack.pop();
        }
    }

    bool comp(int x, int y) {
        return (find_head(x) == find_head(y));
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    swap(n, m);
    DisjointSetUnion dsu(n * m);
    int arr[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> arr[i][j];
        }
    }
    map<pair<int,int>,vector<pair<pair<int,int>,pair<int,int> > > > myMap;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if (i + dx < 0 || i + dx == n || j + dy < 0 || j + dy == m) continue;
                    if (abs(dx) + abs(dy) != 1) continue;
                    //if (arr[i + dx][j + dy] == arr[i][j]) {
                        //dsu.join((i + dx) * m + j + dy, i * m + j);
                    //} else {
                        myMap[make_pair(arr[i][j], arr[i + dx][j + dy])].push_back(make_pair(make_pair(i, j), make_pair(i + dx, j + dy)));
                    //}
                }
            }
        }
    }
    for (int a = 0; a <= 9; a++) {
        for (int b = 0; b <= 9; b++) {
            for (int c = 0; c <= 9; c++) {
                for (auto& p: myMap[make_pair(a, b)]) {
                    dsu.join1(m * p.first.first + p.first.second, m * p.second.first + p.second.second);
                }
                for (auto& p: myMap[make_pair(a, c)]) {
                    dsu.join1(m * p.first.first + p.first.second, m * p.second.first + p.second.second);
                }
                for (auto& p: myMap[make_pair(b, c)]) {
                    dsu.join1(m * p.first.first + p.first.second, m * p.second.first + p.second.second);
                }
                for (auto& p: myMap[make_pair(a, a)]) {
                    dsu.join1(m * p.first.first + p.first.second, m * p.second.first + p.second.second);
                }
                for (auto& p: myMap[make_pair(b, b)]) {
                    dsu.join1(m * p.first.first + p.first.second, m * p.second.first + p.second.second);
                }
                for (auto& p: myMap[make_pair(c, c)]) {
                    dsu.join1(m * p.first.first + p.first.second, m * p.second.first + p.second.second);
                }
                for (int i = 0; i < m; i++) {
                    for (int j = 0; j < m; j++) {
                        //(0, i) and (n - 1, j)
                        if (dsu.find_head(i) == dsu.find_head((n - 1) * m + j)) {
                            cout << a << " " << b << " " << c;
                            exit(0);
                        }
                    }
                }
                dsu.revert();
            }
        }
    }
    cout << "-1 -1 -1";
}
