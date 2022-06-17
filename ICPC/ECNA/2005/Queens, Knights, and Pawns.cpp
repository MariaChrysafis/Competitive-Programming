#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int c = 0;
    while (true) {
        c++;
    int n, m;
    cin >> n >> m;
    if (n == 0) break;
    set<pair<int,int> > valid;
    map<pair<int,int>,int> myMap;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            valid.insert(make_pair(i, j));
        }
    }
    //queens(1)
    int k;
    cin >> k;
    while (k--) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        myMap[make_pair(x, y)] = 1;
        valid.erase(make_pair(x, y));
    }
    //knights(2)
    cin >> k;
    while (k--) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        myMap[make_pair(x, y)] = 2;
        valid.erase(make_pair(x, y));
    }
    //pawns(3)
    cin >> k;
    while (k--) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        myMap[make_pair(x, y)] = 3;
        valid.erase(make_pair(x, y));
    }
    for (auto& p: myMap) {
        if (p.second == 1) {
            //queen
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if (dx == 0 && dy == 0) continue;
                    int x = p.first.first, y = p.first.second;
                    while (x + dx >= 0 && y + dy >= 0 && x + dx < n && y + dy < m) {
                        x += dx, y += dy;
                        if (myMap.count(make_pair(x, y))) {
                            break;
                        }
                        valid.erase(make_pair(x, y));
                    }
                }
            }
        } else if (p.second == 2) {
            for (int dx = -2; dx <= 2; dx++) {
                for (int dy = -2; dy <= 2; dy++) {
                    if (dx == 0 || dy == 0) continue;
                    if (abs(dx) + abs(dy) != 3) continue;
                    int x = p.first.first, y = p.first.second;
                    if (x + dx >= 0 && y + dy >= 0 && x + dx < n && y + dy < m) {
                        valid.erase(make_pair(x + dx, y + dy));
                    }
                }
            }
        }
    }
    cout << "Board " << c << " has " << valid.size() << " safe squares." << '\n';
    }

}
