#include <bits/stdc++.h>
using namespace std;

const int maxn = (int) 2e5 + 3;

struct query_{
	int l, r;
} qry[maxn];

int n, q;
int res[maxn], l[maxn], r[maxn];
vector<int> inBlock[maxn], pos[maxn];
vector<int> rollBack;

struct FenwickTree{
	int bit[maxn];

	void Clear(){
		memset(bit, 0, sizeof bit);
	}

	void Update(int x, int w){
		while(x <= n){
			bit[x] += w;
			x += (x & -x);
		}
	}

	int Get(int x){
		int ans = 0;
		while(x){
			ans += bit[x];
			x -= (x & -x);
		}
		return ans;
	}
} BIT;

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> q;
    for(int i = 1; i <= n; i++){
    	int x; cin >> x;
    	pos[x].push_back(i);
    }
    for(int i = 1; i <= q; i++){
    	int l, r; cin >> l >> r;
    	qry[i] = {l, r};
    }
    for(int i = 1; i <= q; i++){
    	l[i] = 1; r[i] = n;
    }
    for(int run = 1; run <= 20; run++){
    	for(int i = 1; i <= q; i++) inBlock[(l[i] + r[i]) >> 1].push_back(i);
    	for(int val = n; val >= 1; val--){
    		for(int x : pos[val]){
    			BIT.Update(x, 1);
    			rollBack.push_back(x);
    		}
    		for(int &x : inBlock[val]){
    			int num = BIT.Get(qry[x].r) - BIT.Get(qry[x].l - 1);
    			if(num >= val) res[x] = val, l[x] = val + 1;
    			else r[x] = val - 1;
    		}
    		inBlock[val].clear();
    	}
    	for(int x : rollBack) BIT.Update(x, -1);
    	rollBack.clear();
    }
    for(int i = 1; i <= q; i++) cout << res[i] << "\n";
    return 0;
}
