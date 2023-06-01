#include <bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int n,k;
struct node{
    int v,nex,w;
} edge[N<<1];
int dis[N],Edge[N];
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
int tot;
void getdis(int u,int fa,int sum,int val){
    if(val>k) return;
    dis[++tot]=val;
    Edge[tot]=sum;
    for(int i=first[u];i;i=edge[i].nex){
        int v=edge[i].v;
        if(v==fa||vis[v]) continue;
        getdis(v,u,sum+1,val+edge[i].w);
    }
}
int ans=0x3f3f3f3f;
int mn[N];//mn[i]:长度为i所需要的最小边数
void getans(int u){
    int tmpcnt;
    tot=0;
    mn[0]=0;
    for(int i=first[u];i;i=edge[i].nex){
        tmpcnt=tot;
        int v=edge[i].v;
        if(vis[v]) continue;
        getdis(v,u,1,edge[i].w);
        for(int j=tmpcnt+1;j<=tot;j++) {
            ans=min(ans,mn[k-dis[j]]+Edge[j]);
        }
        for(int j=tmpcnt;j<=tot;j++){
            mn[dis[j]]=min(mn[dis[j]],Edge[j]);
        }
    }
    for(int i=1;i<=tot;i++){
        mn[dis[i]]=0x3f3f3f3f;
    }
}
void solve(int u){
    vis[u]=1;
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
    memset(mn,0x3f,sizeof mn);
    cin>>n>>k;
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        u++,v++;
        add(u,v,w);
        add(v,u,w);
    }
    dp[0]=n;
    dfs(1,0,n);
    solve(rt);
    printf("%d\n",ans>=n?-1:ans);
}