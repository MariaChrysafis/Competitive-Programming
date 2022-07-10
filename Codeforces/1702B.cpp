#include <bits/stdc++.h>
 
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        set<char> mySet;
        int cntr = 0;
        for (char c: s) {
            if (!mySet.count(c)) {
                if (mySet.size() == 3) {
                    mySet.clear();
                    cntr++;
                }
            }
            mySet.insert(c);
        }
        cout << cntr + (bool)mySet.size() << '\n';
    }
}
