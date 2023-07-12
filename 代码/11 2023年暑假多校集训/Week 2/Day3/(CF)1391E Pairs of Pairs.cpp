#include <bits/stdc++.h>
using namespace std;
const int N=5e5+10,M=1e6+10;
struct node{
    int v,nex;
}a[M*2];
int first[N],cnt;
void add(int u,int v){
    a[++cnt]={v,first[u]};
    first[u]=cnt;
}

bool vis[N];
int fa[N],dep[N];
vector<int> G[N];
void dfs(int u,int dad){
    fa[u]=dad;
    dep[u]=dep[dad]+1;
    G[dep[u]].push_back(u);
    vis[u]= true;
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(vis[v]) continue;
        dfs(v,u);
    }
}
void solve(){
    int n,m;
    cin>>n>>m;

    cnt=0;
    for(int i=1;i<=n;i++) {
        first[i]=0;
        vis[i]= false;
        G[i].clear();
        fa[i]=0;
        dep[i]=0;
    }

    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        add(u,v);
        add(v,u);
    }
    dfs(1,0);
    for(int i=1;i<=n;i++){
        if(dep[i]>=(n+1)/2){
            puts("PATH");
            cout<<dep[i]<<"\n";
            while (i){
                cout<<i<<" ";
                i=fa[i];
            }
            cout<<"\n";
            return;
        }
    }
    puts("PAIRING");
    int tot=0;
    for(int i=1;i<=n;i++){
        tot+=G[i].size()/2;
    }
    cout<<tot<<"\n";
    for(int i=1;i<=n;i++){
        for(int j=0;j+1<G[i].size();j+=2){
            cout<<G[i][j]<<" "<<G[i][j+1]<<"\n";
        }
    }
    return;
}
int main(){
    int t;
    cin>>t;
    while(t--)solve();
}