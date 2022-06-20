#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#define ll long long
using namespace std;
struct solver{
    vector<vector<pair<ll,ll>>> adj;
    vector<vector<pair<ll,ll>>> inp;
    vector<ll> color;
    void dfs(ll cur, int curColor){
        color[cur] = curColor;
        for(auto p: adj[cur]){
            if(color[p.second] == 2){
                dfs(p.second, !curColor);
            }
        }
    }
    bool valid(ll x){
        vector<vector<pair<ll,ll>>> new_adj(adj.size());
        for(int i = 0; i < inp.size(); i++){
            for(auto p: inp[i]){
                if(p.first < x) {
                    new_adj[i].push_back(p);
                }
            }
        }
        adj = new_adj;
        color.resize(adj.size());
        for(int i = 0; i < adj.size(); i++){
            color[i] = 2;
        }
        for(int i = 0; i < adj.size(); i++){
            if(color[i] == 2){
                dfs(i, 0);
            }
        }
        for(int i = 0; i < adj.size(); i++){
            for(auto p: adj[i]){
                if(color[p.second] == color[i]){
                    return false;
                }
            }
        }
        return true;
    }
    ll binSearch(ll l, ll r){
        while(l < r){
            ll m = (l + r + 1)/2;
            if(valid(m)){
                l = m;
            }else{
                r = m - 1;
            }
        }
        if(l > r){
            return 0;
        }
        return l;
    }
    void read(){
        ll n, m;
        cin >> n >> m;
        adj.resize(n);
        map<pair<ll,ll>,ll> myMap;
        for(int i = 0; i < m; i++){
            ll u, v, w;
            cin >> u >> v >> w;
            adj[u].push_back({w, v});
            adj[v].push_back({w, u});
            myMap[{u, v}] = myMap[{v, u}] = w;
        }
        inp = adj;
        ll myMax = 3e9;
        for(int i = 0; i < n; i++){
            sort(adj[i].begin(), adj[i].end());
            if(adj[i].size() >= 2){
                myMax = min(myMax, adj[i][0].first + adj[i][1].first);
            }
        }
        ll ans = binSearch(0, myMax);
        if(ans == 3e9) cout << "INF\n";
        else cout << ans << endl;
    }
};
int main(){
    int t;
    cin >> t;
    while(t--){
        solver s;
        s.read();
    }
}
