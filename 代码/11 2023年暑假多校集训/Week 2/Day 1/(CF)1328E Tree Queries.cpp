#include <bits/stdc++.h>
using namespace std;
const int N=200005;
struct node{
    int v,nex;
}a[N*2];
int first[N],cnt;
void add(int u,int v){
    a[++cnt]={v,first[u]};
    first[u]=cnt;
}
int dep[N];
int father[N];
int siz[N];
int dfn[N],tot;

void dfs(int u,int fa){
    dep[u]=dep[fa]+1;
    father[u]=fa;
    siz[u]=1;
    dfn[u]=++tot;
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==fa) continue;
        dfs(v,u);
        siz[u]+=siz[v];
    }
}
int query[N];
bool cmp(int x,int y){return dep[x]<dep[y];}

bool check(int x,int y){
    return (dfn[x]<=dfn[y]&&dfn[y]<dfn[x]+siz[x]);
}
int main(){
    int n,q;
    cin>>n>>q;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        add(u,v);
        add(v,u);
    }
    dfs(1,1);
    while (q--){
        int k;
        cin>>k;
        for(int i=1;i<=k;i++) { int x;cin>>x;query[i]=father[x];}
        sort(query+1,query+k+1,cmp);
        bool flag=true;
        for(int i=1;i<=k-1;i++){
            if(!check(query[i],query[i+1])) flag= false;
        }
        if(flag) puts("YES");
        else puts("NO");
    }
}