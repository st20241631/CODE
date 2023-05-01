#include <bits/stdc++.h>
using namespace std;
const int N=500010;
struct Node {
    int v,nex,w;
} a[N];
int first[N],cnt;
void add(int u,int v,int w) {
    a[++cnt]=Node{v,first[u],w};
    first[u]=cnt;
}
vector<pair<int,int> > G[N];
int length[N];
void dfs(int u) {
    for(int i=first[u]; i; i=a[i].nex) {
        int v=a[i].v;
        if(!length[v]) {
            length[v]=length[u]+a[i].w;
            dfs(v);
        }
    }
}
int fa[N];
int find(int x){
    if(fa[x]!=x)fa[x]=find(fa[x]);
    return fa[x];
}
int ans[N];
int vis[N];
void Tarjan(int u){
    vis[u]=1;
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(!vis[v]){
            Tarjan(v);
            fa[v]=u;
        }
    }
    for(auto each:G[u]){
        int cx=each.first,cy=each.second;
        if(vis[cx]==2){
            int lca=find(cx);
            ans[cy]=length[u]+length[cx]-2*length[lca];
        }
    }
    vis[u]=2;
}
int n,q;
void init(){
    cnt=0;
    memset(first,0,sizeof first);
    memset(length,0,sizeof length);
    length[1]=1;
    for(int i=1;i<=n;i++)fa[i]=i;
    memset(vis,0,sizeof vis);
}
void solve(){
    cin>>n>>q;
    init();
    for(int i=1;i<n;i++){
        int x,y,w;
        cin>>x>>y>>w;
        add(x,y,w);
        add(y,x,w);
    }
    dfs(1);
    for(int i=1;i<=q;i++){
        int x,y;
        cin>>x>>y;
        G[x].push_back({y,i});
        G[y].push_back({x,i});
    }
    Tarjan(1);
    for(int i=1;i<=q;i++){
        cout<<ans[i]<<"\n";
    }
}

int main(){
    int t;
    cin>>t;
    while(t--) solve();

}