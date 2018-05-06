#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

#define rep(i, x, y) for (int i = (x), _ = (y); i < _; ++i)
#define down(i, x, y) for (int i = (x) - 1, _ = (y); i >= _; --i)
#define mp(x, y) make_pair(x, y)
#define pb(x) push_back(x)
#define bin(x) (1 << (x))
#define fi first
#define se second
//#define LX_JUDGE

template<typename T> inline bool upmax(T &x, T y) { return x < y ? (x = y, 1) : 0; }
template<typename T> inline bool upmin(T &x, T y) { return x > y ? (x = y, 1) : 0; }

const int MAX_N = 4e5 + 10;

class Tree {
public :
	vector<pii> g[MAX_N];

	ll ans[MAX_N];
	ll dis[MAX_N];
	int dep[MAX_N];

	void dfs1(int x, int fa, int mi, ll mv) {
		if (dep[x] < dep[mi]) {
			mi = x;
			mv = dis[x];
		}
		ans[x] = dis[x] - mv;
		for (auto y : g[x]) {
			if (y.fi == fa) continue ;
			dfs1(y.fi, x, mi, mv);
		}
	}
	void dfs2(int x, int fa, int mi, ll mv) {
		if (dep[x] < dep[mi]) {
			mi = x;
			mv = dis[x];
		}
		ans[x] = mv;
		for (auto y : g[x]) {
			if (y.fi == fa) continue ;
			dfs2(y.fi, x, mi, mv);
		}
	}

	void DFS(int x, int fa) {
		for (auto y : g[x]) {
			if (y.fi == fa) continue ;
			dis[y.fi] = dis[x] + y.se;
			dep[y.fi] = dep[x] + 1;
			DFS(y.fi, x);
		}
	}

	inline void addEdge(int x, int y, int w) {
		g[x].pb(mp(y, w));
		g[y].pb(mp(x, w));
	}
	inline void build(int Root) {
		DFS(Root, 0);
	}
	inline ll* query(int x, int tp) {
		if (tp == 0) dfs1(x, 0, x, dis[x]);
		else dfs2(x, 0, x, dis[x]);
		return ans;
	}
} t[2];

int N;

ll merge(ll *a, ll *b) { 
	ll res = 0;
	rep (i, 1, N + 1) upmax(res, a[i] - b[i]);
	return res;
}

int main() {
#ifdef LX_JUDGE
	freopen(".in", "r", stdin);
#endif
	int x, y, v;
	scanf("%d", &N);
	rep (i, 1, N) {
		scanf("%d%d%d", &x, &y, &v);
		t[0].addEdge(x, y, v);
	}
	rep (i, 1, N) {
		scanf("%d%d%d", &x, &y, &v);
		t[1].addEdge(x, y, v);
	}
	t[0].build(1);
	t[1].build(1);
	ll ans = 0;
	rep (i, 1, N + 1) {
		upmax(ans, t[0].dis[i] + merge(t[0].query(i, 0), t[1].query(i, 1)));
	}
	printf("%lld\n", ans);
	return 0;
}
