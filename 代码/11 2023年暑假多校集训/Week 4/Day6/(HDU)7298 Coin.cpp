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
int now[100000];
int d[100000];
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
int x[1000000];
int tot;
void init(){
    s=0;
    cnt=1;
    memset(first,0, sizeof first);
    tot=0;
}
int id[1000000];
void solve(){
    init();
    int n,m,k;
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++) cin>>x[i];
    for(int i=1;i<=n;i++){
        id[i]=++tot;
        add(s,id[i],1);
        add(id[i],s,0);
    }
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        add(id[u],id[v],1), add(id[v],id[u],0);
        add(id[v],id[u],1), add(id[u],id[v],0);
        tot++;
        add(id[u],tot,x[u]), add(tot,id[u],0);
        id[u]=tot;
        tot++;
        add(id[v],tot,x[v]), add(tot,id[v],0);
        id[v]=tot;
    }
    tot+=10;
    t=tot;
    for(int i=1;i<=k;i++){
        int u;
        cin>>u;
        add(id[u],t,x[u]);
        add(t,id[u],0);
    }

    int ans=0;
    while (bfs()){
        int tmp;
        while (tmp= dinic(s,MAX)) ans+=tmp;
    }
    cout<<ans<<"\n";
}
signed main(){
    int T;
    cin>>T;
    while (T--) solve();
}