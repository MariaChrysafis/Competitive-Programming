#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;
struct Graph{
	vector<vector<pair<int,int> > > adj; //{-weight, node}
	vector<int> dijk(int src){
		vector<int> dist;
		vector<bool> mark;
		dist.resize(adj.size()), mark.resize(adj.size());
		for(int i = 0; i < adj.size(); i++){
			dist[i] = INF;
			mark[i] = false;
		}
		dist[src] = 0;
		priority_queue<pair<int,int> > pq;
		pq.push(make_pair(0,src));
		while(!pq.empty()){
			int u = pq.top().second; //node
			pq.pop();
			if(mark[u]){
				continue;
			}
			mark[u] = true;
			for(auto p: adj[u]){
				int v = p.second;
				int w = p.first;
				if(dist[v] > dist[u] + w){
					dist[v] = dist[u] + w;
					pq.push(make_pair(-dist[v], v));
				}
			}
		}
		return dist;
	}
};
class Solver {
public:
    vector<vector<int> > forward_blue, backward_blue;
    int start, end;
    vector<int64_t> res; //from start to x
    vector<int64_t> ans; //from x to end
    int64_t dfs (int curNode) {
        if (res[curNode] != -1) {
            return res[curNode];
        }
        if (curNode == start) {
            return (res[curNode] = 1);
        }
        res[curNode] = 0;
        for (int i: backward_blue[curNode]) {
            res[curNode] += dfs(i);
            res[curNode] %= ((int)1e9 + 7);
        }
        return res[curNode];
    }
    int64_t dfs1 (int curNode) {
        if (ans[curNode] != -1) {
            return ans[curNode];
        }
        if (curNode == end) {
            return (ans[curNode] = 1);
        }
        ans[curNode] = 0;
        for (int i: forward_blue[curNode]) {
            ans[curNode] += dfs1(i);
            ans[curNode] %= ((int)1e9 + 7);
        }
        return ans[curNode];
    }
    void add_edge (int u, int v) {
        swap(u, v);
        forward_blue[u].push_back(v), backward_blue[v].push_back(u);
    }
    Solver (int n) {
        res.assign(n, -1), ans.assign(n, -1), forward_blue.resize(n), backward_blue.resize(n);
    }
    vector<pair<int,int > > red;
    void add_red (int u, int v) {
        red.push_back(make_pair(u, v));
        red.push_back(make_pair(v, u));
    }
    void read () {
        for (int i = 0; i < res.size(); i++) {
            dfs(i);
            dfs1(i);
        }
        int64_t extra = 0;
        for (auto& p: red) {
            extra += (res[p.first] * ans[p.second]) % ((int)1e9 + 7);
            extra %= ((int)1e9 + 7);
        }
        cout << (res[end] + extra) % ((int)1e9 + 7) << '\n';
    }
};
void solve () {
    Graph gr;
    int n, m;
    cin >> n >> m;
    int s, t;
    cin >> s >> t;
    s--, t--;
    gr.adj.resize(n);
    vector<pair<int,int> > edges;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        edges.push_back(make_pair(u, v));
        gr.adj[u].push_back(make_pair(1, v));
        gr.adj[v].push_back(make_pair(1, u));
    }
    vector<int> distances = gr.dijk(s);
    Solver slvr(n);
    slvr.start = s, slvr.end = t;
    for (auto& p: edges) {
        if (distances[p.first] == distances[p.second]) {
            //red.push_back(p);
            slvr.add_red(p.first, p.second);
        } else {
            if (distances[p.first] == distances[p.second] + 1) {
                slvr.add_edge(p.first, p.second);
            } else if (distances[p.first] == distances[p.second] - 1){
                slvr.add_edge(p.second, p.first);
            }
        }
    }
    slvr.read();
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int tc;
    cin >> tc;
    while (tc--) {
        solve();
    }
}
