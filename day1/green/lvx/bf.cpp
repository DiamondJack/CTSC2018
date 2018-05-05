#include <bits/stdc++.h>
#define constexpr inline

using namespace std;
typedef long long ll;
typedef pii pair<int, int>;

#define rep(i, x, y) for (int i = (x), _ = (y); i < _; ++i)
#define down(i, x, y) for (int i = (x) - 1, _ = (y); i >= _; --i)
#define mp(x, y) make_pair(x, y)
#define pb(x) push_back(x)
#define bin(x) (1 << (x))
#define fi first
#define se second
//#define LX_JUDGE

const int MAX_N = 2005;

namespace MATH_CAL {
	const int mod = 998244353;
	constexpr int add(int a, int b) { return a + b >= mod ? a + b - mod : a + b; }
	constexpr int sub(int a, int b) { return a - b < 0 ? a - b + mod : a - b; }
	constexpr int mul(int a, int b) { return (ll) a * b % mod; }
	inline int qpow(int x, int n) { int r = 1; for ( ; n; n /= 2, x = mul(x, x)) if (n & 1) r = mul(r, x); return r; }
	inline int mod_inv(int x) { return qpow(x, mod - 2); }
} using namespace MATH_CAL;

int fac[MAX_N], inv[MAX_N];
int f[MAX_N];
int g[MAX_N][MAX_N];
int len[MAX_N], siz[MAX_N], cov[MAX_N], to[MAX_N];

void Solve(int n) {
	memset(siz + 1, 0, n << 2);
	memset(cov + 1, 0, n << 2);
	rep (i, 1, n + 1) scanf("%d", &len[i]), to[i] = i - len[i] + 1;
	bool flag = 1;
	rep (i, 1, n + 1) flag &= (to[i] >= 1);
	rep (i, 1, n + 1) {
		siz[i] = 1;
		rep (j, to[i], i + 1) {
			flag &= to[i] <= to[j];
			if (!cov[j] && j < i) cov[j] = i, siz[i]++;
		}
	}
	rep (i, 1, n + 1) flag &= cov[i];
	if (!flag) return void(puts("0"));
	int res = 1;
	rep (i, 1, n + 1) res = mul(res, f[siz[i]]);
	printf("%d\n", res);
}

int main() {
#ifdef LX_JUDGE
	freopen(".in", "r", stdin);
#endif
	int T, n = MAX_N;
	{ // pre
		fac[0] = 1;
		rep (i, 1, n) fac[i] = mul(fac[i - 1], i);
		inv[1] = 1;
		rep (i, 2, n) inv[i] = mul(mod - mod / i, inv[mod % i]);
		g[0][0] = 1;
		rep (i, 1, n) rep (j, 1, i + 1) {
			g[i][j] = add(mul(g[i - 1][j], mul(i + j - 1, inv[j])), g[i - 1][j - 1]);
		}
		f[1] = 1;
		rep (i, 2, n) {
			f[i] = fac[i];
			rep (j, 2, i) {
				f[i] = sub(f[i], mul(f[j], g[i - 1][j - 1]));
			}
		}
	}
	scanf("%d%d", &T, &n);
	while (T--) Solve(n);
	return 0;
}
