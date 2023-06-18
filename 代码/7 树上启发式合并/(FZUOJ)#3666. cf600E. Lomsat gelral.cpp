#include <bits/stdc++.h>
const int N=1000000;
#define int long long
using namespace std;
struct node{
    int v,nex;
}a[N];
int cnt,first[N];
void add(int u,int v){
    a[++cnt]={v,first[u]};
    first[u]=cnt;
}
int col[N];
int siz[N],son[N];
void dfs1(int u,int fa){
    siz[u]=1;
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==fa) continue;
        dfs1(v,u);
        siz[u]+=siz[v];
        if(siz[v]>siz[son[u]])son[u]=v;
    }
}
int SON;
int check[N];
int MAX;
int sum;
void solve(int u,int fa,int opt){
    check[col[u]]+=opt;
    if(check[col[u]]>MAX){
        MAX=check[col[u]];
        sum=col[u];
    }
    else if(check[col[u]]==MAX){
        sum+=col[u];
    }
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==fa||v==SON) continue;
        solve(v,u,opt);
    }
}
int ans[N];
void dfs2(int u,int fa,int opt){
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==fa)continue;
        if(v!=son[u]) dfs2(v,u,0);
    }
    if(son[u]){
        dfs2(son[u],u,1);
        SON=son[u];
    }
    solve(u,fa,1);
    SON=0;
    ans[u]=sum;
    if(!opt){
        solve(u,fa,-1);
        MAX=sum=0;
    }

}
signed main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>col[i];
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        add(u,v);
        add(v,u);
    }
    dfs1(1,0);
    dfs2(1,0,0);
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<' ';
    }
}