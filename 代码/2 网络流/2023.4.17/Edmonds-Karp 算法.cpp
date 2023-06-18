#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAX=pow(2,40);
int n,m,s,t;
struct Node{
    int v,w,nex;
}a[100000];
int cnt=1,first[50000];
void add(int u,int v,int w){
    a[++cnt]=Node{v,w,first[u]};
    first[u]=cnt;
}
int val[100000];
bool vis[100000];
int pre[100000];
int bfs(){
    memset(vis, false,sizeof vis);
    queue<int> q;
    q.push(s);
    vis[s]= true;
    val[s]=MAX;
    while(!q.empty()){
        int now=q.front();
        q.pop();
        for(int i=first[now];i;i=a[i].nex){
            if(a[i].w){
                int v=a[i].v;
                if(vis[v]) continue;
                q.push(v);
                vis[v]=true;
                val[v]=min(a[i].w,val[now]);
                pre[v]=i;
                if(v==t) return 1;
            }
        }
    }
    return 0;
}
int ans;
void update(){
    int x=t;
    ans+=val[t];
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
        int u,v,w;
        cin>>u>>v>>w;
        add(u,v,w);
        add(v,u,0);
    }
    while(bfs())update();
    cout<<ans;

}