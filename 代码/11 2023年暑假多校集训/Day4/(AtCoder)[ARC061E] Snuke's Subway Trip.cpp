#include <bits/stdc++.h>
using namespace std;
vector<pair<int,int> >G[2000005];
int fa[2000005],vis[2000005],id[2000005];
int find(int x){
    if(fa[x]!=x)return fa[x]= find(fa[x]);
    return fa[x];
}
struct node{
    int v,nex;
}a[4000005];
int first[2000005],cnt;
void add(int u,int v){
    a[++cnt]={v,first[u]};
    first[u]=cnt;
}
int dis[2000005];
int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v,opt;
        cin>>u>>v>>opt;
        G[opt].push_back({u,v});
    }
    int idx=n;
    for(int i=1;i<=1000000;i++){
        if(G[i].empty()) continue;
        for(auto now:G[i]){
            id[now.first]=id[now.second]=-1;
            fa[now.first]=now.first;
            fa[now.second]=now.second;
            vis[now.first]=vis[now.second]=false;
        }
        for(auto now:G[i]){
            int fa1=find(now.first),fa2= find(now.second);
            if(fa1!=fa2)fa[fa1]=fa2;
        }
        for(auto now:G[i]){
            if(!vis[now.first]){
                vis[now.first]=true;
                int tmp= find(now.first);
                if(id[tmp]==-1)  id[tmp]=++idx;
                add(now.first,id[tmp]);
                add(id[tmp],now.first);
            }
            if(!vis[now.second]){
                vis[now.second]=true;
                int tmp= find(now.second);
                if(id[tmp]==-1)  id[tmp]=++idx;
                add(now.second,id[tmp]);
                add(id[tmp],now.second);
            }
        }
    }
    queue<int> q;
    memset(dis,-1,sizeof dis);
    dis[1]=0;
    q.push(1);
    while (!q.empty()){
        int now=q.front();
        q.pop();
        for(int i=first[now];i;i=a[i].nex){
            int v=a[i].v;
            if(dis[v]==-1){
                dis[v]=dis[now]+1;
                q.push(v);
            }
        }
    }
    if(dis[n]==-1) cout<<-1;
    else cout<<dis[n]/2;
    return 0;
}