#include<cstdio>
#include<cstdlib>
#include<cstring>

using namespace std;

const int maxn=110;

int n,m,k,en;

int t[maxn][maxn],r[maxn][maxn],in[maxn];

int res[maxn];

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
	sprintf(djm,"..\\simulator.exe %s %s",args[1],args[2]);
	system(djm);
	FILE *f=fopen("res.txt","r");
	int v;
	fscanf(f,"%d",&v);
	fclose(f);
	return v;
}

//start from here

int nowres[maxn];

void init()
{
	FILE *f = fopen(args[1],"r");
	fscanf(f,"%d%d%d%*d",&n,&m,&k);
	for (int a=1;a<=m;a++)
	{
		int s,e;
		fscanf(f,"%d%d",&s,&e);
		add_edge(s,e);
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

void dfs(int now)
{
	if (now>n)
	{
		FILE *f = fopen(args[2],"w");
		for (int a=1;a<=n;a++)
			fprintf(f,"%d ",nowres[a]);
		fclose(f);
		int v=judge();
		for (int a=1;a<=n;a++)
			printf("%d ",nowres[a]);
		printf(":%d\n",v);
		if (v<ans)
		{
			ans=v;
			for (int a=1;a<=n;a++)
				res[a]=nowres[a];
		}
		return;
	}
	for (int a=1;a<=k;a++)
	{
		nowres[now]=a;
		dfs(now+1);
	}
}

void work()
{
	dfs(1);
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
