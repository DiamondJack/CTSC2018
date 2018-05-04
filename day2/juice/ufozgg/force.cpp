#include<cstdio>
#include<algorithm>
using namespace std;
int n,m;
long long g,L;
struct tp{int d,p,l;}w[100100];
bool cmpp(tp c1,tp c2)
{
	return c1.p<c2.p;
}
int dd[100100];
bool chk(int mind)
{
	int i;
	long long g0=0,L0=0;
	for(i=1;i<=n;++i)
		if(w[i].d>=mind)
		{
			if(L-L0<=w[i].l)
			{
				g0+=(L-L0)*w[i].p;
				L0=L;
			}
			else
			{
				g0+=(long long)w[i].l*w[i].p;
				L0+=w[i].l;
			}
			if(g0>g)
				return false;
			if(L0==L)
				return true;
		}
	return false;
}
int main()
{
	int i,j;
	int left,right,mid;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;++i)
	{
		scanf("%d%d%d",&w[i].d,&w[i].p,&w[i].l);
		dd[i]=w[i].d;
	}
	sort(w+1,w+n+1,cmpp);
	sort(dd+1,dd+n+1);
	for(i=1;i<=m;++i)
	{
		scanf("%lld%lld",&g,&L);
		left=0;
		right=n;
		while(left<right)
		{
			mid=left+right+1>>1;
			if(chk(dd[mid]))
				left=mid;
			else
				right=mid-1;
		}
		if(left==0)
			puts("-1");
		else
			printf("%d\n",dd[left]);
	}
	return 0;
} 
