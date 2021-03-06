#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>

using namespace std;

#define ops "4"

const int maxn=510;

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
	n=399;m=0;k=100;
	for (int a=1;a<=3;a++)
		for (int b=1;b<=132;b++)
		{
			m++;
			ed[m][0]=(a-1)*133+b;
			ed[m][1]=(a-1)*133+b+1;
		}
	for (int a=1;a<=n;a++)
		for (int b=1;b<=k;b++)
			t[a][b]=rand()%500+500;
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
	make_data();
	output();
	run_data();

	return 0;
}
