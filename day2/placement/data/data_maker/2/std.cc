#include <bits/stdc++.h>

using namespace std;

struct Event {
	int step, type, tid;
};

inline bool operator <(const Event& a, const Event& b) {
	if (a.step ^ b.step) {
		return a.step > b.step;
	} else if (a.type ^ b.type) {
		return a.type > b.type;
	} else {
		return a.tid > b.tid;
	}
}

struct Edge {
	int t;
	Edge *ne;
};

const int maxn = 1003;

int n, m, k, r[maxn][maxn], t[maxn][maxn], indeg[maxn];
Edge epool[maxn], *ebuf(epool), *head[maxn];

int schedule(int* assignment) {
	priority_queue<Event> evq;
	static int cnt_deg[maxn], cur[maxn], est[maxn];
	memset(cnt_deg, 0, sizeof(cnt_deg));
	memset(cur, 0, sizeof(cur));
	for (int i = 1; i <= n; ++ i) {
		if (indeg[i] == 0) {
			Event e;
			e.step = 0;
			e.type = 1;
			e.tid = i;
			evq.push(e);
		}
	}
	int res(0);
	while (!evq.empty()) {
		Event e(evq.top());
		evq.pop();
		res = e.step;
		int m(assignment[e.tid]);
		if (e.type == 0) {
			cur[m] = 0;
			for (Edge* ed = head[e.tid]; ed; ed = ed->ne) {
				if (++ cnt_deg[ed->t] == indeg[ed->t]) {
					Event f;
					f.tid = ed->t;
					f.type = 1;
					f.step = res + r[m][assignment[ed->t]];
					evq.push(f);
				}
			}
		} else if (cur[m] == 0) {
			cur[m] = e.tid;
			e.step = est[m] = res + t[e.tid][m];
			e.type = 0;
			evq.push(e);
		} else {
			e.step = est[m];
			evq.push(e);
		}
	}
	return res;
}

int ass[maxn], res_ass[maxn], res;

void DFS(int x) {
	static int cnt(0);
	if (x == n) {
		int v(schedule(ass));
		if (v < res) {
			memcpy(res_ass, ass, sizeof(ass));
			res = v;
			fprintf(stderr, "%d\n", res);
			for (int i = 1; i <= n; ++ i) {
				fprintf(stderr, "%d ", ass[i]);
			}
			fprintf(stderr, "\n");
		}
		if ((++ cnt & 0xffff) == 0) {
			for (int i = 1; i <= n; ++ i) {
				fprintf(stderr, "%d ", ass[i]);
			}
			fprintf(stderr, " %d \n", cnt);
		}
	} else {
		for (int i = 1; i <= k; ++ i) {
			ass[x + 1] = i;
			DFS(x + 1);
		}
	}
}

int main() {
	memset(head, 0, sizeof(head));
	memset(indeg, 0, sizeof(indeg));
	scanf("%d%d%d%*d", &n, &m, &k);
	for (int i = 0; i < m; ++ i) {
		int u, v;
		scanf("%d%d", &u, &v);
		ebuf->t = v;
		ebuf->ne = head[u];
		head[u] = ebuf ++;
		++ indeg[v];
	}
	for (int i = 1; i <= n; ++ i) {
		for (int j = 1; j <= k; ++ j) {
			scanf("%d", t[i] + j);
		}
	}
	for (int i = 1; i <= k; ++ i) {
		for (int j = 1; j <= k; ++ j) {
			scanf("%d", r[i] + j);
		}
	}
	res = 0x3f3f3f3f;
	DFS(0);
	fprintf(stderr, "%d\n", res);
	for (int i = 1; i <= n; ++ i) {
		printf("%d ", res_ass[i]);
	}
	putchar(10);
}

