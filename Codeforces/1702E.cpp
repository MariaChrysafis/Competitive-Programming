#include <bits/stdc++.h>
 
using namespace std;

vector<pair<int,int> > vec;

vector<int> color;

map<int, vector<int> > myMap;

bool fine;

void dfs (int ind) {
    int t = 2;
    while(t--) {
        for (int x: myMap[vec[ind].first]) {
            if (x != ind) {
                if (color[x] != -1 && color[x] == color[ind]) {
                    //cout << ind << "<->" << x << '\n';
                    fine = false;
                    return;
                } else if (color[x] == -1) {
                    color[x] = !color[ind];
                    dfs (x);
                }
            }
        }
        swap(vec[ind].first, vec[ind].second);
    }
}

void solve () {
    fine = true;
    int n;
    cin >> n;
    vec.resize(n), color.assign(n, -1);
    myMap.clear();
    for (int i = 0; i < n; i++) {
        cin >> vec[i].first >> vec[i].second;
        myMap[vec[i].first].push_back(i);
        myMap[vec[i].second].push_back(i);
    }
    for (auto& p: vec) {
        if (p.first == p.second) {
            fine = false;
        }
    }
    for (int i = 0; i < n; i++) {
        if (color[i] == -1) {
            color[i] = 0;
            dfs(i);
        }
    }
    if (fine) {
        cout << "YES";
    } else {
        cout << "NO";
    }
    cout << '\n';
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
