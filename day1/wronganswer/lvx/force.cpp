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

	int dfn[MAX_N], d_clock;
	int table[23][MAX_N * 2], seq[MAX_N * 2];

	void DFS(int x, int fa) {
		dfn[x] = d_clock;
		seq[d_clock++] = x;
		for (auto y : g[x]) {
			if (y.fi == fa) continue ;
			dis[y.fi] = dis[x] + y.se;
			dep[y.fi] = dep[x] + 1;
			DFS(y.fi, x);
			seq[d_clock++] = x;
		}
	}

	inline void addEdge(int x, int y, int w) {
		g[x].pb(mp(y, w));
		g[y].pb(mp(x, w));
	}

#define cmp(x, y) (dep[(x)] < dep[(y)] ? (x) : (y))
	inline void build(int Root) {
		DFS(Root, 0);
		rep (i, 0, d_clock) table[0][i] = seq[i];
		rep (i, 0, 31 - __builtin_clz(d_clock)) {
			rep (j, 0, d_clock - bin(i + 1) + 1) {
				table[i + 1][j] = cmp(table[i][j], table[i][j + bin(i)]);
			}
		}
	}
	inline ll qry(int x, int y) {
		int l = dfn[x], r = dfn[y], v;
		if (l > r) swap(l, r);
		v = 31 - __builtin_clz(r - l + 1);
		return dis[cmp(table[v][l], table[v][r - bin(v) + 1])];
	}
#undef cmp
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
	rep (i, 1, N + 1) rep (j, 1, i) {
		upmax(ans, t[0].dis[i] + t[0].dis[j] - t[0].qry(i, j) - t[1].qry(i, j));
	}
	printf("%lld\n", ans);
	return 0;
}
