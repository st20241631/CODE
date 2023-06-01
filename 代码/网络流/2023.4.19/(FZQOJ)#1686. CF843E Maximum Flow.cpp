#include <bits/stdc++.h>
#define int long long
const int MAX=1ll<<40;
using namespace std;
int s,t;
struct Node{
    int v,w,nex;
}a[100000];
int cnt=1,first[50000];
void add(int u,int v,int w){
    a[++cnt]=Node{v,w,first[u]};
    first[u]=cnt;
}
int now[100000];//弧优化（去掉已经遍历的边）
int dis[100000];//层次（深度）（代替vis）
int bfs(){
    memset(dis, false,sizeof dis);
    queue<int> q;
    q.push(s);
    dis[s]=1;
    now[s]=first[s];
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=first[u];i;i=a[i].nex){
            int v=a[i].v;
            if(a[i].w&&!dis[v]){
                q.push(v);
                now[v]=first[v];
                dis[v]=dis[u]+1;
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
        if(a[i].w&&dis[v]==dis[x]+1){
            int tmp= dinic(v,min(a[i].w,have));
            if(!tmp) dis[v]=0;
            a[i].w-=tmp;
            a[i^1].w+=tmp;
            have-=tmp;
        }
    }
    return val-have;
}
int solve(){
    int ans=0;
    int tmp;
    while(bfs()){
        while(tmp=dinic(s,MAX)) ans+=tmp;
    }
    return ans;
}
struct edge{
    int u,v,g;
}b[1000000];
int d[1000000];//入度减出度
int f[1000000];
main(){
    int n,m,_s,_t;
    cin>>n>>m>>_s>>_t;
    s=_s,t=_t;
    for(int i=1;i<=m;i++){
        cin>>b[i].u>>b[i].v>>b[i].g;
        if(b[i].g)add(b[i].v,b[i].u,MAX),add(b[i].u,b[i].v,0);
        add(b[i].u,b[i].v,b[i].g?1:MAX),add(b[i].v,b[i].u,0);
        d[b[i].v]++,d[b[i].u]--;
    }
    cout<<solve()<<"\n";

    for(int i=1;i<=m;i++){
        if(b[i].g){
            if(dis[b[i].u]&&!dis[b[i].v]) f[i]=1;
        }
    }

    cnt=1;
    for(int i=0;i<=n+1;i++)first[i]=0;

    s=0,t=n+1;
    for(int i=1;i<=m;i++)if(b[i].g)add(b[i].u,b[i].v,MAX),add(b[i].v,b[i].u,0);
    add(t,s,MAX),add(s,t,0);
    for(int i=1;i<=n;i++){
        if(d[i]<0) add(i,t,-d[i]),add(t,i,0);
        else add(s,i,d[i]),add(i,s,0);
    }
    solve();
    int sum=0;
    for(int i=1;i<=m;i++){
        if(!b[i].g)puts("0 1");
        else{
            sum++,cout<<a[sum<<1|1].w+1<<" "<<a[sum<<1|1].w+(!f[i])+1<<"\n";
        }

    }
}