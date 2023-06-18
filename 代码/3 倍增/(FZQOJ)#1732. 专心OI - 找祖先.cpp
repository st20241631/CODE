#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1000000,mod=1e9+7;
struct node{
    int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
    a[++cnt]=node{v,first[u]};
    first[u]=cnt;
}
int ans[N];
int siz[N],son[N],depth[N],fa[N];
void dfs1(int u,int dad){
    siz[u]=1;
    depth[u]=depth[dad]+1;
    fa[u]=dad;
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==dad) continue;
        dfs1(v,u);
        siz[u]+=siz[v];
        if(siz[v]>siz[son[u]]) son[u]=v;
    }
    ans[u]=(ans[u]+siz[u])%mod;
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==dad) continue;
        ans[u]=(ans[u]+siz[v]*(siz[u]-siz[v])%mod)%mod;
    }
}
signed main(){
    int n,r,m;
    cin>>n>>r>>m;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        add(u,v);
        add(v,u);
    }
    dfs1(r,0);
    for(int i=1;i<=m;i++){
        int x;
        cin>>x;
        cout<<ans[x]%mod<<"\n";
    }
}