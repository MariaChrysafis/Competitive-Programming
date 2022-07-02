#include <bits/stdc++.h>
 
using namespace std;
struct BIT{
    vector<int> bit; //1-indexed
    int pref(int ind){
        int ans = 0;
        ind++;
        while(ind > 0){
            //cout << ind << " ";
            ans += bit[ind];
            ind -= (ind & (-ind));
        }
        return ans;
    }
    int sum(int l, int r){
        if(l == 0){
            return pref(r);
        }
        return pref(r) - pref(l - 1);
    }
    void update(int ind, int val){
        ind++;
        while(ind < bit.size()){
            bit[ind] += val;
            ind += ind & (-ind);
        }
    }
    void construct (int sz) {
        bit.resize(sz + 1);
        for(int i = 0; i <= sz; i++){
            bit[i] = 0;
        }
    }
};
int main() {
    int n;
    cin >> n;
    vector<int> nxt(n), v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    map<int,int> oc;
    for (int i = n - 1; i >= 0; i--) {
        if (!oc.count(v[i])) {
            nxt[i] = -1;
        } else {
            nxt[i] = oc[v[i]];
        }
        oc[v[i]] = i;
    }
    vector<int> need[n];
    for (int i = 0; i < oc.size(); i++) {
        need[0].push_back(i);
    }
    BIT st;
    st.construct(n);
    oc.clear();
    for (int i = 0; i < n; i++) {
        if (!oc.count(v[i])) {
            st.update(i, 1);
        }
        oc[v[i]]++;
    }
    int sz[n + 1];
    for (int i = 1; i <= n; i++) {
        sz[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        if (i != 0) {
            st.update(i - 1, 0);
        }
        if (i != 0 && nxt[i - 1] != -1) {
            st.update(nxt[i - 1], 1);
        }
        for (int j = 0; j < need[i].size(); j++) {
            int l = i;
            int r = n - 1;
            while (l != r) {
                int m = (l + r + 1)/2;
                if (st.sum(i, m) <= need[i][j]) {
                    l = m;
                } else {
                    r = m - 1;
                }
            }
            if (l + 1 != n) {
                need[l + 1].push_back(need[i][j]);
            }
            sz[need[i][j]]++;
        }
    
    }
    for (int i = 1; i <= n; i++) {
        cout << max(sz[i], 1) << ' ';
    }
}
