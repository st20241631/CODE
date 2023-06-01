#include <bits/stdc++.h>
using namespace std;
const int N=10000000;
struct node{
    int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
    a[++cnt]=node{v,first[u]};
    first[u]=cnt;
}
int depth[N],fa[N][20],siz[N];
void dfs(int u,int dad){
    depth[u]=depth[dad]+1;fa[u][0]=dad;siz[u]=1;
    for(int i=1;i<=17;i++)fa[u][i]=fa[fa[u][i-1]][i-1];
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==dad) continue;
        dfs(v,u);
        siz[u]+=siz[v];
    }
}
int LCA(int x,int y){
    if(depth[x]<depth[y]) swap(x,y);
    for(int i=17;i>=0;i--)if(depth[fa[x][i]]>=depth[y]) x=fa[x][i];
    if(x==y) return x;
    for(int i=17;i>=0;i--)if(fa[x][i]!=fa[y][i])x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}
int jump(int u,int sum){
    for(int i=17;i>=0;i--)if(depth[fa[u][i]]>=sum)u=fa[u][i];
    return u;
}
int MID(int x,int y){
    int lca=LCA(x,y);
    if(lca==y)return jump(x,(depth[x]+depth[y])/2);
    else{
        int tmp=depth[x]+depth[y]-2*depth[lca];
        return jump(x,depth[x]-tmp/2);
    }
}
int child(int u,int v){
    return jump(v,depth[u]+1);
}
int solve(int x,int y){
    if(depth[x]<depth[y]) swap(x,y);
    int lca=LCA(x,y);
    int dis=depth[x]+depth[y]-2*depth[lca];
    if(dis&1) return 0;
    if(x==y) return siz[1];
    else{
        int mid=MID(x,y);
        if(lca==mid){
            int tmp1= child(mid,x),tmp2= child(mid,y);
            return siz[1]-siz[tmp1]-siz[tmp2];
        }
        else{
            int tmp= child(mid,x);
            return siz[mid]-siz[tmp];
        }
    }

}
int main(){
    int n;
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        add(u,v),add(v,u);
    }
    dfs(1,0);
    int m;
    cin>>m;
    for(int i=1;i<=m;i++){
        int x,y;
        cin>>x>>y;
        cout<<solve(x,y)<<"\n";
    }
}