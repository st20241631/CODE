#include<bits/stdc++.h>
using namespace std;
int dep[20005],f[20005][20],w[20005][20],vis[20005],n,m,q,fa[20005],cnt,first[20005];
struct bian{
    int u,v,w;
}a[50005*2];
struct bian2{
    int v,w,nex;
}b[50005*2];
void add(int u,int v,int w){
    b[++cnt].v=v;
    b[cnt].w=w;
    b[cnt].nex=first[u];
    first[u]=cnt;
}
int cmp(bian x,bian y){
    return x.w>y.w;
}
int find(int x){
    if(fa[x]!=x)fa[x]=find(fa[x]);
    return fa[x];
}
void dfs(int u,int v){
    f[u][0]=v;
    vis[u]=1;
    dep[u]=dep[v]+1;
    for(int i=1;i<=10;i++)f[u][i]=f[f[u][i-1]][i-1],w[u][i]=min(w[u][i-1],w[f[u][i-1]][i-1]);
    for(int i=first[u];i;i=b[i].nex){
        if(b[i].v!=v){
            w[b[i].v][0]=b[i].w;
            dfs(b[i].v,u);
        }
    }

}
int lca(int x,int y){
    if(find(x)!=find(y))return -1;
    int ans=INT_MAX;
    if(dep[x]<dep[y])swap(x,y);
    for(int i=10;i>=0;i--){
        if(dep[f[x][i]]>=dep[y]){
            ans=min(ans,w[x][i]);
            x=f[x][i];
        }
    }
    if(x==y)return ans;
    for(int i=10;i>=0;i--){
        if(f[x][i]!=f[y][i]){
            ans=min(ans,min(w[x][i],w[y][i]));
            x=f[x][i];
            y=f[y][i];
        }
    }
    return min(ans,min(w[x][0],w[y][0]));
}
int main() {
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>a[i].u>>a[i].v>>a[i].w;
    }
    for(int i=1;i<=n;i++)fa[i]=i;
    sort(a+1,a+m+1,cmp);
    int k=0;
    for(int i=1;i<=m;i++){
        int x=find(a[i].u),y=find(a[i].v);
        if(x!=y){
            fa[x]=y;
            add(a[i].u,a[i].v,a[i].w);
            add(a[i].v,a[i].u,a[i].w);
            k++;
        }
        if(k==n-1)break;
    }
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            w[i][0]=0;
            dfs(i,0);
        }
    }
    cin>>q;
    for(int i=1;i<=q;i++){
        int x,y;
        cin>>x>>y;
        cout<<lca(x,y)<<"\n";
    }
    return 0;
}