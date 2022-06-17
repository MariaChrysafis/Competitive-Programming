#include <bits/stdc++.h>

using namespace std;

vector<vector<pair<int,bool> > > adj;
vector<bool> hv;
vector<bool> val;
vector<int> cc;
int c = 0;

void dfs (int x) {
    cc[x] = c;
    hv[x] = true;
    for (auto& p: adj[x]) {
        if (hv[p.first] && val[p.first] != val[x] ^ p.second) {
            cout << "Waterloo\n";
            exit(0);
        }
        val[p.first] = val[x] ^ p.second;
        if (hv[p.first]) continue;
        dfs(p.first);
    }
}

int main() {
    int n, q;
    cin >> n >> q;
    map<string,int> myMap;
    vector<pair<int,int> > queries;
    vector<pair<pair<int,int>, bool> > vec(n);
    for (int i = 0; i < n; i++) {
        string s1, s2, s3;
        cin >> s1 >> s2 >> s3;
        if (!myMap.count(s1)) {
            myMap[s1] = myMap.size();
        }
        if (!myMap.count(s2)) {
            myMap[s2] = myMap.size();
        }
        vec[i].first.first = myMap[s1], vec[i].first.second = myMap[s2], vec[i].second = (s3 == "intersect");
    }
    for (int i = 0; i < q; i++) {
        string s1, s2;
        cin >> s1 >> s2;
        if (!myMap.count(s1)) {
            myMap[s1] = myMap.size();
        }
        if (!myMap.count(s2)) {
            myMap[s2] = myMap.size();
        }
        queries.push_back(make_pair(myMap[s1], myMap[s2]));
    }
    adj.resize(myMap.size()), hv.assign(myMap.size(), false), val.resize(myMap.size()), cc.assign(myMap.size(), 0);
    for (int i = 0; i < vec.size(); i++) {
        adj[vec[i].first.first].push_back(make_pair(vec[i].first.second, vec[i].second));
        adj[vec[i].first.second].push_back(make_pair(vec[i].first.first, vec[i].second));
    }
    for (int i = 0; i < myMap.size(); i++) {
        if (!hv[i]) {
            val[i] = true;
            dfs(i);
            c++;
        }
    }
    for (auto& p: queries) {
        if (cc[p.first] != cc[p.second]) {
            cout << "unknown\n";
            continue;
        }
        if (val[p.first] == val[p.second]) {
            cout << "parallel\n";
        } else {
            cout << "intersect\n";
        }
    }
}
