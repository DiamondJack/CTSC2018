#pragma GCC diagnostic error "-std=c++11"
#pragma GCC optimize("-O2")
#include <bits/stdc++.h>
namespace __banban_hao_ke_ai__ {

	using ll = long long;
	const int MAX_N = 1000010;
	const ll inf = 1ll << 60;

	template<class T> constexpr T dmax(T a, T b) {return a > b ? a : b;}
	template<class T> inline bool cmax(T &a, T b) {return a < b ? a = b, 1 : 0;}
	template<class T> inline bool cmin(T &a, T b) {return a > b ? a = b, 1 : 0;}
	constexpr int diff(int a, int b) {return a > b ? a - b : b - a;}

	struct Adj{int to, val; Adj *nxt;}
		*adj[MAX_N << 1], *adj1[MAX_N], mem[MAX_N * 8], *tot = mem;
	
	inline void link(Adj* adj[], int x, int y, int v) {
///*bgg*/if(adj==__banban_hao_ke_ai__::adj) printf("link %d ~ %d v = %d\n",x,y,v);
		*++tot = {y, v, adj[x]}; adj[x] = tot;
		*++tot = {x, v, adj[y]}; adj[y] = tot;
	}

	int N, N0, fa[MAX_N << 1], cnt[MAX_N << 1], _S, _S1, _E[2], _ED, _EV;
	ll dep[MAX_N << 1];
	bool vis[MAX_N << 1];

	void dfs_build(int p) {
		vis[p] = 1; int p0 = p; 
		for(auto k = adj1[p]; k; k = k->nxt) 
			if(!vis[k->to]) {
				link(adj, p0, ++N0, 0);
				fa[N0] = p0; dep[N0] = dep[p0];
				link(adj, p0 = N0, k->to, k->val);
				fa[k->to] = p0; dep[k->to] = dep[p0] + k->val;
				dfs_build(k->to);
			}
		vis[p] = 0;
	}
	void dfs_cnt(int p) {
		vis[p] = 1; cnt[p] = 1;
		for(auto k = adj[p]; k; k = k->nxt)
			if(!vis[k->to]) {
				dfs_cnt(k->to);
				cnt[p] += cnt[k->to];
			}
		vis[p] = 0;
	}
	void dfs_gra(int p) {
		vis[p] = 1;
		_S1 += (p <= N);
///*bgg*/printf("dfs_gra p = %d cnt = %d\n", p, cnt[p]);
		for(auto k = adj[p]; k; k = k->nxt)
			if(!vis[k->to]) {
				dfs_gra(k->to);
				if(cmin(_ED, diff(_S - cnt[k->to], cnt[k->to])))
					{_E[0] = p; _E[1] = k->to; _EV = k->val;}
			}
		vis[p] = 0;
	}

	struct Node {
		Node *ch[2];
		ll val[2];
		inline void* operator new(std::size_t) {
			static const int B = 2048;
			static Node *mem, *tot;
			if(mem == tot) tot = (mem = new Node[B]) + B;
			return mem++;
		}
	}	*null, *T[MAX_N], **Th[MAX_N];

	void append(int p, bool d, ll val) {
		auto x = new Node(*null);
		x->val[d] = val;
		*Th[p] = x;
		Th[p] = &x->ch[d];
///*bgg*/printf("append p = %d d = %d val = %lld\n",p,d,val);
	}

	void dfs_append_0(int p, ll v, bool f) {
		vis[p] = 1; cnt[p] = 1;
		if(p <= N) append(p, 0, f ? v : (v + dep[p])); 
		for(auto k = adj[p]; k; k = k->nxt)
			if(!vis[k->to]) {
				if(!f && fa[k->to] == p)
					dfs_append_0(k->to, v + dep[p] + k->val, 1);
				else
					dfs_append_0(k->to, v + k->val, f);
				cnt[p] += cnt[k->to];
			}
		vis[p] = 0;
	}
	void dfs_append_1(int p, ll v) {
		vis[p] = 1; cnt[p] = 1;
		if(p <= N) append(p, 1, v);
		for(auto k = adj[p]; k; k = k->nxt)
			if(!vis[k->to]) {
				dfs_append_1(k->to, v + k->val);
				cnt[p] += cnt[k->to];
			}
		vis[p] = 0;
	}


	void divide(int p, int S) {
		cnt[p] = _S = S; 
		_S1 = 0;
		_ED = N0;
		_E[0] = _E[1] = 0;
		dfs_gra(p);
///*bgg*/printf("_S1 = %d\n", _S1);
		if(_S1 <= 1) return;

		if(fa[_E[0]] == _E[1]) std::swap(_E[0], _E[1]);
///*bgg*/assert(_E[0] == fa[_E[1]]); printf("divide S = %d E = %d ~ %d\n", _S, _E[0], _E[1]);

		vis[_E[1]] = 1; dfs_append_0(_E[0], _EV, 0); vis[_E[1]] = 0;
		vis[_E[0]] = 1; dfs_append_1(_E[1], 0); vis[_E[0]] = 0; 
///*bgg*/getchar();

		int E[2] = {_E[0], _E[1]};
		int C[2] = {cnt[E[0]], cnt[E[1]]};
		vis[E[1]] = 1; divide(E[0], C[0]); vis[E[1]] = 0;
		vis[E[0]] = 1; divide(E[1], C[1]); vis[E[0]] = 0;
	}

	ll ans = -inf, mov;

	void merge(Node*& l, Node* r) {
		if(r == null) return;
		if(l == null) return void(l = r);
		cmax(ans, l->val[0] + r->val[1] - mov);
		cmax(ans, l->val[1] + r->val[0] - mov);
///*bgg*/printf("merge check %lld %lld\n",l->val[0]+r->val[1]-mov,l->val[1]+r->val[0]-mov);
		cmax(l->val[0], r->val[0]);
		cmax(l->val[1], r->val[1]);
		merge(l->ch[0], r->ch[0]);
		merge(l->ch[1], r->ch[1]);
	}
	void dfs_calc(int p, ll d) {
		vis[p] = 1;
		cmax(ans, dep[p] - d);
		for(auto k = adj1[p]; k; k = k->nxt)
			if(!vis[k->to]) {
				dfs_calc(k->to, d + k->val);
				mov = d;
///*bgg*/printf("dfs_calc %d ~ %d mov = %lld\n",p,k->to,mov);
				merge(T[p], T[k->to]);
///*bgg*/getchar();
			}
	}

	void __main__() {
		null = new Node;
		*null = {null, null, -inf, -inf};

		std::cin >> N; N0 = N;
		for(int i = 1; i < N; ++i) {
			int x, y, v;
			std::cin >> x >> y >> v;
			link(adj1, x, y, v);
		}
		for(int i = 1; i <= N; ++i) *(Th[i] = T + i) = null;
		dfs_build(1);
		memset(adj1 + 1, 0, N * sizeof adj1[0]);
		for(int i = 1; i < N; ++i) {
			int x, y, v;
			std::cin >> x >> y >> v;
			link(adj1, x, y, v);
		}
///*bgg*/printf("read init done\n");
		dfs_cnt(1);
		divide(1, N0);
		dfs_calc(1, 0);
		std::cout << ans << std::endl;
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);
	__banban_hao_ke_ai__::__main__();
}