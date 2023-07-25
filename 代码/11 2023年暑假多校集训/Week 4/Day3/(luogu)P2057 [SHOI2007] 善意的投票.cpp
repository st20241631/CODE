#include <bits/stdc++.h>
#define int long long
const int MAX=1ll<<40;
using namespace std;
int n,m,s,t;
struct Node{
    int v,w,nex;
}a[10000000];
int cnt=1,first[5000000];
void add(int u,int v,int w){
    a[++cnt]=Node{v,w,first[u]};
    first[u]=cnt;
}
int now[10000000];//弧优化（去掉已经遍历的边）
int d[10000000];//层次（深度）（代替vis）
int bfs(){
    memset(d, false,sizeof d);
    queue<int> q;
    q.push(s);
    d[s]=1;
    now[s]=first[s];
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=first[u];i;i=a[i].nex){
            int v=a[i].v;
            if(a[i].w&&!d[v]){
                q.push(v);
                now[v]=first[v];
                d[v]=d[u]+1;
                if(v==t) return 1;
            }
        }
    }
    return 0;
}
int ans;
int dinic(int x,int val){
    if(x==t) return val;
    int have=val;
    for(int i=now[x];i&&have;i=a[i].nex){
        now[x]=i;
        int v=a[i].v;
        if(a[i].w&&d[v]==d[x]+1){
            int tmp= dinic(v,min(a[i].w,have));
            if(!tmp) d[v]=0;
            a[i].w-=tmp;
            a[i^1].w+=tmp;
            have-=tmp;
        }
    }
    return val-have;
}
main(){
    int n,m;
    cin>>n>>m;
    s=n*2+1,t=n*3+1;
    for(int i=1;i<=n;i++){
        int opt;
        cin>>opt;
        if(opt) add(s,i,1),add(i,s,0);
        else add(i,t,1), add(t,i,0);
    }
    for(int i=1;i<=m;i++){
        int x,y;
        cin>>x>>y;
        add(x,y,1),add(y,x,0);
        add(y,x,1),add(x,y,0);
    }
    int ans=0;
    while (bfs()){
        int tmp=0;
        while (tmp= dinic(s,MAX)) ans+=tmp;
    }
    cout<<ans;
}