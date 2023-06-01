#include <bits/stdc++.h>
using namespace std;
const int N=100010;
int n,m;
struct node{
    int v,nex,w;
} edge[N<<1];
int a[N];
int first[N],cnt;
void add(int u,int v,int w){
    edge[++cnt]={v,first[u],w};
    first[u]=cnt;
}
int vis[N],rt,siz[N],dp[N];
void dfs(int u,int fa,int sum){
    siz[u]=1;
    dp[u]=0;
    for(int i=first[u];i;i=edge[i].nex){
        int v=edge[i].v;
        if(v==fa||vis[v]) continue;
        dfs(v,u,sum);
        siz[u]+=siz[v];
        dp[u]=max(dp[u],siz[v]);
    }
    dp[u]=max(dp[u],sum-siz[u]);
    if(dp[u]<dp[rt]) rt=u;
}
int tot,dis[N];
int sum[4];
void getdis(int u,int fa){
    sum[dis[u]%3]++;
    for(int i=first[u];i;i=edge[i].nex){
        int v=edge[i].v;
        if(v==fa||vis[v]) continue;
        dis[v]=dis[u]+edge[i].w;
        getdis(v,u);
    }
}
int ans=0;
int getans(int u,int w){
    sum[0]=sum[1]=sum[2]=0;
    dis[u]=w;
    getdis(u,0);
    return sum[1]*sum[2]*2+sum[0]*sum[0];
}
void solve(int u){
    vis[u]=1;
    ans+=getans(u,0);
    for(int i=first[u];i;i=edge[i].nex){
        int v=edge[i].v;
        if(vis[v])continue;
        ans-= getans(v,edge[i].w);
        rt=0;
        dp[rt]=0x3f3f3f3f;
        dfs(v,0,siz[v]);
        solve(rt);
    }
}
int main(){
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        add(u,v,w);
        add(v,u,w);
    }
    dp[0]=n;
    dfs(1,0,n);
    solve(rt);
    int tmp=n*n;
    int gcd=__gcd(ans,tmp);
    ans/=gcd;tmp/=gcd;
    cout<<ans<<"/"<<tmp;
}