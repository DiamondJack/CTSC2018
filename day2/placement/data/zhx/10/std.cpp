#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>

using namespace std;

const int maxn=210;

int n,m,k,en;

int t[maxn][maxn],r[maxn][maxn],in[maxn];

int res[maxn];

bool use[maxn][maxn];

char args[100][100];

char djm[1000];

int ans=0x3f3f3f3f;

struct edge
{
	int e;
	edge *next;
}*v[maxn],ed[maxn*maxn];

void add_edge(int s,int e)
{
	en++;
	ed[en].next=v[s];v[s]=ed+en;v[s]->e=e;
}

int judge()
{
	sprintf(djm,"..\\simulator_easy.exe %s %s",args[1],args[2]);
	system(djm);
	FILE *f=fopen("res.txt","r");
	int v;
	fscanf(f,"%d",&v);
	fclose(f);
	return v;
}

//start from here

void init()
{
	FILE *f = fopen(args[1],"r");
	fscanf(f,"%d%d%d%*d",&n,&m,&k);
	for (int a=1;a<=m;a++)
	{
		int s,e;
		fscanf(f,"%d%d",&s,&e);
		add_edge(s,e);
		use[s][e]=true;
		in[e]++;
	}
	for (int a=1;a<=n;a++)
		for (int b=1;b<=k;b++)
			fscanf(f,"%d",&t[a][b]);
	for (int a=1;a<=k;a++)
		for (int b=1;b<=k;b++)
			fscanf(f,"%d",&r[a][b]);
	fclose(f);
}

bool running[maxn];

struct rec
{
	int v,p;
	rec(){}
	rec(int a){v=a;p=a;}
	rec(int a,int b){v=a;p=b;}
};

bool operator<(const rec &a,const rec &b)
{
	return a.v>b.v;
}

priority_queue<rec> q[maxn],event;

int simulate(int *w)
{	
	memset(in,0,sizeof(in));
	memset(running,false,sizeof(running));
	for (int a=1;a<=n;a++)
		for (edge *e=v[a];e;e=e->next)
			in[e->e]++;
	for (int a=1;a<=n;a++)
		while (q[a].size())
			q[a].pop();
	while (event.size())
		event.pop();

	int totalt=0,maxt=0;
	for (int a=1;a<=n;a++)
		if (!in[a]) 
		{
			q[w[a]].push(a);
			totalt += t[a][w[a]];
		}

	for (int a=1;a<=k;a++)
		if (q[a].size() > 0)
		{
			running[a] = true;
			rec top = q[a].top();
			q[a].pop();
			event.push(rec(t[top.p][a],top.p<<1));
		}

	int solved = 0;
	while (event.size() > 0)
	{
		rec top = event.top();
		event.pop();
		int id=top.p>>1;
		int op=top.p&1;
		int nowt=top.v;
		maxt=max(maxt,nowt);
		if (op == 0)
		{
			for (edge *e=v[id];e;e=e->next)
			{
				event.push(rec(nowt+r[w[id]][w[e->e]],e->e<<1|1));
				totalt += r[w[id]][w[e->e]];
			}
			solved += 1;
			if (q[w[id]].size() > 0)
			{
				rec top = q[w[id]].top();
				q[w[id]].pop();
				event.push(rec(nowt+t[top.p][w[id]],top.p<<1));
			}
			else running[w[id]] = false;
		}
		else
		{
			in[id]--;
			if (!in[id])
			{
				totalt += t[id][w[id]];
				q[w[id]].push(rec(id));

				if (!running[w[id]])
				{
					rec top = q[w[id]].top();
					q[w[id]].pop();
					event.push(rec(nowt+t[top.p][w[id]],top.p<<1));
					running[w[id]] = true;
				}
			}
		}
	}

	return totalt;
}

int x[maxn],y[maxn],z[maxn];

namespace Fire
{
	double getCost(int *z)
	{
		return simulate(z);
	}
	void generate(int *z)
	{
		for (int a=1;a<=n;a++)
			z[a]=rand()%k+1;
	}
	double calcStartTemp() {
		double s = 0, last = 0;
		int cnt = 200;
		generate(x);
		last=getCost(x);
		for (int i = 0; i < cnt; ++ i) {
			random_shuffle(x+1,x+n+1);	// generate random state
			double now =getCost(x);
			s += fabs(now - last);
			last = now;
		}
		return (s / cnt) / log(1.0 / 0.9);
	}
	void dropTemp(double &T)
	{
		double alpha=0.995;
		T=T*alpha;
	}
	bool transfer(double T,double c1, double c2) {
		if (c1 > c2) return true;
		double t = (double)rand() / RAND_MAX;
		return (t < exp((c1 - c2) / T));
	}
	void solve() {
		generate(z);
		double nowbest=getCost(z),cost=0;

		for (int a=1;a<=10;a++)
		{
			double T = calcStartTemp();
			double T_end = 1e-3;
			cost = getCost(x);
			fprintf(stdout,"Process start! Initial Temperature: %.3lf , cost: %.3lf\n", T, cost);
			while (T > T_end) {
				for (int i = 0; i < n*10; ++ i) {
					for (int a=1;a<=n;a++)
						y[a]=x[a];
					y[rand()%n+1]=rand()%k+1;

					double newcost = getCost(y);
					if (transfer(T,cost, newcost)) {
						for (int a=1;a<=n;a++)
							x[a]=y[a];
						cost = newcost;
					}
					if (cost<nowbest)
					{
						nowbest=cost;
						ans=cost;
						for (int a=1;a<=n;a++)
							z[a]=x[a];
					}
				}
				dropTemp(T);
				fprintf(stdout,"Now Temperature: %lf , cost: %lf nowbest:%lf\n", T, cost,nowbest);

			}
		}

	}
};


void work()
{
	freopen("log","w",stderr);
	fclose(stderr);
	Fire::solve();
	for (int a=1;a<=n;a++)
		res[a]=z[a];

	FILE *f=fopen(args[2],"w");
	for (int a=1;a<=n;a++)
		fprintf(f,"%d%c",res[a],a==n?'\n':' ');
	fclose(f);
	int v=judge();
	if (v!=ans)
	{
		printf("%d sb\n",ans);
	}
}

void output()
{
	FILE *f=fopen(args[2],"w");
	for (int a=1;a<=n;a++)
		fprintf(f,"%d%c",res[a],a==n?'\n':' ');
	fclose(f);
}


int main(int argc,char *argss[])
{
	for (int a=0;a<argc;a++)
		sprintf(args[a],"%s",argss[a]);
	init();
	work();
	output();

	return 0;
}
