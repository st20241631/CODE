#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e4+5;
int n,q[N];
int dp[N];
struct node {
	int w,l;
} a[N];
bool cmp(node a,node b){
    return a.l==b.l?a.w>b.w:a.l>b.l;
}
int X(int i,int j){return a[i+1].l-a[j+1].l;}
int Y(int i,int j){return dp[j]-dp[i];}
signed main() {
	cin>>n;
	for(int i=1;i<=n;++i) cin>>a[i].w>>a[i].l;
	sort(a+1,a+n+1,cmp);
	int tmp=0;
	for(int i=1;i<=n;++i) if(a[i].w>a[tmp].w) a[++tmp]=a[i];
	n=tmp;
	int l=1,r=1;
	q[1]=0;
	for(int i=1;i<=n;++i) {
		while(l<r&&Y(q[l+1],q[l])>=a[i].w*X(q[l+1],q[l])) ++l;
		dp[i]=dp[q[l]]+1LL*a[q[l]+1].l*a[i].w;
		while(l<r&&Y(q[r],q[r-1])*X(i,q[r])>=Y(i,q[r])*X(q[r],q[r-1])) --r;
		q[++r]=i;
	}
	cout<<dp[n];
	return 0;
}