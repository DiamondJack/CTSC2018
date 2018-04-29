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
const int maxe = 1000003;

int n, m, k, r[maxn][maxn], t[maxn][maxn], indeg[maxn];
Edge epool[maxe], *ebuf(epool), *head[maxn];

int schedule(int* assignment) {
	priority_queue<Event> evq;
	static int cnt_deg[maxn], cur[maxn], est[maxn];
	memset(cnt_deg, 0, sizeof(cnt_deg));
	memset(cur, 0, sizeof(cur));
	memset(est, 0, sizeof(est));
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
				Event f;
				f.tid = ed->t;
				f.type = 1;
				f.step = max(res + r[m][assignment[ed->t]], est[assignment[ed->t]]);
				evq.push(f);
			}
		} else if (++ cnt_deg[e.tid] >= indeg[e.tid]) {
			if (cur[m] == 0) {
				cur[m] = e.tid;
				e.step = est[m] = res + t[e.tid][m];
				e.type = 0;
				evq.push(e);
			} else {
				e.step = est[m];
				evq.push(e);
			}
		}
	}
	return res;
}

int ass[maxn];

int main(int argc, char* args[]) {
	memset(head, 0, sizeof(head));
	memset(indeg, 0, sizeof(indeg));
	if (argc < 3) {
		fprintf(stderr, "Wrong usage. ./sim <input> <your answer>\n");
		return -1;
	}
	FILE* fin(fopen(args[1], "r"));
	fscanf(fin, "%d%d%d%*d", &n, &m, &k);
	for (int i = 0; i < m; ++ i) {
		int u, v;
		fscanf(fin, "%d%d", &u, &v);
		ebuf->t = v;
		ebuf->ne = head[u];
		head[u] = ebuf ++;
		++ indeg[v];
	}
	for (int i = 1; i <= n; ++ i) {
		for (int j = 1; j <= k; ++ j) {
			fscanf(fin, "%d", t[i] + j);
		}
	}
	for (int i = 1; i <= k; ++ i) {
		for (int j = 1; j <= k; ++ j) {
			fscanf(fin, "%d", r[i] + j);
		}
	}
	fclose(fin);
	FILE* fans(fopen(args[2], "r"));
	for (int i = 1; i <= n; ++ i) {
		fscanf(fans, "%d", ass + i);
	}
	fclose(fans);
	printf("Answer = %d\n", schedule(ass));
}

