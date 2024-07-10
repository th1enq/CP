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
    vector<vector<char>> a(n, vector<char>(m));
    for (int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(a[i][j] == '#') {
                if(i + 1 < n && a[i + 1][j] == '.') a[i + 1][j] = 'a';
                if(j + 1 < m && a[i][j + 1] == '.') a[i][j + 1] = 'a';
                if(i + 1 < n && j + 1 < m && a[i + 1][j + 1] == '.') a[i + 1][j + 1] = 'a';
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cout << (a[i][j] == '.' ? '.' : '#');
        }
        cout << "\n";
    }
    return 0;
}