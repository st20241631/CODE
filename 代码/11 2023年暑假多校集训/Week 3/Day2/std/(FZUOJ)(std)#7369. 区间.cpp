#include<algorithm>
#include<cstring>
#include<cctype>
#include<cstdio>
#define rep(i,x,y) for(int i=x; i<=y; ++i)

using namespace std;
const int N=5005,INF=1000000000;
int n,k,tot,m;
struct data{int l,r;} dat[N],p[N];
int ans,f[N],g[N],top,lst,stk[N],mx,len[N];

bool cmp(data a,data b)
{
	return a.r==b.r?a.l>b.l:a.r<b.r;
}

bool gr(int x,int y) {return x>y;}

void ins(int x)
{
	while(top && f[stk[top]-1]+p[stk[top]].r<=f[x-1]+p[x].r) --top;
	stk[++top]=x;
	lst=min(top,lst);
}

int query(int x)
{
	while(p[stk[lst]].r<=p[x].l) ++lst;
	return f[stk[lst]-1]+p[stk[lst]].r-p[x].l;
}

void solve()
{
	rep(i,1,n) f[i]=-INF;
	rep(i,1,k)
	{
		top=0,lst=1,g[0]=-INF;
		rep(j,1,n)
		{
			ins(j);
			g[j]=query(j);
		}
		rep(j,0,n) f[j]=g[j];
		ans=max(ans,f[n]+len[k-i]);
	}
}

int main()
{
	freopen("interval.in","r",stdin);
	freopen("interval.out","w",stdout);
	scanf("%d%d",&n,&k);
	rep(i,1,n) scanf("%d%d",&dat[i].l,&dat[i].r);
	sort(dat+1,dat+1+n,cmp);
	tot=0,mx=0;
	rep(i,1,n) if(!tot || mx<dat[i].l) mx=dat[i].l,p[++tot]=dat[i]; else len[++m]=dat[i].r-dat[i].l;
	sort(len+1,len+1+m,gr);
	rep(i,1,m) len[i]+=len[i-1];
	rep(i,m+1,k) len[i]=-INF;
	n=tot,solve();
	printf("%d\n",ans);
	return 0;
}
