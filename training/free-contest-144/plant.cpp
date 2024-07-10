#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "../headers/debug.h"
#else
#define debug(...) 42
#endif

const int maxn = (int) 1e6 + 3;

int n, cnt;
int tin[maxn], tout[maxn];
vector<int> adj[maxn];
int seg[4 * maxn], lazy[4 * maxn];

void push(int node, int l, int r, int mid) {
    if(lazy[node]) {
        seg[node << 1] = lazy[node] * (mid - l + 1);
        lazy[node << 1] = lazy[node];
        seg[node << 1 | 1] = lazy[node] * (r - mid);
        lazy[node << 1 | 1] = lazy[node];
        lazy[node] = 0;
    }
}

void update(int u, int v, int w, int node = 1, int l = 1, int r = cnt) {
    if(u > r || v < l) return;
    if(u <= l && r <= v) {
        seg[node] = w * (r - l + 1);
        lazy[node] = w;
        return;
    }
    int mid = (l + r) >> 1;
    push(node, l, r, mid);
    update(u, v, w, node << 1, l, mid);
    update(u, v, w, node << 1 | 1, mid + 1, r);
    seg[node] = seg[node << 1] + seg[node << 1 | 1];
}

int get(int u, int v, int node = 1, int l = 1, int r = cnt) {
    if(u > r || v < l) return 0;
    if(u <= l && r <= v) return seg[node];
    int mid = (l + r) >> 1;
    push(node, l, r, mid);
    seg[node] = seg[node << 1] + seg[node << 1 | 1];
    return get(u, v, node << 1, l, mid) + get(u, v, node << 1 | 1, mid + 1, r);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    cin >> n;
    vector<array<int, 2>> qry(n);

    cnt = 0;
    for(int i = 0; i < n; i++) {
        char c; int u;
        cin >> c >> u;

        int type = (c == '+' ? 0 : (c == '-' ? 1 : 2));
        qry[i] = {type, u};

        if(!type) {
            ++cnt;
            qry[i][1] = cnt;
            adj[u].push_back(cnt);
            adj[cnt].push_back(u);
        }
    }

    cnt = 0;
    function<void(int, int)> dfs = [&] (int u, int par) {
        tin[u] = ++cnt;
        for(int v : adj[u]) if(v != par) {
            dfs(v, u);
        }
        tout[u] = cnt;
    };
    dfs(0, -1);
    
    update(tin[0], tin[0], 1);
    for(auto &[type, u] : qry) {
        if(!type) {
            update(tin[u], tin[u], 1);
        }
        else if(type == 1) {
            update(tin[u], tout[u], 0);
        }
        else {
            cout << get(tin[u], tout[u]) << "\n";
        }
    }

    return 0;
}

/*
25
? 0
+ 0
+ 1
+ 1
+ 0
- 3
? 2
+ 1
+ 5
+ 6
+ 1
- 5
+ 0
- 2
+ 1
+ 8
- 10
- 1
+ 9
- 12
- 9
+ 0
? 13
? 13
? 0
*/