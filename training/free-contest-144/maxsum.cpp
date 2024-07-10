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

    vector<int> a(n + 1);

    for(int i = 1; i < n; i++) cin >> a[i];

    a[0] = a[n] = (int) 1e5 + 1;

    long long res = 0;

    for(int i = 1; i <= n; i++) {
        res += (long long) min(a[i], a[i - 1]);
    }

    cout << res;

    return 0;
}