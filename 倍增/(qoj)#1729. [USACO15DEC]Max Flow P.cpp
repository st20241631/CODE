#include<bits/stdc++.h>
using namespace std;
struct edge{
    int v,nex;
}a[1000000];
int first[1000000],cnt;
void add(int u,int v){
    a[++cnt]=edge{v,first[u]};
    first[u]=cnt;
}
int heigth[100000],fa[1000000][20];
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
int diff[1000000];
int ans=-10000000;
void dfs(int u,int f){
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==f) continue;
        dfs(v,u);
        diff[u]+=diff[v];
    }
    ans=max(ans,diff[u]);
}

int main(){
    int n,k;
    cin>>n>>k;
    for(int i=1;i<=n-1;i++){
        int u,v;
        cin>>u>>v;
        add(u,v);
        add(v,u);
    }
    init(1,0);
    for(int i=1;i<=k;i++){
        int u,v;
        cin>>u>>v;
        int lca=LCA(u,v);
        diff[u]++;
        diff[v]++;
        diff[lca]--;
        diff[fa[lca][0]]--;
    }
    dfs(1,0);
    cout<<ans;
    return 0;
}
