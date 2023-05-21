#include <bits/stdc++.h>
using namespace std;
const int N=40000+10;
int n,k;
struct node1{
    int v,nex,w;
}edge[N*4];
struct node2{
    int b,d;
}a[N];
int first[N],cnt;
void add(int u,int v,int w){
    edge[++cnt]={v,first[u],w};
    first[u]=cnt;
}
int vis[N];
int rt,siz[N],dp[N]/*最大子树的大小*/;
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
    dp[u]=max(dp[u],sum-dp[u]);
    if(dp[u]<dp[rt]) rt=u;
}
int dep[N],tot,dis[N],id[N];
void getdis(int u,int fa){
    a[++tot].d=dis[u];
    id[u]=tot;
    if(dep[u]>1) a[tot].b=a[id[fa]].b;
    else a[tot].b=u;
    for(int i=first[u];i;i=edge[i].nex){
        int v=edge[i].v;
        if(v==fa||vis[v]) continue;
        dep[v]=dep[u]+1;
        dis[v]=dis[u]+edge[i].w;
        getdis(v,u);
    }
}
int ans;
int cntt[N];
bool cmp(node2 x,node2 y){return x.d<y.d;}
int getans(int u){
    dep[u]=tot=dis[u]=0;
    getdis(u,0);
    sort(a+1,a+tot+1,cmp);
    memset(cntt,0,sizeof cntt);
    for(int i=2;i<=tot;i++) cntt[a[i].b]++;
    int l=1,r=tot;
    int sum=0;
    while (l<r){
        if(a[l].d+a[r].d<=k){
            sum+=r-l-cntt[a[l].b];
            l++;
            cntt[a[l].b]--;
        }
        else{
            cntt[a[r].b]--;
            r--;
        }
    }
    return sum;
}
void solve(int u){
    vis[u]=1;
    dep[u]=0;
    a[u].b=u;
    ans+= getans(u);
    for(int i=first[u];i;i=edge[i].nex){
        int v=edge[i].v;
        if(vis[v])continue;
        rt=0;
        dfs(v,u,siz[v]);
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
    cin>>k;
    dp[0]=0x3f3f3f3f;
    dfs(1,0,n);
    solve(rt);
    cout<<ans;
}