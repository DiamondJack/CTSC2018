#include <cstdio>
#include <algorithm>
using namespace std;

#define maxp 100000
#define maxd 100000

struct node {
  node *c[2];
  int l,r;
  long long num,price;
  node(int _l,int _r) {
    c[0] = c[1] = NULL;
    l = _l;
    r = _r;
    num = price = 0;
  }
  node(node *a) {
    c[0] = a->c[0];
    c[1] = a->c[1];
    l = a->l;
    r = a->r;
    num = a->num;
    price = a->price;
  }
};

node *add(node *now,int x,int y) {
  node *ret = new node(now);
  if (ret->l + 1 == ret->r) {
    ret->num += y;
    ret->price += ((long long)x) * y;
  }
  else {
    if (!ret->c[0]) {
      int mid = (ret->l + ret->r) / 2;
      ret->c[0] = new node(ret->l,mid);
      ret->c[1] = new node(mid,ret->r);
    }
    if (x <= ret->c[0]->r) 
      ret->c[0] = add(ret->c[0],x,y);
    else
      ret->c[1] = add(ret->c[1],x,y);
    ret->num = ret->c[0]->num + ret->c[1]->num;
    ret->price = ret->c[0]->price + ret->c[1]->price;
  }
  return ret;
}

long long query(node *now,long long L) {
  
  if (now->l == now->r - 1) return L * now->r;
  if (now->c[0]->num >= L) return query(now->c[0],L);
  return now->c[0]->price + query(now->c[1],L - now->c[0]->num);
}

struct juice{
  int d,p,l;
} a[100100];

bool operator <(juice &a,juice &b) {
  return a.d > b.d;
}

node *root[100100];

int n,m;

int main() {
  scanf("%d%d",&n,&m);
  for (int i = 0;i < n;i++) scanf("%d%d%d",&a[i].d,&a[i].p,&a[i].l);
  sort(a,a+n);
  root[0] = new node(0,100000);
  for (int i = 0;i < n;i++) root[i + 1] = add(root[i],a[i].p,a[i].l);
  
  long long g,L;
  while (m--) {
    scanf("%lld%lld",&g,&L);
    int l = 1,r = n + 1,mid;
    while (l < r) {
      mid = (l + r) / 2;
      if (root[mid]->num < L) l = mid + 1;
        else if (query(root[mid],L) <= g) r = mid;
          else l = mid + 1;
    }
    if (r == n + 1) puts("-1");else printf("%d\n",a[r - 1].d);
  }
  return 0;
}
