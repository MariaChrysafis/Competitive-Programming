#include <bits/stdc++.h>
using namespace std;
bool isPalindrome (int64_t i) {
    string s = to_string(i);
    bool fine = true;
    for (int64_t j = 0; j < s.length(); j++) {
        if (j >= 1 && s[j] == s[j - 1]) {
            fine = false;
        }
        if (j >= 2 && s[j] == s[j - 2]) {
            fine = false;
        }
    }
    return fine;
}
int64_t res (int64_t a, int64_t b) {
    int64_t ans = 0;
    for (int64_t i = a; i <= b; i++) {
        ans += isPalindrome(i);
    }
    return ans;
}
int64_t removeAllBut2 (int64_t x) {
    string s = to_string(x);
    for (int64_t i = 2; i < s.length(); i++) {
        s[i] = '0';
    }
    return stoll(s);
}
vector<int64_t> pos;
vector<int64_t> powr;
int64_t query (int64_t a, int64_t b) {
    if (b - a <= 10000) {
        return res(a, b);
    }
    if (a != 0) {
        return query(0, b) - query(0, a - 1);
    }
    string s = to_string(b);
    int64_t tot = 0;
    int64_t c = 0;
    for (int64_t i = 1; i <= 9; i++) {
        for (int64_t j = 0; j <= 9; j++) {
            for (int64_t k = 0; k <= 9; k++) {
                if (i == j || j == k || i == k) {
                    continue;
                }
                tot += (100 * i + 10 * j + k < 100 * (s[0] - '0') + 10 * (s[1] - '0') + (s[2] - '0')) * powr[s.size() - 3];
                if (i == s[0] - '0' && j == s[1] - '0' && k == s[2] - '0') {
                    if (s[1] != '0') {
                        string orig = s;
                        reverse(s.begin(), s.end());
                        s.pop_back();
                        reverse(s.begin(), s.end());
                        tot += query(removeAllBut2(stoll(s)), stoll(s));
                        s = orig;
                    } else {
                        for (int m = 0; m <= 9; m++) {
                            if (k == m || j == m) {
                                continue;
                            }
                            if (m == s[3] - '0') {
                                string orig = s;
                                reverse(s.begin(), s.end());
                                s.pop_back(), s.pop_back();
                                reverse(s.begin(), s.end());
                                tot += query(removeAllBut2(stoll(s)), stoll(s));
                                s = orig;
                            } else if (m < s[3] - '0') {
                                tot += powr[s.size() - 4];
                            }
                        }
                    }
                }
            }
        }
    }
    return tot + pos[s.length() - 1];
}
int main() {
    int64_t a, b;
    cin >> a >> b;
    pos.resize(20);
    pos[1] = 10;
    powr.push_back(1);
    for (int i = 0; i < 19; i++) {
        powr.push_back(powr.back() * 8);
    }
    for (int i = 2; i < 19; i++) {
        pos[i] = pos[i - 1];
        int64_t res = 81;
        pos[i] += res * powr[i - 2];
    }
    cout << query(a, b);
}
