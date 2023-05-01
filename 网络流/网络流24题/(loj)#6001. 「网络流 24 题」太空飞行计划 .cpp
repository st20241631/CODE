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
void insert(int u,int v,int w){
    add(u,v,w), add(v,u,0);
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
int Dinic(){
    int ans=0,tmp;
    while (bfs()){
        while (tmp=dinic(s,MAX)) ans+=tmp;
    }
    return ans;
}

main(){
    int cost=0;
    int m,n;
    cin>>m>>n;
    s=m+n+1,t=s+1;
    for(int i=1;i<=m;i++){
        int x;
        cin>>x;
        cost+=x;
        insert(s,i,x);
        while (getchar()==' '){
            cin>>x;
            insert(i,m+x,MAX);
        }
    }
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        insert(i+m,t,x);
    }
    int ans=Dinic();
    for(int i=1;i<=m;i++)if (d[i])cout<<i<<" ";
    cout<<"\n";
    for(int i=1;i<=n;i++)if (d[i+m])cout<<i<<" ";
    cout<<"\n";
    cout<<cost-ans;
}