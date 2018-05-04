#include <bits/stdc++.h>

#define MOD 998244353
#define G 3

using namespace std ;

int T, n ; 

inline void read(int &a) { 
		a = 0 ; char c = getchar() ; 
		while (isspace(c)) c = getchar() ;
		do a = a * 10 + c - '0', c = getchar(); while (isdigit(c)) ; 
}
const int MAXN = 1 << 18 ; 

int L[MAXN] ; 

int qpow(int a, int b) { 
		int tmp = 1 ;
		for (; b; b >>= 1, a = 1LL * a * a % MOD) if (b & 1) tmp = 1LL * tmp * a % MOD ; 
		return tmp ; 
}

int wn[20], inv[20]; 

void InitNTT() {
	   for (int i = 0, j = 1; i < 20; i ++, j <<= 1) { 
		   wn[i] = qpow(G, (MOD - 1) / j) ; 
		   inv[i] = qpow(wn[i], MOD - 2) ; 
	   }
}

int rev[MAXN] ; 
void NTT(int *a, int n, int typ) { 
		int cnt = 0 ;
		while (n >> cnt) ++ cnt; 
		cnt -- ; 
		for (int i = 0; i < n; i ++) rev[i] = 0; 
		for (int i = 0; i < n; i ++) { 
				rev[i] |= rev[i >> 1] >> 1 ; 
				rev[i] |= (i & 1) << (cnt - 1) ; 
		}
		for (int i = 0; i < n; i ++) if (i < rev[i]) swap(a[i], a[rev[i]]) ; 
		for (int len = 1, p = 1; len < n; len <<= 1, p ++) { 
				int W = typ == 1 ? wn[p] : inv[p] ; 
				for (int j = 0; j < n; j += (len << 1)) { 
					int wk = 1; 
					for (int k = 0; k < len; k ++) { 
						int u = a[j + k], v = 1LL * wk * a[j + k + len] % MOD ;
						a[j + k] = (u + v >= MOD ? u + v - MOD : u + v) ; 
						a[j + k + len] = (u - v < 0 ? u - v + MOD : u - v) ; 
						wk = 1LL * wk * W % MOD ; 
					}
				}
		}
		if (typ < 0) { 
				int I = qpow(n, MOD - 2) ; 
				for (int i = 0; i < n; i ++) a[i] = 1LL * a[i] * I % MOD ; 
		}
}

int f[MAXN] ;

int tmpa[MAXN], tmpb[MAXN] ; 
void Query(int l, int r) { 
		if (l == r) {
				if (l == 0) f[l] = 1 ;
				else if (l == 1) f[l] = 2 ;
				else f[l] += 1LL * (l - 1) * f[l - 1] % MOD, f[l] %= MOD ; 
			    return ; 
		}
		int mid = (l + r) >> 1, len = r - l;  
		Query(l, mid) ; 
		
		if (l == 0) { 
				
				int N = 1; 
				while (N <= len) N <<= 1 ; 
				
				for (int i = 0; i < N; i ++) tmpa[i] = tmpb[i] = 0 ;
				for (int i = 2; i <= mid; i ++) {tmpa[i] = 1LL * (i - 1) * f[i] % MOD, tmpb[i] = f[i];}
			
				NTT(tmpa, N, 1), NTT(tmpb, N, 1) ; 
				for (int i = 0; i < N; i ++) tmpa[i] = 1LL * tmpa[i] * tmpb[i] % MOD ; 
				NTT(tmpa, N, -1) ; 
				for (int i = mid + 1; i <= r; i ++) {
						f[i] += tmpa[i] ; 
						if (f[i] >= MOD) f[i] -= MOD ;
				}
		}		
		else {
				int N = 1; 
				while (N <= len + mid - l) N <<= 1 ; 
				for (int i = 0; i < N; i ++) tmpa[i] = tmpb[i] = 0 ;
			    for (int i = l; i <= mid; i ++) tmpa[i - l] = 1LL * (i - 1) * f[i] % MOD ;
				for (int i = 2; i <= len; i ++) tmpb[i] = f[i] ; 
				NTT(tmpa, N, 1), NTT(tmpb, N, 1) ; 
				for (int i = 0; i < N; i ++) tmpa[i] = 1LL * tmpa[i] * tmpb[i] % MOD ; 
				NTT(tmpa, N, -1) ; 
				for (int i = mid - l + 1; i <= r - l; i ++) {
						f[i + l] += tmpa[i] ; 
						if (f[i + l] >= MOD) f[i + l] -= MOD ;
				}	
				for (int i = 0; i < N; i ++) tmpa[i] = tmpb[i] = 0 ;
			    for (int i = l; i <= mid; i ++) tmpa[i - l] = f[i] % MOD ;
				for (int i = 2; i <= len; i ++) tmpb[i] = 1LL * (i - 1) * f[i] % MOD ; 
				NTT(tmpa, N, 1), NTT(tmpb, N, 1) ; 
				for (int i = 0; i < N; i ++) tmpa[i] = 1LL * tmpa[i] * tmpb[i] % MOD ; 
				NTT(tmpa, N, -1) ; 
				for (int i = mid - l + 1; i <= r - l; i ++) {
						f[i + l] += tmpa[i] ; 
						if (f[i + l] >= MOD) f[i + l] -= MOD ;
				}
		}
		Query(mid + 1, r) ; 
}

int st[MAXN], tp = 0 ;

int main() {

		InitNTT() ; 
		Query(0, 50000) ; 
		read(T) ; 
		read(n) ; 
		while (T --) { 
			int ans = 1 ; 
			tp = 0 ; 
			int flag = 1 ; 
			for (int i = 1; i <= n; i ++) {
					read(L[i]) ; 
					while (tp && st[tp] - L[st[tp]] + 1 >= i - L[i] + 1) tp -- ; 
					if (tp && st[tp] >= i - L[i] + 1) flag = 0 ; 
					st[++ tp] = i ; 
			}
			tp = 0 ; 
			for (int i = 1; i <= n; i ++) { 
					int siz = 1 ; 
					while (tp && st[tp] >= i - L[i] + 1) tp --, siz ++ ;
					ans = 1LL * ans * f[siz - 1] % MOD ;
				    st[++ tp] = i ; 
			}
			if (tp > 1) flag = 0 ;
			if (!flag) puts("0") ;
			else printf("%d\n", ans) ; 
		}
		return 0 ; 
}	
