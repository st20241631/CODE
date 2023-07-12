#include <bits/stdc++.h>
using namespace std;
struct node{
    int v,nex;
}a[10000000];
int first[1000000],cnt;
void add(int u,int v){
    a[++cnt]={v,first[u]};
    first[u]=cnt;

}
vector<int> ans;
bool vis[10000000];
int color[10000000];
void dfs(int u){
    vis[u]=true;
    if(!color[u]){
        color[u]=1;
        ans.push_back(u);
        for(int i=first[u];i;i=a[i].nex){
            int v=a[i].v;
            if(color[v]) continue;
            color[v]=2;
        }
    }
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(!vis[v]) dfs(v);
    }
}
void solve(){
    int n,m;
    cin>>n>>m;

    cnt=0;
    for(int i=1;i<=n;i++) first[i]=vis[i]=color[i]=0;
    ans.clear();

    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        add(u,v);
        add(v,u);
    }
    dfs(1);

    bool flag=true;
    for(int i=1;i<=n;i++){
        if(color[i]==0){
            flag= false;
            break;
        }
    }
    if(!flag) puts("NO");
    else{
        puts("YES");
        cout<<ans.size()<<"\n";
        for(int i:ans) cout<<i<<" ";
        cout<<"\n";
    }
}
int main(){
    int t;
    cin>>t;
    while(t--)solve();
}