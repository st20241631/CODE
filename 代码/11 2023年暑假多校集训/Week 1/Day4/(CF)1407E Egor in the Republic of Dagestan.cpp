#include <bits/stdc++.h>
using namespace std;
struct node{
    int v,nex,w;
}a[10000000];
int first[1000000],cnt;
void add(int u,int v,int w){
    a[++cnt]=node{v,first[u],w};
    first[u]=cnt;
}

int color[1000000];
bool vis[1000000];
int dis[1000000];
int main(){
    int n,m;
    cin>>n>>m;
    if(n==1) { cout <<"0\n0";return 0;}
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        add(v,u,w);
    }
    queue<int> q;
    memset(color,-1,sizeof color);
    vis[n]= true;
    q.push(n);
    while(!q.empty()){
        int now=q.front();
        q.pop();
        if(now==1) break;
        for(int i=first[now];i;i=a[i].nex){
            int v=a[i].v;
            if(vis[v]) continue;
            if(color[v]==-1||color[v]==1-a[i].w){
                color[v]=1-a[i].w;
            }
            else{
                q.push(v);
                dis[v]=dis[now]+1;
                vis[v]=1;
            }
        }
    }
    if(dis[1])cout<<dis[1]<<"\n";
    else cout<<"-1\n";
    for(int i=1;i<=n;i++){
        if(color[i]==-1) cout<<0;
        else cout<<color[i];
    }
}