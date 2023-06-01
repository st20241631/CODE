#include<bits/stdc++.h>
using namespace std;
struct edge{
    int v,nex;
}a[300050*2];
int first[300050],cnt;
void add(int u,int v){
    a[++cnt]=edge{v,first[u]};
    first[u]=cnt;
}
int heigth[300050],fa[300050][20];
void init(int u,int f){
    heigth[u]=heigth[f]+1;
    fa[u][0]=f;
    for(int i=1;i<=17;i++){
        fa[u][i]=fa[fa[u][i-1]][i-1];
    }
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==f) continue;
        init(v,u);
    }
    return;
}
int LCA(int x,int y){
    if(heigth[x]<heigth[y])swap(x,y);
    for(int i=17;i>=0;i--){
        if(heigth[fa[x][i]]>=heigth[y]){
            x=fa[x][i];
        }
    }
    if(x==y)return x;
    for(int i=17;i>=0;i--){
        if(fa[x][i]!=fa[y][i]){
            x=fa[x][i];
            y=fa[y][i];
        }
    }
    return fa[x][0];

}
int diff[300050];
void dfs(int u,int f){
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==f) continue;
        dfs(v,u);
        diff[u]+=diff[v];
    }
}
int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        add(u,v);
        add(v,u);
    }
    init(1,0);
    for(int i=1;i<=m;i++){
        int x,y;
        cin>>x>>y;
        int lca=LCA(x,y);
        diff[x]++;
        diff[y]++;
        diff[lca]-=2;
    }
    dfs(1,0);
    int ans=0;
    for(int i=2;i<=n;i++){
        if(diff[i]==1)ans++;
        if(diff[i]==0)ans+=m;
    }
    cout<<ans;
    return 0;
}