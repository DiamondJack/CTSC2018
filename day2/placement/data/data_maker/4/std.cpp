#include<cstdio>
#include<cstdlib>
#include<cstring>

using namespace std;

const int maxn=510;

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


int f[maxn][maxn][2];

void work()
{
	int co = 3;
	int co_size = n/co;
	int ans=0;
	for (int a=1;a<=co;a++)
	{
		memset(f,0x3f,sizeof(f));
		int base = (a-1)*co_size;
		for (int b=1;b<=k;b++)
			f[1][b][0]=t[base+1][b];
		for (int b=2;b<=co_size;b++)
			for (int c=1;c<=k;c++)
				for (int d=1;d<=k;d++)
				{
					int newv=f[b-1][c][0]+t[base+b][d]+r[c][d];
					if (newv<f[b][d][0])
					{
						f[b][d][0]=newv;
						f[b][d][1]=c;
					}
				}
		int minp=1;
		for (int b=2;b<=k;b++)
			if (f[co_size][b][0]<f[co_size][minp][0]) minp=b;
		ans +=f[co_size][minp][0];
		res[base+co_size]=minp;
		for (int b=co_size-1;b>=1;b--)
		{
			minp=f[b+1][minp][1];
			res[base+b]=minp;
		}
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
