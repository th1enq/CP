#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "../headers/debug.h"
#else
#define debug(...) 42
#endif

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    map<string, int> cnt;

    int n, k; cin >> n >> k;
    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        sort(s.begin(), s.end());
        cnt[s]++;
    }

    vector<int> val;
    for(auto &[key, value] : cnt) {
        val.push_back(value);
    }

    debug(val);

    int m = (int) cnt.size();
    vector<vector<long long>> dp(m + 1, vector<long long>(k + 1, 0));

    const int mod = (int) 1e9 + 7;

    vector<long long> POW(n + 1, 0), inv(n + 1, 0);
    POW[0] = 1;
    for(int i = 1; i <= n; i++) {
        POW[i] = (POW[i - 1] * i) % mod;
    }

    auto getPow = [&](long long a, long long b) -> long long {
        long long res = 1;
        while(b) {
            if(b & 1) res = (res * a) % mod;
            a = (a * a) % mod;
            b >>= 1;
        }
        return res;
    };

    auto CKN = [&](int k, int n) -> long long {
        if(k > n) return 0LL;
        return (POW[n] * inv[k] % mod) * inv[n - k] % mod;
    };

    inv[n] = getPow(POW[n], mod - 2);
    for(int i = n - 1; i >= 0; i--) {
        inv[i] = (inv[i + 1] * (i + 1)) % mod;
    }

    dp[0][0] = 1;
    for(int i = 1; i <= m; i++) {
        for(int j = 0; j <= k; j++) {
            for(int c = 0; c <= val[i - 1]; c++) {
                int p = CKN(2, c);
                if(j - p >= 0) {
                    dp[i][j] = (dp[i][j] + (dp[i - 1][j - p] * CKN(c, val[i - 1]) % mod)) % mod;
                }
            }
        }
    }
    cout << dp[m][k];

    return 0;
}