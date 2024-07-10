#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "../headers/debug.h"
#else
#define debug(...) 42
#endif

int dp[151][151][3751];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n, k;
    cin >> n >> k;

    memset(dp, -0x3f, sizeof dp);
    dp[0][0][0] = 0;

    for(int i = 1; i <= n; i++) {
        long long x; cin >> x;

        auto get = [&](long long x, int p) {
            int res = 0;
            while(x % p == 0) {
                ++res;
                x /= p;
            }
            return res;
        };

        int m2 = get(x, 2);
        int m5 = get(x, 5);

        for(int j = 0; j <= k; j++) {
            for(int m = 0; m <= 3750; m++) {
                dp[i][j][m] = dp[i - 1][j][m];
                if(j >= 1 && m >= m5) {
                    dp[i][j][m] = max(dp[i][j][m], dp[i - 1][j - 1][m - m5] + m2);
                }
            }
        }
    }

    int res = 0;

    for(int m = 0; m <= 3750; m++) {
        res = max(res, min(m, dp[n][k][m]));
    }

    cout << res;
    return 0;
}