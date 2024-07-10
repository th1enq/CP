#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "../headers/debug.h"
#else
#define debug(...) 42
#endif

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n, m; cin >> n >> m;

    map<string, vector<pair<string, int>>> adj;

    for(int i = 0; i < m; i++) {
        int w;
        string u, v; cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    auto solve = [&](const string &u, const string &v) -> void {
        map<string, long long> dp;
        dp[u] = 0;
        priority_queue<pair<long long, string>, vector<pair<long long, string>>, greater<pair<long long, string>>> pq;
        pq.push({0, u});
        while(!pq.empty()) {
            auto [d, x] = pq.top();
            pq.pop();
            if(dp[x] != d) continue;
            if(x == v) {
                cout << dp[x] << '\n';
                return;
            }
            for(auto &[y, w] : adj[x]) {
                if(dp.find(y) == dp.end() || dp[y] > dp[x] + w) {
                    dp[y] = dp[x] + w;
                    pq.push({dp[y], y});
                }
            }
        
        }
        cout << "Roger\n";
    };

    int q;
    cin >> q;
    while(q--) {
        string u, v; cin >> u >> v;
        solve(u, v);
    }

    return 0;
}
