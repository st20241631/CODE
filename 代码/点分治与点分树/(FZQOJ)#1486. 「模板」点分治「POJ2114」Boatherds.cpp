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
unordered_map<int,int> Hash;
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
void getdis(int u,int fa){
    a[++tot]=dis[u];
    for(int i=first[u];i;i=edge[i].nex){
        int v=edge[i].v;
        if(v==fa||vis[v]) continue;
        dis[v]=dis[u]+edge[i].w;
        getdis(v,u);
    }
}
int pro[N],ans[N],tmp[N];
void getans(int u){
    int tmpsum=0;
    for(int i=first[u];i;i=edge[i].nex){
        int v=edge[i].v;
        if(vis[v]) continue;
        tot=0;
        dis[v]=edge[i].w;
        getdis(v,u);
        for(int j=tot;j>=1;j--)for(int k=1;k<=m;k++)if(pro[k]>=a[j])ans[k]|=Hash[pro[k]-a[j]];
        for(int j=tot;j>=1;j--)Hash[a[j]]=1,tmp[++tmpsum]=a[j];
    }
    for(int i=1;i<=tmpsum;i++)Hash[tmp[i]]=0;
}
void solve(int u){
    vis[u]=1;
    Hash[0]=1;
    getans(u);
    for(int i=first[u];i;i=edge[i].nex){
        int v=edge[i].v;
        if(vis[v])continue;
        rt=0;
        dp[rt]=0x3f3f3f3f;
        dfs(v,0,siz[v]);
        solve(rt);
    }
}
int main(){
    cin>>n>>m;
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        add(u,v,w);
        add(v,u,w);
    }
    for(int i=1;i<=m;i++)cin>>pro[i];
    dp[0]=n;
    dfs(1,0,n);
    solve(rt);
    for(int i=1;i<=m;i++)puts(ans[i]==1?"AYE":"NAY");
}