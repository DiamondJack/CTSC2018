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

const int maxn = 103;

int n, m, k, r[maxn][maxn], t[maxn][maxn], indeg[maxn];
Edge epool[maxn * maxn], *ebuf(epool), *head[maxn];

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

int best_res, ass[maxn], best_ass[maxn], new_ass[maxn], val;

inline double frand() {
	return (double)rand() / 0x7fffffff;
}

void ann() {
	double lr(.99);
	for (int i = 1; i <= n; ++ i) {
		ass[i] = 1;
		for (int j = 2; j <= k; ++ j) {
			if (t[i][j] < t[i][ass[i]]) {
				ass[i] = j;
			}
		}
	}
	best_res = schedule(ass);
	for (int i = 0; 1; ++ i, lr *= .99) {
		double chgr(.05 + frand() * .9);
		fprintf(stderr, "Batch %d kr = %lf chgr = %lf best = %d\n", i, lr, chgr, best_res);
		clock_t c(clock());
		while (clock() - c < 3 * 60 * 1000000) {
			for (int j = 1; j <= n; ++ j) {
				if (frand() < chgr) {
					new_ass[j] = rand() % k + 1;
				} else {
					new_ass[j] = ass[j];
				}
			}
			int new_res(schedule(new_ass));
			if (new_res < best_res) {
				fprintf(stderr, "new best at %ld us val = %d\n", clock() - c, new_res);
				best_res = new_res;
				FILE* ouf(fopen("best_res.out", "w"));
				for (int j = 1; j <= n; ++ j) {
					fprintf(ouf, "%d ", new_ass[j]);
				}
				fclose(ouf);
				memcpy(best_ass, new_ass, sizeof(best_ass));
			}
			if (new_res < best_res || exp((double)best_res / new_res) * frand() < lr) {
				memcpy(ass, new_ass, sizeof(ass));
			}
		}
		memcpy(ass, best_ass, sizeof(ass));
	}
}

int main(int argc, char* args[]) {
	memset(head, 0, sizeof(head));
	memset(indeg, 0, sizeof(indeg));
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
	ann();
}

