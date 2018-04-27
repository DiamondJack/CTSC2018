#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>

using namespace std;

#define ops "1"

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
	n=8;m=15;k=3;
	use[0][0]=true;
	for (int a=1;a<=m;a++)
	{
		int p1=0,p2=0;
		while (p1==p2 || use[p1][p2])
		{
			p1=rand()%n+1;
			p2=rand()%n+1;
			if (p1>p2) swap(p1,p2);
		}
		use[p1][p2]=true;
		ed[a][0]=p1;ed[a][1]=p2;
	}
	for (int a=1;a<=n;a++)
		for (int b=1;b<=k;b++)
			t[a][b]=rand()%100+1;
	for (int a=1;a<=k;a++)
		for (int b=1;b<=k;b++)
			if (a!=b) r[a][b]=rand()%20+1;
}

void run_data()
{
	printf("std.exe " ops ".in " ops ".out");
	system("std.exe " ops ".in " ops ".out");
}

int main()
{
	make_data();
	output();
	run_data();

	return 0;
}
