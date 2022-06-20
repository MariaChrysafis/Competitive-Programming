#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#define ll long long
using namespace std;
struct Tree{
    vector<vector<int>> adj;
    vector<int> dp;
    int dfs(int cur, int prev){
        vector<int> children;
        for(int i: adj[cur]){
            if(i != prev){
                children.push_back(i);
            }
        }
        if(children.size() == 2){
            dp[cur] = 2 * min(dfs(children[0], cur), dfs(children[1], cur)) + 1;
        }
        if(children.size() == 1){
            dp[cur] = dfs(children[0], cur) + 1;
        }
        if(children.size() == 0){
            dp[cur] = 1;
        }
        return dp[cur];
    }
    void read(){
        int n;
        cin >> n;
        adj.resize(n);
        dp.resize(n);
        for(int i = 0; i < n - 1; i++){
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        cout << dfs(0, -1) << endl;
    }
};
int main(){
    int t;
    cin >> t;
    while(t--){
        Tree tree;
        tree.read();
    }
}
