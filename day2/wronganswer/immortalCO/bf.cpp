#pragma GCC diagnostic error "-std=c++11"
#pragma GCC optimize("-O2")
#include <bits/stdc++.h>
namespace __banban_hao_ke_ai__ {

	using ll = long long;
	const int MAX_N = 1000010;

	struct Tree {
		std::vector<std::pair<int, int>> e[MAX_N];
		int fa[MAX_N], dep[MAX_N], cnt[MAX_N], cho[MAX_N], top[MAX_N];
		ll sum[MAX_N];
		void dfs_init(int i) {
			cnt[i] = 1;
			for(auto k : e[i]) if(!cnt[k.first]) {
				fa[k.first] = i;
				dep[k.first] = dep[i] + 1;
				sum[k.first] = sum[i] + k.second;
				dfs_init(k.first);
				cnt[i] += cnt[k.first];
				if(cnt[k.first] > cnt[cho[i]])
					cho[i] = k.first;
			}
		}
		void dfs_make(int i) {
			top[i] = (i == cho[fa[i]] ? top[fa[i]] : i);
			// printf("i = %d top = %d\n", i, top[i]);
			for(auto k : e[i]) if(!top[k.first]) dfs_make(k.first);
		}
		int lca(int x, int y) const {
			while(top[x] != top[y]) {
				dep[top[x]] > dep[top[y]]
					? x = fa[top[x]] : y = fa[top[y]];
			}
			return dep[x] < dep[y] ? x : y;
		}
	}	tree[2];

	void __main__() {
		int N; std::cin >> N;
		for(int k = 0; k <= 1; ++k) {
			for(int i = 1; i < N; ++i) {
				int a, b, v; std::cin >> a >> b >> v;
				tree[k].e[a].push_back({b, v});
				tree[k].e[b].push_back({a, v});
			}
			tree[k].dfs_init(1);
			tree[k].dfs_make(1);
		}
		ll ans = -(1ll << 60);
		for(int i = 1; i <= N; ++i)
			for(int j = i; j <= N; ++j) {
				ll tmp = tree[0].sum[i] + tree[0].sum[j] - tree[0].sum[tree[0].lca(i, j)] - tree[1].sum[tree[1].lca(i, j)];
				// printf("work %d %d tmp = %lld\n", i,j,tmp);
				ans = std::max(ans, tmp);
			}
		std::cout << ans << std::endl;
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);
	__banban_hao_ke_ai__::__main__();
}

#if 0
6

1 2 2
1 3 0
2 4 1
2 5 -7
3 6 0

1 2 -1
2 3 -1
2 5 3
2 6 -2
3 4 8

#endif