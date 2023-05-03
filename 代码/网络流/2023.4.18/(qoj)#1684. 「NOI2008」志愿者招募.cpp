#include <bits/stdc++.h>
#define int long long
const int MAX=1ll<<50;
using namespace std;
int s,t;
struct Node{
    int v,w,nex,val;
}a[1000000];
int cnt=1,first[1000000];
void add(int u,int v,int w,int val){
    a[++cnt]=Node{v,w,first[u],val};
    first[u]=cnt;
}
bool vis[1000000];
int now[1000000];
int dis[1000000];
int spfa(){
    for(int i=0;i<1000000;i++)dis[i]=0x7fffffffff;
    queue<int> q;
    q.push(s);
    dis[s]=0;
    vis[s]= true;
    now[s]=first[s];
    while(!q.empty()){
        int u=q.front();
        q.pop();
        vis[u]=false;
        for(int i=first[u];i;i=a[i].nex){
            if(a[i].w){
                int v=a[i].v;
                if(dis[v]>dis[u]+a[i].val){
                    now[v]=first[v];
                    dis[v]=dis[u]+a[i].val;
                    if(!vis[v]) q.push(v),vis[v]=true;
                }
            }
        }
    }
    if(dis[t]==0x7fffffffff)return 0;
    return 1;
}
int dinic(int x,int val){
    if(x==t) return val;
    int have=val;
    vis[x]=true;
    for(int i=now[x];i&&have;i=a[i].nex){
        now[x]=i;
        int v=a[i].v;
        if(!vis[v]&&a[i].w&&dis[v]==dis[x]+a[i].val){
            int tmp= dinic(v,min(a[i].w,have));
            if(!tmp) dis[v]=0;
            a[i].w-=tmp;
            a[i^1].w+=tmp;
            have-=tmp;
        }
    }
    vis[x]=false;
    return val-have;
}

int ans;
main(){
    int n,m;
    cin>>n>>m;
    s=0,t=n+2;
    add(s,1,MAX,0),add(1,s,0,0);
    add(n+1,t,MAX,0),add(t,n+1,0,0);
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        add(i,i+1,MAX-x,0),add(i+1,i,0,0);
    }
    for(int i=1;i<=m;i++){
        int x,y,z;
        cin>>x>>y>>z;
        add(x,y+1,MAX,z),add(y+1,x,0,-z);
    }
    while(spfa()){
        int tmp;
        while(tmp=dinic(s,MAX)) ans+=tmp*dis[t];
    }
    cout<<ans;

}