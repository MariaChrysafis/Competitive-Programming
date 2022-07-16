#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <vector>
#include <map>
using namespace std;
int main() {
    int W, H;
    cin >> W >> H;
    int dp[W + 1][H + 1];
    for (int i = 0; i <= W; i++) {
        for (int j = 0; j <= H; j++) {
            dp[i][j] = i * j; //amount of space wasted
        }
    }
    int N;
    cin >> N;
    for (int i = 0; i < N; i++) {
        int w, h;
        cin >> w >> h;
        dp[w][h] = 0;
    }
    for (int i = 0; i <= W; i++) {
        for (int j = 0; j <= H; j++) {
            for (int k = 0; k < j; k++) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[i][j - k]);
            }
            for (int k = 0; k < i; k++) {
                dp[i][j] = min(dp[i][j], dp[k][j] + dp[i - k][j]);
            }
        }
    }
    cout << dp[W][H] << endl;
}
