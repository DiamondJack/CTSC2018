#include <bits/stdc++.h>

#define Rand() ((rand() << 15) | rand())
using namespace std ;

const int MAXN = 50010 ; 

int L[MAXN] ; 

void Make(int l, int r) { 
		L[r] = r - l + 1; 
		if (l == r) return ; 
		// 90 : 1 , 10 : rand
		for (int i = l; i < r; ) { 
				if (Rand() % 100 < 10) {
						int to = rand() % (r - i) + i ; 
						Make(i, to) ; 
						i = to + 1; 
				}
				else Make(i, i), i ++ ; 
		}
}

void Make2(int l, int r) {
		L[r] = r - l + 1 ;
		if (l == r) return ;
		
		for (int i = l; i < r; ) { 
				if (Rand() % 100 < 90) {
						int to = rand() % (r - i) + i ; 
						Make(i, to) ; 
						i = to + 1; 
				}
				else Make(i, i), i ++ ; 
		}
}


int main() { 

		freopen(".cnt", "r", stdin) ; 
		int kkk ;
		scanf("%d", &kkk) ; 
		srand(kkk * 10000) ; 


		int T = 100, n = 10000 ;

		printf("%d %d\n", T, n) ; 

		while (T --) { 
				int typ = 4 ; 
				if (T != 0) typ = rand() % 3; 
				if (typ == 0) { // maximal the width
						Make(1, n) ; 
				}
				if (typ == 1) { // maximal the depth
						Make2(1, n) ; 
				}

				if (typ == 2) { 
						Make2(1, n) ; 

						int p = Rand() % n + 1 ;
						L[p] = Rand() % p + 1 ; 
				}
				if (typ == 3) { // Li = i 
						for (int i = 1; i <= n; i ++) L[i] = i ; 
				}

				if (typ == 4) { // Li = 1
						for (int i = 1; i < n; i ++) L[i] = 1; 
						L[n] = n ;
				}	
 

				for (int i = 1; i <= n; i ++) {
						printf("%d%c", L[i], i == n ? 10 : ' ') ; 
				}

		}
		freopen(".cnt", "w", stdout) ; 
		printf("%d\n", kkk * rand()) ;
}


