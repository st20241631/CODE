#include <bits/stdc++.h>
using namespace std;
const int MAX=1<<30;
int n,m,s,t;
struct Node{
    int v,w,nex,val;
}a[100000];
int cnt=1,first[50000];
void add(int u,int v,int w,int val){
    a[++cnt]=Node{v,w,first[u],val};
    first[u]=cnt;
}
int val[100000];
int dis[1000000];
bool vis[100000];
int pre[100000];
int spfa(){
    memset(vis, false,sizeof vis);
    memset(dis,0x3f,sizeof dis);
    queue<int> q;
    q.push(s);
    dis[s]=0;
    vis[s]= true;
    val[s]=MAX;
    while(!q.empty()){
        int now=q.front();
        q.pop();
        vis[now]=false;
        for(int i=first[now];i;i=a[i].nex){
            if(a[i].w){
                int v=a[i].v;
                if(dis[v]>dis[now]+a[i].val){
                    dis[v]=dis[now]+a[i].val;
                    pre[v]=i;
                    val[v]=min(val[now],a[i].w);
                    if(!vis[v]) q.push(v),vis[v]=true;
                }
            }
        }
    }
    if(dis[t]==0x3f3f3f3f)return 0;
    return 1;
}
int ans1,ans2;
void update(){
    int x=t;
    ans1+=val[t];
    ans2+=val[t]*dis[t];
    while(x != s){
        int i=pre[x];
        a[i].w-=val[t];
        a[i^1].w+=val[t];
        x=a[i ^ 1].v;
    }
}
main(){
    cin>>n>>m>>s>>t;
    for(int i=1;i<=m;i++){
        int u,v,w,c;
        cin>>u>>v>>w>>c;
        add(u,v,w,c);
        add(v,u,0,-c);
    }
    while(spfa())update();
    cout<<ans1<<" "<<ans2;

}