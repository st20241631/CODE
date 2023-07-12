#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
struct node{
    int v,nex;
}a[N*5];
int first[N],cnt;
void add(int u,int v){
    a[++cnt]={v,first[u]};
    first[u]=cnt;
}

int n,m,k;

int dep[N],fa[N];
bool vis[N];
void solve1(){
    cout<<"1\n";
    if(m==n-1){
        vector<int> ans1,ans2;
        for(int i=1;i<=n;i++){
            if(dep[i]&1) ans1.push_back(i);
            else ans2.push_back(i);
        }
        if(ans1.size()>ans2.size()){
            for(int i=1;i<=(k+1)/2;i++){
                cout<<ans1.back()<<" ";
                ans1.pop_back();
            }
        }
        else{
            for(int i=1;i<=(k+1)/2;i++){
                cout<<ans2.back()<<" ";
                ans2.pop_back();
            }
        }
    }
    else{
        int p=1;
        for(int i=1;i<=n;i++){
            if(dep[i]>dep[p]) p=i;
        }
        for(int i=1;i<=(k+1)/2;i++){
            cout<<p<<" ";
            p=fa[fa[p]];
        }
    }
    exit(0);
}
void solve2(int u,int v){
    cout<<"2\n";
    cout<<dep[u]-dep[v]+1<<"\n";
    while (u!=v){
        cout<<u<<" ";
        u=fa[u];
    }
    cout<<v;
    exit(0);
}
void dfs(int u,int dad){
    fa[u]=dad;
    dep[u]=dep[dad]+1;
    vis[u]= true;
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==dad) continue;
        if(vis[v]){
            if(dep[u]<dep[v])continue;
            if(dep[u]-dep[v]+1<=k) solve2(u,v);
            continue;
        }
        dfs(v,u);
    }
}
int main(){
    cin>>n>>m>>k;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        add(u,v);
        add(v,u);
    }
    dfs(1,0);
    solve1();

}