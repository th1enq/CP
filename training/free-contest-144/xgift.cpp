#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "../headers/debug.h"
#else
#define debug(...) 42
#endif

int A, B, C;
int dp[31][2];

int cal(int i, int rem) {
    if(i == 30) return (rem == 0);
    if(dp[i][rem] != -1) return dp[i][rem];
    dp[i][rem] = 0;
    for(int c = 0; c <= 1; c++) {
        int a = (A >> i) & 1;
        int b = (B >> i) & 1;
        int x  = (C >> i) & 1;

        int val = ((a ^ c) + (b ^ c) + rem) % 2;

        if(val != (x ^ c)) continue;
        int new_rem = ((a ^ c) + (b ^ c) + rem) / 2;
        dp[i][rem] |= cal(i + 1, new_rem);
    }
    return dp[i][rem];
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int ntest; cin >> ntest;
    while(ntest--) {
        cin >> A >> B >> C;
        memset(dp, -1, sizeof dp);
        cout << (cal(0, 0) ? "YES" : "NO") << '\n';
    }

    return 0;
}