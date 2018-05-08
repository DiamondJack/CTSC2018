#pragma GCC diagnostic error "-std=c++11"
#pragma GCC optimize("-O2")
#include <bits/stdc++.h>
namespace __banban_hao_ke_ai__ {

	using str = std::string;
	const int MAX_N = 410;
	const char C_MAX = 127, C_MIN = 0;
	const str NONE = "";

	class Solver {
		int n;
		char val[MAX_N];
		std::vector<int> adj[MAX_N];
		str f[MAX_N];
		str INF;

		bool cmp(const str& a, const str& b) {
			return a.length() != b.length() ? a.length() < b.length() : a < b;
		}

		str dpl(str tmp, const str& lim) {
			if(tmp[0] == '0') return NONE;
			if(tmp.length() < lim.length()) return NONE;
			if(tmp.length() > lim.length()) {
				for(int k = 0; k < (int) tmp.length(); ++k)
					if(tmp[k] == '?') tmp[k] = (k ? '0' : '1');
				return tmp;
			}
			str f[2]; f[1] = C_MAX; f[0] = " ";
			for(int k = 0; k < (int) tmp.length(); ++k) {
				if(tmp[k] != '?') {
					if(tmp[k] > lim[k]) {f[1] = min(f[1], f[0]) + tmp[k]; f[0] = C_MAX;}
					else if(tmp[k] == lim[k]) {f[1] += tmp[k]; f[0] += tmp[k];}
					else {f[1] += tmp[k]; f[0] = C_MAX;}
				} else {
					f[1] += '0';
					if(lim[k] != '9') f[1] = min(f[1], f[0] + char(lim[k] + 1));
					f[0] += lim[k];
				}
				if(f[1][0] == '0') f[1] = C_MAX;
			}
			tmp = f[1];
			if(tmp[0] == C_MAX) return NONE;
			tmp.erase(tmp.begin());
			if(tmp[0] == '0') return NONE;
			return tmp;
		}
		str dpr(str tmp, const str& lim) {
			if(tmp[0] == '0') return NONE;
			if(tmp.length() > lim.length()) return NONE;
			if(tmp.length() < lim.length()) {
				for(int k = 0; k < (int) tmp.length(); ++k)
					if(tmp[k] == '?') tmp[k] = '9';
				return tmp;
			}
			str f[2]; f[1] = C_MIN; f[0] = " ";
			for(int k = 0; k < (int) tmp.length(); ++k) {
				if(tmp[k] != '?') {
					if(tmp[k] < lim[k]) {f[1] = max(f[1], f[0]) + tmp[k]; f[0] = C_MIN;}
					else if(tmp[k] == lim[k]) {f[1] += tmp[k]; f[0] += tmp[k];}
					else {f[1] += tmp[k]; f[0] = C_MIN;}
				} else {
					f[1] += '9';
					if(lim[k] != '0') f[1] = max(f[1], f[0] + char(lim[k] - 1));
					f[0] += lim[k];
				}
				if(f[1][0] == '0') f[1] = C_MIN;
			}
			tmp = f[1];
			if(tmp[0] == C_MIN) return NONE;
			tmp.erase(tmp.begin());
			if(tmp[0] == '0') return NONE;
			return tmp;
		}

		str dp_init_inner(int p, str lim) {
			str ret = "";
			if(!lim.empty() && !f[p].empty())
				ret = dpr(lim, f[p]);
			if(val[p] != ',') {
				lim += val[p];
				str ret2 = INF;
				for(auto q : adj[p]) {
					str temp = dp_init_inner(q, lim);
					if(cmp(temp, ret2)) ret2 = temp;
				}
				if(cmp(ret, ret2)) ret = ret2;
			}
			return ret;
		}

		void dp_init(int p) {
			if(p > n) return;
			for(auto q : adj[p]) dp_init(q);
			if(val[p] == '?' || val[p] == ',') {
				f[p] = INF;
				for(auto q : adj[p]) {
					str temp = dp_init_inner(q, "");
					if(cmp(temp, f[p])) f[p] = temp;
				}
			}
		}

		bool dp_make_inner(int p, str pre, const str& lim) {
			if(!pre.empty() && pre[0] == '0') return 0;
			if(!f[p].empty()) {
				str temp = dpl(pre, lim);
				if(!temp.empty() && cmp(temp, f[p])) return 1;
			}
			if(val[p] == ',') return 0;
			pre += val[p];
			for(auto q : adj[p]) 
				if(!dp_make_inner(q, pre, lim)) return 0;
			return 1;
		}

		void dp_make(int p, str pre, str lim) {
			if(p > n) return;
			if(val[p] == '?') {
				if(!f[p].empty() && cmp(lim, pre) && cmp(pre, f[p])) val[p] = ',';
				else for(val[p] = '0'; !dp_make_inner(p, pre, lim); ++val[p])
					;
			}
			if(val[p] == ',') {lim = pre; pre = "";}
			else pre += val[p];
			for(auto q : adj[p]) dp_make(q, pre, lim);
		}
		public: void __main__() {
			memset(val, 0, sizeof val);
			std::cin >> (val + 1);
			n = strlen(val + 1);
			printf("n = %d\n", n);
			INF = str(n + 1, '9');
			for(int i = 0; i <= n + 1; ++i) {f[i].clear(); adj[i].clear();}
			val[0] = ',';
			adj[0].push_back(1);
			for(int i = 1; i <= n; ++i) {
				int f = i - 1; std::cin >> f;
				adj[f].push_back(i);
			}
			int n0 = n;
			for(int i = 1; i <= n; ++i) if(adj[i].empty()) {
				adj[i].push_back(++n0);
				val[n0] = ',';
				f[n0] = INF;
			}
			dp_init(0);
			if(f[0].empty()) return (void) puts("failed");
			dp_make(0, "", "0");
			std::cout << str(val + 1, val + n + 1) << std::endl;
		}
	}	sol;

	void __main__() {
		int T; std::cin >> T;
		while(T--) {
			printf("%d\n", T);
			sol.__main__();
		}
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);
	__banban_hao_ke_ai__::__main__();
}