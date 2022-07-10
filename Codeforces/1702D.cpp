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
        int p;
        cin >> p;
        int cntr = 0;
        map<char,int> rem;
        for (char c: s) {
            cntr += c - 'a' + 1;
            rem[c]++;
        }
        string dum = s;
        sort(dum.begin(), dum.end());
        while (cntr > p) {
            rem[dum.back()]--;
            cntr -= (dum.back() - 'a' + 1);
            dum.pop_back();
        }
        for (char c: s) {
            if (rem[c] == 0) {
                continue;
            }
            rem[c]--;
            cout << c;
        }
        cout << '\n';
    }
}
