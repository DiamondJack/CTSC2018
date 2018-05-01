#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<set>
#include<ctime>
#include<random>
using namespace std;

int NUM;

int n,m,lmax,pmax;
bool chain;

default_random_engine generator;

long long rand(long long min,long long max) {
  uniform_int_distribution<long long> ui(min,max);
  return ui(generator);
}

int main(int argc,char **argv)
{
  freopen("juice.in","w",stdout);
  
  sscanf(argv[1],"%d",&NUM);
  generator.seed(time(0)+NUM);
  rand(1,2);
  
  lmax = pmax = 100000;
  n = m = 100000;
  if (NUM < 2) n = 10, m = 10;
  else if (NUM < 5) n = m = 500;
  else if (NUM < 9) pmax = 1;
  else if (NUM < 14) lmax = 1;
  printf("%d %d\n",n,m);
  for (int i = 0;i < n;i++) {
    long long d = rand(1,100000),p;
    if (pmax == 1) p = 1;
    else p = (d / 100 * 99) + rand(1,1000);
    printf("%lld %lld %lld\n",d,p,rand(1,lmax));
  }
  long long gmax = n;
  gmax *= pmax;
  gmax *= lmax;
  gmax /= 50;
  long long Lmax = n;
  Lmax *= lmax;
  Lmax /= 100;
  for (int i = 0;i < m;i++) printf("%lld %lld\n",rand(1,gmax),rand(1,Lmax));
  return 0;
}
