#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<queue>
#include "testlib.h"

using namespace std;

const int maxn=1010;

int argc=4;
char *argv[4];

int n,m,k,en,r[maxn][maxn],t[maxn][maxn],w[maxn],in[maxn];

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
	return a.v>b.v;
}

priority_queue<rec> q[maxn],event;

void work()
{
	n = inf.readInt(1,1000);
	m = inf.readInt(0,n*(n-1)/2);
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
	for (int a=1;a<=n;a++)
		for (int b=1;b<=k;b++)
			r[a][b] = inf.readInt(0,100000);

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
	if (solved == n)
	{
		quitf(_ok,"Outputs ok and at least 1 score you get with task 1 value %d and task 2 value %d",totalt,maxt);
	}
	else
	{
		quitf(_wa,"The input or the output error, we think that there is cycle in the graph");
	}
}

int main(int argcs,char *argvs[])
{
	if (argcs != 3)
	{
		printf("You should run like:./simulator input_file answer_file\n");
		return 0;
	}
	for (int a=0;a<4;a++)
		argv[a]=new char[100];
	sprintf(argv[0],"%s",argvs[0]);
	sprintf(argv[1],"%s",argvs[1]);
	sprintf(argv[2],"%s",argvs[2]);
	sprintf(argv[3],"%s",argvs[2]);
	registerTestlibCmd(argc, argv);
	work();

	return 0;
}
