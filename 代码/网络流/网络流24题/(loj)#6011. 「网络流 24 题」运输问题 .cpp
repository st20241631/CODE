#include <bits/stdc++.h>
const int MAX=1<<30;
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
void insert(int u,int v,int w,int val){
    add(u,v,w,val),add(v,u,0,-val);
}

bool vis[1000000];
int now[1000000];
int dis[1000000];
int spfa(){
    memset(dis,0x3f,sizeof dis);
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
    if(dis[t]==0x3f3f3f3f)return 0;
    return 1;
}
int ans1,ans2;
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
int Dinic(){
    int sum=0,tmp;
    while(spfa()){
        while (tmp= dinic(s,MAX)) sum+=tmp*dis[t];
    }
    return sum;
}
int pay1[1000000],pay2[1000000];
int pay3[200][200];
main(){
    int m,n;
    cin>>m>>n;
    s=n+m+1,t=s+1;
    for(int i=1;i<=m;i++) {
        cin >> pay1[i];
        insert(s,i,pay1[i],0);
    }
    for(int i=1;i<=n;i++) {
        cin >> pay2[i];
        insert(i+m,t,pay2[i],0);
    }
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            cin>>pay3[i][j];
            insert(i,j+m,pay2[j],pay3[i][j]);
        }
    }
    cout<<Dinic()<<"\n";
    cnt=1;
    memset(first,0,sizeof first);
    for(int i=1;i<=m;i++) {
        insert(s,i,pay1[i],0);
    }
    for(int i=1;i<=n;i++) {
        insert(i+m,t,pay2[i],0);
    }
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            insert(i,j+m,pay2[j],-pay3[i][j]);
        }
    }
    cout<<-Dinic();

}