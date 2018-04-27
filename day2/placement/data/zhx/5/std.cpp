#include<cstdio>
#include<cstdlib>
#include<cstring>

using namespace std;

const int maxn=110;

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


int f[maxn][4000][2];

void work()
{
	memset(f,0x3f,sizeof(f));
	int ans=0;
	for (int a=1;a<=k;a++)
		f[1][a%5][0]=t[1][a];
	for (int a=2;a<=n;a++)
		for (int b=0;b<3125;b++)
			for (int c=1;c<=k;c++)
			{
				int nowv=f[a-1][b][0]+t[a][c];
				int nows=b;
				for (int d=a-1;d>=1 && d>=a-5;d--)
				{
					if (use[d][a])
					{
						int e=nows%5;
						if (!e) e=5;
						nowv+=r[e][c];
					}
					nows/=5;
				}
				nows=b*5%3125+c%5;
				if (f[a][nows][0]>nowv)
				{
					f[a][nows][0]=nowv;
					f[a][nows][1]=b;
				}
			}
	int nowp=0;
	for (int a=1;a<3125;a++)
		if (f[n][nowp][0]>f[n][a][0]) nowp=a;
	ans=f[n][nowp][0];
	res[n]=nowp%5;
	for (int a=n;a>=2;a--)
	{
		nowp=f[a][nowp][1];
		res[a-1]=nowp%5;
	}
	for (int a=1;a<=n;a++)
		if (!res[a]) res[a]=5;
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
