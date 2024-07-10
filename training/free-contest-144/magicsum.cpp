#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "../headers/debug.h"
#else
#define debug(...) 42
#endif

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n; cin >> n;

    long long ans = 0;

    while(n--) {
        int l, r; cin >> l >> r;

        auto f = [](int x) {
            long long res = (long long) x * (x + 1) / 2;
            return res;
        };


        ans += f(r) - f(l - 1);
    }
    cout << ans;

    return 0;
}