#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<ctime>

using namespace std;

#define ops "6"

const int maxn=110;

int n,m,k;

int ed[maxn*maxn][2];

int t[maxn][maxn],r[maxn][maxn];

bool use[maxn][maxn];

void output()
{
	FILE *f = fopen(ops ".in","w");
	fprintf(f,"%d %d %d 1\n",n,m,k);
	for (int a=1;a<=m;a++)
		fprintf(f,"%d %d\n",ed[a][0],ed[a][1]);
	for (int a=1;a<=n;a++)
		for (int b=1;b<=k;b++)
			fprintf(f,"%d%c",t[a][b],b==k?'\n':' ');
	for (int a=1;a<=k;a++)
		for (int b=1;b<=k;b++)
			fprintf(f,"%d%c",r[a][b],b==k?'\n':' ');
	fclose(f);
}

void make_data()
{
	n=100;m=900;k=2;
	for (int a=1;a<=m;a++)
	{
		int s=0,e=0;
		while (s==e || use[s][e])
		{
			s=rand()%n+1;
			e=rand()%n+1;
			if (s>e) swap(s,e);
		}
		use[s][e]=true;
		ed[a][0]=s;
		ed[a][1]=e;
	}
	for (int a=1;a<=n;a++)
		for (int b=1;b<=k;b++)
			t[a][b]=rand()%50000+50000;
	for (int a=1;a<=k;a++)
		for (int b=1;b<=k;b++)
			if (a!=b) r[a][b]=rand()%20+1;
}

void run_data()
{
	printf("std.exe " ops ".in " ops ".out\n");
	system("std.exe " ops ".in " ops ".out");
}

int main()
{
	srand(time(0));
	make_data();
	output();
	run_data();

	return 0;
}
