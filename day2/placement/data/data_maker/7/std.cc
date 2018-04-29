#include <bits/stdc++.h>

using namespace std;

const int maxn = 603;
const int maxv = maxn * maxn;

int n, m, k, a[maxn][maxn], pt[maxn * 2], sel[maxn * 2], vl[maxv], rnd[maxn * 2], totv;

int DFS(int p, int i, int v) {
	rnd[p] = i;
	for (int j = 0; j < k; ++ j) {
		if (a[p][j] <= v && pt[j + n] == -1) {
			pt[p] = j;
			pt[j + n] = p;
			return 1;
		}
	}
	for (int j = 0; j < k; ++ j) {
		if (a[p][j] <= v && rnd[pt[j + n]] < i) {
			int q(pt[j + n]);
			pt[p] = j;
			pt[j + n] = p;
			if (DFS(q, i, v)) {
				return 1;
			}
			pt[j + n] = q;
		}
	}
	return 0;
}

int check(int v) {
	for (int i = 0; i < n + k; ++ i) {
		pt[i] = -1;
		rnd[i] = -1;
	}
	for (int i = 0; i < n; ++ i) {
		if (!DFS(i, i, v)) {
			return 0;
		}
	}
	return 1;
}

int main() {
	scanf("%d%d%d%*d", &n, &m, &k);
	totv = 0;
	for (int i = 0; i < n; ++ i) {
		for (int j = 0; j < k; ++ j) {
			scanf("%d", a[i] + j);
			vl[totv ++] = a[i][j];
		}
	}
	sort(vl, vl + totv);
	totv = unique(vl, vl + totv) - vl;
	int l(0), r(totv);
	while (l + 1 < r) {
		int md((l + r)>> 1);
		fprintf(stderr, "Checking %d ", vl[md - 1]);
		if (check(vl[md - 1])) {
			fprintf(stderr, "Succ\n");
			r = md;
		} else {
			fprintf(stderr, "Fail\n");
			l = md;
		}
	}
	fprintf(stderr, "Ans = %d\n", vl[l]);
	fprintf(stderr, "Check %d\n", check(vl[l]));
	for (int i = 0; i < n; ++ i) {
		printf("%d ", pt[i] + 1);
	}
}
