#include <bits/stdc++.h>

#define MOD 998244353

using namespace std ;

int n ; 

const int MAXN = 1010 ; 

int cov[MAXN], to[MAXN], len[MAXN] ; 

int siz[MAXN];  

int f[MAXN] ; 

int main() { 

		f[0] = 1, f[1] = 2 ; 

		for (int i = 2; i <= 1000; i ++) { 
				f[i] = 1LL * (i - 1) * f[i - 1] % MOD ; 
				for (int j = 2; j <= i - 2; j ++) { 
						f[i] = (1LL * f[i] + 1LL * (j - 1) * f[j] % MOD * f[i - j] % MOD) % MOD ; 
				}
		}

		int T ; 
		scanf("%d", &T) ;
		scanf("%d", &n) ;
		while (T --) { 	
				for (int i = 1; i <= n; i ++) scanf("%d", &len[i]), to[i] = i - len[i] + 1 ; 

				bool flag = 1; 
				for (int i = 1; i <= n; i ++) flag &= (to[i] >= 1) ; 
				memset(cov, 0, sizeof cov) ; 
				for (int i = 1; i <= n; i ++) { 
						siz[i] = 1 ; 
						for (int j = to[i]; j <= i; j ++) { 
								if (to[j] < to[i]) flag = 0 ; 
								if (!cov[j] && j < i) cov[j] = i, siz[i] ++ ; 
						}
				}



				for (int i = 1; i < n; i ++) { 
						if (!cov[i]) { 
								flag = 0 ; 
						}
				}
				if (!flag) {
						puts("0") ; 
						continue ;  
				}
				int ans = 1 ; 
				for (int i = 1; i <= n; i ++) ans = 1LL * ans * f[siz[i] - 1] % MOD;  
				printf("%d\n", ans);  
		}

}

