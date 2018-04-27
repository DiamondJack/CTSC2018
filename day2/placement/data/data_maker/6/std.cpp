#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>

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
	int e,f;
	edge *next,*op;
}*v[maxn],ed[maxn*maxn];

void add_edge(int s,int e)
{
	en++;
	ed[en].next=v[s];v[s]=ed+en;v[s]->e=e;
}

int judge()
{
	sprintf(djm,"..\\simulator.exe %s %s",args[1],args[2]);
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

int depth[maxn],q[maxn];


void add_edge(int s,int e,int f)
{
	en++;
	ed[en].next=v[s];v[s]=ed+en;v[s]->e=e;v[s]->f=f;
	en++;
	ed[en].next=v[e];v[e]=ed+en;v[e]->e=s;v[e]->f=0;
	v[s]->op=v[e];v[e]->op=v[s];
}

bool bfs()
{
	memset(depth,0,sizeof(depth));
	int front=1,tail=1;
	q[1]=0;
	depth[0]=1;
	for (;front<=tail;)
	{
		int now=q[front++];
		for (edge *e=v[now];e;e=e->next)
			if (e->f && !depth[e->e])
			{
				depth[e->e]=depth[now]+1;
				q[++tail]=e->e;
			}
	}
	return depth[n<<1|1]!=0;
}

int dfs(int now,int flow)
{
	if (now==(n<<1|1)) return flow;
	int rest=flow;
	for (edge *e=v[now];e && rest;e=e->next)
		if (e->f && depth[e->e]==depth[now]+1)
		{
			int cur_flow=dfs(e->e,min(e->f,rest));
			rest-=cur_flow;
			e->f-=cur_flow;
			e->op->f+=cur_flow;
		}
	return flow-rest;
}

int dinic()
{
	int ans=0;
	while (bfs())
		ans+=dfs(0,0x3f3f3f3f);
	return ans;
}

void work()
{
	en=0;
	memset(v,0,sizeof(v));
	for (int a=1;a<=n;a++)
	{
		add_edge(0,a,t[a][1]);
		add_edge(a,a+n,0x3f3f3f3f);
		add_edge(a+n,n<<1|1,t[a][2]);
	}
	for (int a=1;a<=n;a++)
		for (int b=1;b<=n;b++)
			if (use[a][b]) 
			{
				add_edge(a,b+n,r[2][1]);
				add_edge(b,a+n,r[1][2]);
			}
	int ans=dinic();
	for (edge *e=v[0];e;e=e->next)
		if (!e->f) res[e->e]=1;
		else res[e->e]=2;
	for (edge *e=v[n<<1|1];e;e=e->next)
		if (!e->op->f)
		{
			if (res[e->e-n]==1) printf("%d gg\n",e->e-n);
		}
		else
		{
			if (res[e->e-n]==2) printf("%d gg\n",e->e-n);
		}

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
