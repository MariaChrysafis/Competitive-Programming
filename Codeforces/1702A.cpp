#include <bits/stdc++.h>
 
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        cout << setprecision(20) << n - pow(10, (int)log10(n)) << '\n';
    }
}
