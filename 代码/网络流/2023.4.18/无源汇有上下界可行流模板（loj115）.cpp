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
int d[100000];//层次（深度）（代替vis）
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
int solve(){
    int ans=0;
    int tmp;
    while(bfs()){
        while(tmp=dinic(s,MAX)) ans+=tmp;
    }
    return ans;
}
int id[1000000];
int flow[1000000];//入度减出度
int lower[1000000];
main(){
    int n,m;
    cin>>n>>m;
    s=n+1,t=n+2;
    for(int i=1;i<=m;i++){
        int u,v,upper;
        cin>>u>>v>>lower[i]>>upper;
        add(u,v,upper-lower[i]),add(v,u,0);
        id[i]=cnt;
        flow[v]+=lower[i],flow[u]-=lower[i];
    }
    int sum=0;
    for(int i=1;i<=n;i++){
        if(flow[i]<0) add(i,t,-flow[i]),add(t,i,0);
        else add(s,i,flow[i]),add(i,s,0),sum+=flow[i];
    }
    int ans=solve();
    if(sum!=ans){puts("NO");return 0;}
    puts("YES");
    solve();
    for(int i=1;i<=m;i++){
        cout<<lower[i]+a[id[i]].w<<"\n";
    }
}