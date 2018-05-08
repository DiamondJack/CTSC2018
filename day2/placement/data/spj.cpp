#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<queue>
#include "testlib.h"

using namespace std;

const int maxn=1010;
const int maxk=1010;
const int maxm=50010;

int argc=4;
char *argv[4];

int n,m,k,en,r[maxk][maxk],t[maxk][maxk],w[maxn],in[maxn];

bool running[maxn];

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

struct rec
{
	int v,p;
	rec(){}
	rec(int a){v=a;p=a;}
	rec(int a,int b){v=a;p=b;}
};

bool operator<(const rec &a,const rec &b)
{
	if (a.v != b.v) {
		return a.v>b.v;
	} else if ((a.p & 1) != (b.p & 1)) {
		return (a.p & 1) < (b.p & 1);
	} else {
		return a.p > b.p;
	}
}

priority_queue<rec> q[maxn],event;

int work()
{
	try
	{
		n = inf.readInt(1,1000);
		m = inf.readInt(0,50000);
		k = inf.readInt(1,1000);
		int op = inf.readInt(1,2);
		for (int a=1;a<=m;a++)
		{
			int p1,p2;
			p1=inf.readInt(1,n);
			p2=inf.readInt(1,n);
			add_edge(p1,p2);
			in[p2]++;
		}
		for (int a=1;a<=n;a++)
			for (int b=1;b<=k;b++)
				t[a][b] = inf.readInt(0,100000);
		for (int a=1;a<=k;a++)
			for (int b=1;b<=k;b++)
				if (a==b) r[a][b] = inf.readInt(0,0);
				else r[a][b] = inf.readInt(0,100000);

		for (int a=1;a<=n;a++)
			w[a] = ouf.readInt(1,k);

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
			int nowt=event.top().v;
			maxt=max(maxt,nowt);
			while (event.size()>0 && event.top().v == nowt)
			{
				rec top = event.top();
				event.pop();
				int id=top.p>>1;
				int op=top.p&1;
				if (op == 0)
				{
					for (edge *e=v[id];e;e=e->next)
					{
						event.push(rec(nowt+r[w[id]][w[e->e]],e->e<<1|1));
						totalt += r[w[id]][w[e->e]];
					}
					solved += 1;
					running[w[id]] = false;
				}
				else
				{
					in[id]--;
					if (!in[id])
					{
						totalt += t[id][w[id]];
						q[w[id]].push(rec(id));
					}
				}
			}
			for (int a=1;a<=k;a++)
				if (!running[a] && q[a].size()>0)
				{
					rec now = q[a].top();
					q[a].pop();
					event.push(rec(nowt+t[now.p][a],now.p<<1));
					running[a]=true;
				}
		}
		if (solved == n)
		{
			int v;
			if (op==1) v=totalt;
			else v=maxt;
			int score=0;
			for (int a=1;a<=10;a++)
			{
				int nowv=ans.readInt(0,1000000000);
				if (v<=nowv) score=a;
			}
			return score; 
		}
		else
		{
			return 0;
		}
	}
	catch (...)
	{
		return 0;
	}
}

int main(int argcs,char *argvs[])
{
	for (int a=0;a<4;a++)
		argv[a]=new char[100];
	sprintf(argv[0],"%s",argvs[0]);
	sprintf(argv[1],"%s",argvs[1]);
	sprintf(argv[2],"%s",argvs[2]);
	sprintf(argv[3],"%s",argvs[3]);
	registerTestlibCmd(argc, argv);
	int v = work();
	freopen(argv[5],"w",stdout);
	printf("%d\n",v);
	fclose(stdout);
	quitf(_ok,"");

	return 0;
}
