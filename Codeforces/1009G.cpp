#include <bits/stdc++.h>

using namespace std;
int main() {
    string s;
    cin >> s;
    int oc[6];
    for (int i = 0; i < 6; i++) {
        oc[i] = 0;
    }
    for (char c: s) {
        oc[c - 'a']++;
    }
    int q;
    cin >> q;
    vector<int> vec;
    vec.assign(s.length(), (1 << 7) - 1);
    while (q--) {
        int pos; string str;
        cin >> pos >> str;
        int mask = 0;
        for (char c: str) {
            mask += (1 << (c - 'a'));
        }
        vec[--pos] = mask;
    }
    int cnt[(1 << 7)];
    for (int i = 0; i < (1 << 7); i++) {
        cnt[i] = 0;
    }
    vector<vector<int> > supermasks(vec.size());
    for (int i = 0; i < vec.size(); i++) {
        for (int j = 0; j < (1 << 7); j++) {
            if ((j & vec[i])) {
                supermasks[i].push_back(j);
                cnt[j]++;
            }
        }
    }
    string str;
    //cout << oc[0] << " " << oc[1] << '\n';
    for (int i = 0; i < vec.size(); i++) {
        bool okay = false;
        for (int j = 0; j < 6; j++) {
            if (!oc[j]) {
                continue;
            }
            if (vec[i] & (1 << j)) {
                oc[j]--;
                    for (int x: supermasks[i]) {
                        cnt[x]--;
                    }
                bool fine = true;
                for (int k = 0; k < (1 << 7); k++) {
                    int tot = 0;
                    for (int t = 0; t < 6; t++) {
                        if (k & (1 << t)) {
                            tot += oc[t];
                        }
                    }
                    if (cnt[k] < tot) {
                        fine = false;
                        break;
                    }
                }
                if (fine) {
                    char c = 'a';
                    c += j;
                    str += c;
                    okay = true;
                    break;
                }
                oc[j]++;
                    for (int x: supermasks[i]) {
                        cnt[x]++;
                    }
            }
        }
    }
    if (str.length() != vec.size()) {
        cout << "Impossible\n";
    } else {
        cout << str;
    }
}
