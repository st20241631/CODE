#include <bits/stdc++.h>
#define int long long
const int mod=1e9+7;
using namespace std;
struct node{
    int v,nex,w;
}a[1000000];
int first[1000000],cnt;
void add(int u,int v,int w){
    a[++cnt]={v,first[u],w};
    first[u]=cnt;
}

struct node2{
    int id,val;
    bool operator<(const node2&b)const{
        return val>b.val;
    }
};
int dis[2][1000000];
int tot[2][1000000];
bool vis[1000000];
void dij(int id,int x){
    priority_queue<node2> q;
    memset(vis,false,sizeof vis);
    memset(dis[id],0x3f,sizeof dis[id]);
    dis[id][x]=0;
    tot[id][x]=1;
    q.push(node2{x,0});
    while (!q.empty()){
        node2 now=q.top();
        q.pop();
        int u=now.id;
        if(vis[u]) continue;
        vis[u]= true;
        for(int i=first[u];i;i=a[i].nex){
            int v=a[i].v;
            if(dis[id][u]+a[i].w<dis[id][v]){
                tot[id][v]=tot[id][u];
                dis[id][v]=dis[id][u]+a[i].w;
                q.push(node2{v,dis[id][v]});
            }
            else if(dis[id][u]+a[i].w==dis[id][v]){
                tot[id][v]=(tot[id][v]+tot[id][u])%mod;
            }
        }
    }

}
struct edge{
    int u,v,w;
}b[1000000];
signed main(){
    int n,m,s,t;
    cin>>n>>m>>s>>t;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        b[i].u=u,b[i].v=v,b[i].w=w;
        add(u,v,w);
        add(v,u,w);
    }
    dij(0,s);
    dij(1,t);
    int ans=(tot[0][t]*tot[1][s])%mod;
    for(int i=1;i<=n;i++){  //在第i个点相聚
        if(dis[0][i]+dis[1][i]==dis[0][t]&&dis[0][i]==dis[1][i]){
            int tmp=(tot[0][i]*tot[1][i])%mod;
            ans=(ans-tmp*tmp%mod+mod)%mod;
        }
    }
    for(int i=1;i<=m;i++){
        int u=b[i].u;
        int v=b[i].v;
        int w=b[i].w;
        if(dis[0][u]>dis[0][v]) swap(u,v);
        if(dis[0][u]+dis[1][v]+w==dis[0][t]&&dis[0][u]+w>dis[1][v]&&dis[1][v]+w>dis[0][u]){
            int tmp=(tot[0][u]*tot[1][v])%mod;
            ans=(ans-tmp*tmp%mod+mod)%mod;
        }
    }
    cout<<ans%mod;
}