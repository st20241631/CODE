#include <bits/stdc++.h>
using namespace std;
const int N=1000000;
struct node{
    int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
    a[++cnt]=node{v,first[u]};
    first[u]=cnt;
}

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
}
int top[N];
void dfs2(int u){
    if(son[u]){
        int v=son[u];
        top[v]=top[u];
        dfs2(v);
    }
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(top[v]) continue;
        top[v]=v;
        dfs2(v);
    }
}
int lca(int u,int v){
    int x=top[u],y=top[v];
    while(x!=y){
        if(depth[x]<depth[y]){ swap(x,y), swap(u,v);}
        u=fa[x];
        x=top[u];
    }
    if(depth[u]>depth[v]) swap(u,v);
    return u;
}
int main(){
    int n,q;
    cin>>n>>q;
    for(int i=1;i<n;i++){
        int x,y;
        cin>>x>>y;
        add(x,y);
        add(y,x);
    }
    dfs1(1,0);
    top[1]=1;
    dfs2(1);
    for(int i=1;i<=q;i++){
        int a,b,c,d;
        cin>>a>>b>>c>>d;
        int lca1= lca(a,b),lca2= lca(c,d);
        if((depth[lca1]>=depth[lca2])&&((lca(lca1,d)==lca1)||(lca(lca1,c)==lca1))){
            puts("Y");
        }
        else if((depth[lca2]>=depth[lca1])&&((lca(lca2,a)==lca2)||(lca(lca2,b)==lca2))){
            puts("Y");
        }
        else puts("N");
    }
}