#include <bits/stdc++.h>
namespace __banban_hao_ke_ai__ {

	using str = std::string;
	const int MAX_N = 1010;
	const char C_MAX = 127, C_MIN = 0;
	const str NONE = "";

	char val[MAX_N];
	std::vector<int> adj[MAX_N];
	int n;

	bool cmp(const str& a, const str& b) {
		return a.length() != b.length() ? a.length() < b.length() : a < b;
	}

	bool pig(int p, str last, str cur) {
		if(!cur.empty() && cur[0] == '0') return 0;
		if(val[p] == ',') {
			if(!cmp(last, cur)) return 0;
			last = cur; cur = "";
		} else cur += val[p];
		if(p > n) return 1;
		for(auto q : adj[p]) if(!pig(q, last, cur)) return 0;
		return 1;
	}

	bool dfs_enum(int p) {
		if(p > n) return pig(1, "0", "");
		if(val[p] != '?') return dfs_enum(p + 1);
		val[p] = ','; if(dfs_enum(p + 1)) return 1;
		for(val[p] = '0'; val[p] <= '9'; ++val[p])
			if(dfs_enum(p + 1)) return 1;
		val[p] = '?'; return 0;
	}

	void __main__() {
		std::cin >> (val + 1);
		n = strlen(val + 1);
		val[0] = ',';
		adj[0].push_back(1);
		for(int i = 2; i <= n; ++i) {
			int f = i; std::cin >> f;
			adj[f].push_back(i);
		}
		int n0 = n;
		for(int i = 1; i <= n; ++i) if(adj[i].empty()) {
			adj[i].push_back(++n0);
			val[n0] = ',';
		}
		if(dfs_enum(1)) std::cout << str(val + 1, val + n + 1) << std::endl;
		else puts("failed");
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);
	__banban_hao_ke_ai__::__main__();
}