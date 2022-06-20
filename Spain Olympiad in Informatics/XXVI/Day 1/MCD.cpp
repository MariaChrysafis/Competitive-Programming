#include <bits/stdc++.h>
using namespace std;
int64_t x = 99954301827492463;
int64_t y = 780143264487015779;
int64_t gcd (int64_t a, int64_t b) {
    if (!a || !b) return max(a,b) ;
    return gcd(max(a,b) % min(a, b), min(a, b));
}
int64_t query (int64_t a, int64_t b) {
    cout << "? " << a << " " << b << '\n';
    cout.flush();
    int64_t res; cin >> res; return res;
    if (res == 0) {
        exit(0);
    }
    
    return gcd(abs(x - a), abs(y - b));
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<int64_t> powr;
    powr.push_back(1);
    while (powr.size() != 64) {
        powr.push_back(powr.back() * 2);
    }
    int64_t dx = 0, dy = 0;
    for (int i = 0; i <= 59; i++) {
        //find it modulo 2^i
        bool br = false;
        for (int qry1 = 0; qry1 <= 1; qry1++) {
            for (int qry2 = 0; qry2 <= 1; qry2++) {
                if (query(-dx - qry1 * powr[i], -dy - qry2 * powr[i]) % (2 * powr[i]) == 0) {
                    dx += qry1 * powr[i];
                    dy += qry2 * powr[i];
                    br = true;
                    break;
                }
            }
            if (br) {
                break;
            }
        }
    }
    //cout << powr[61] - dx << '\n';
    query(powr[60] - dx, powr[60] - dy);
}
