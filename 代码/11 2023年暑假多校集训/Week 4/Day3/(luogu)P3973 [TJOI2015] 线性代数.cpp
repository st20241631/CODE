#include <bits/stdc++.h>
#define int long long
const int MAX=1ll<<40;
using namespace std;
int s,t;
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
signed main(){
    int n;
    cin>>n;
    s=n*n*2+1;t=s+1;
    int sum=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            int x;
            cin>>x;
            sum+=x;
            add(s,(i-1)*n+j,x);
            add((i-1)*n+j,s,0);
        }
    }
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        add(n*n+i,t,x);
        add(t,n*n+i,0);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            int tmp=(i-1)*n+j;
            add(tmp,n*n+i,MAX-10), add(n*n+i,tmp,0);
            add(tmp,n*n+j,MAX-10),add(n*n+j,tmp,0);
        }
    }
    int ans=0;
    while (bfs()){
        int tmp;
        while (tmp= dinic(s,MAX)) ans+=tmp;
    }
    cout<<sum-ans;

}