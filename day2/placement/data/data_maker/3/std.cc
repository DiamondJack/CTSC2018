#include <bits/stdc++.h>

using namespace std;

const int maxn = 503;
const int inf = 0x3f3f3f3f;

int f[maxn][maxn][maxn], fd[maxn][maxn][maxn], res[maxn];
int n, k, a[maxn][3];

int main() {
	int m1(0), m2(0);
	scanf("%d%*d%d%*d", &n, &k);
	for (int i = 1; i <= n; ++ i) {
		for (int j = 0; j < 3; ++ j) {
			scanf("%d", a[i] + j);
		}
		m1 += a[i][0];
		m2 += a[i][1];
	}
	int cur(0), prv(1);
	memset(f, 0x3f, sizeof(f));
	f[0][0][0] = 0;
	for (int i = 1; i <= n; ++ i) {
		for (int j = 0; j <= m1; ++ j) {
			for (int k = 0; k <= m2; ++ k) {
				if (j + a[i][0] <= m1) {
					if (f[i][j + a[i][0]][k] > f[i - 1][j][k]) {
						f[i][j + a[i][0]][k] = f[i - 1][j][k];
						fd[i][j + a[i][0]][k] = 0;
					}
				}
				if (k + a[i][1] <= m2) {
					if (f[i][j][k + a[i][1]] > f[i - 1][j][k]) {
						f[i][j][k + a[i][1]] = f[i - 1][j][k];
						fd[i][j][k + a[i][1]] = 1;
					}
				}
				if (f[i][j][k] > f[i - 1][j][k] + a[i][2]) {
					f[i][j][k] = f[i - 1][j][k] + a[i][2];
					fd[i][j][k] = 2;
				}
			}
		}
	}
	fprintf(stderr, "FI 1\n");
	int ans(inf), ai, aj;
	for (int i = 0; i <= m1; ++ i) {
		for (int j = 0; j <= m2; ++ j) {
			int s(max(max(i, j), f[n][i][j]));
			if (s < ans) {
				ans = s, ai = i, aj = j;
			}
		}
	}
	fprintf(stderr, "FI 2\n");
	fprintf(stderr, "ANS = %d\n", ans);
	for (int i = n; i > 0; -- i) {
		res[i] = fd[i][ai][aj] + 1;
		switch (fd[i][ai][aj]) {
			case 0:
				ai -= a[i][0];
				break;
			case 1:
				aj -= a[i][1];
				break;
		}
	}
	for (int i = 1; i <= n; ++ i) {
		printf("%d ", res[i]);
	}
	putchar(10);
}

