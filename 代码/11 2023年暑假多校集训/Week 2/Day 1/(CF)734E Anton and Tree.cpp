#include <bits/stdc++.h>

using namespace std;
const int N=200005;
int fa[N];
int color[N];
int u[N],v[N];
int find(int x){
    if(fa[x]!=x) fa[x]=find(fa[x]);
    return fa[x];
}
struct node{
    int v,nex;
}a[N*2];
int first[N],cnt;
void add(int u,int v){
    a[++cnt]={v,first[u]};
    first[u]=cnt;
}
int dep[N];
int MAX;
void dfs(int u,int dad){
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==dad) continue;
        dep[v]=dep[u]+1;
        if(dep[v]>dep[MAX]) MAX=v;
        dfs(v,u);
    }
}
int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) fa[i]=i;
    for(int i=1;i<=n;i++) cin>>color[i];
    for(int i=1;i<n;i++){
        cin>>u[i]>>v[i];
        int fu= find(u[i]),fv= find(v[i]);
        if(color[fu]==color[fv]) fa[fu]=fv;
    }
    for(int i=1;i<=n;i++){
        int fu= find(u[i]),fv= find(v[i]);
        if(fu!=fv){
            add(fu,fv);
            add(fv,fu);
        }
    }
    dfs(find(1),0);
    dep[MAX]=0;
    dfs(MAX,0);
    cout<<((dep[MAX]+1)>>1);
}