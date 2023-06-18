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
int need[1000000];
//1~n:上午,n+1~2n:下午
main(){
    int n;
    cin>>n;
    int p,d1,w1,d2,w2;
    cin>>p>>d1>>w1>>d2>>w2;
    for(int i=1;i<=n;i++)cin>>need[i];
    s=n*2+1,t=n*2+2;
    for(int i=1;i<=n;i++){
        add(s,i,MAX,p);add(i,s,0,-p);
        add(i,t,need[i],0);add(t,i,0,0);
        add(s,i+n,need[i],0);add(i+n,s,0,0);
        if(i+d1<=n)add(i+n,i+d1,MAX,w1),add(i+d1,i+n,0,-w1);
        if(i+d2<=n)add(i+n,i+d2,MAX,w2),add(i+d2,i+n,0,-w2);
        if(i+1<=n)add(i+n,i+n+1,MAX,0),add(i+n+1,i+n,0,0);
    }
    while(spfa()){
        int tmp;
        while(tmp=dinic(s,MAX)) ans+=tmp*dis[t];
    }
    cout<<ans;

}