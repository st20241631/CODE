#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=150000+10;
int x[N];
struct node{
    int v,nex,w;
} a[2*N];
int first[N],cnt;
void add(int u,int v,int w){
    a[++cnt]={v,first[u],w};
    first[u]=cnt;
}
struct node2{
    int val,s1,s2;
    bool operator<(const node2 &b) const{return val<b.val;}
};
vector<node2> ans[N][3];
struct node3{
    int id,dis,opt;
};
vector<node3> G[N];
int vis[N];
int dp[N],siz[N],rt;
void getrt(int u,int fa,int sum){
    siz[u]=1;
    dp[u]=0;
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==fa||vis[v])continue;
        getrt(v,u,sum);
        dp[u]=max(dp[u],siz[v]);
        siz[u]+=siz[v];
    }
    dp[u]=max(dp[u],sum-siz[u]);
    if(dp[rt]>dp[u])rt=u;
}
int dep[N];
void dfs(int u,int fa,int id,int opt){
    G[u].push_back({id,dep[u],opt});
    ans[id][opt].push_back({x[u],1,dep[u]});
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==fa||vis[v])continue;
        dep[v]=dep[u]+a[i].w;
        dfs(v,u,id,opt);
    }

}
void solve(int u){
    rt=0;
    dp[rt]=0x3f3f3f3f;
    getrt(u,0,siz[u]);
    if(siz[u]==1){
        vis[u]=true;
        G[u].push_back({u,0,-1});
        return;
    }
    vis[rt]=true;
    G[rt].push_back({rt,0,-1});
    int t=0;
    for(int i=first[rt];i;i=a[i].nex){
        int v=a[i].v;
        if(vis[v])continue;
        dep[v]=a[i].w;
        dfs(v,0,rt,t);
        ans[rt][t].push_back({0x3f3f3f3f,0,0});
        sort(ans[rt][t].begin(),ans[rt][t].end());
        for(int j=ans[rt][t].size()-2;j>=0;j--){
            ans[rt][t][j].s1+=ans[rt][t][j+1].s1;
            ans[rt][t][j].s2+=ans[rt][t][j+1].s2;
        }
        t++;
    }
    for(int i=first[rt];i;i=a[i].nex){
        int v=a[i].v;
        if(vis[v]!=0)continue;
        solve(v);
    }
}
int last;
int query(int l,int r,int u){
    int res=0;
    for(auto now:G[u]){
        int id=now.id;
        for(int opt=0;opt<=2;opt++){
            if(opt==now.opt||ans[id][opt].empty())continue;
            auto L=lower_bound(ans[id][opt].begin(),ans[id][opt].end(),(node2){l,0,0});
            auto R=upper_bound(ans[id][opt].begin(),ans[id][opt].end(),(node2){r,0,0});
            res+=now.dis*(L->s1-R->s1)+(L->s2-R->s2);
        }
        if(l<=x[id]&&x[id]<=r)res+=now.dis;
    }
    return res;
}
int n,m,A;
signed main(){
    cin>>n>>m>>A;
    for(int i=1;i<=n;i++)cin>>x[i];
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        add(u,v,w);
        add(v,u,w);
    }
    rt=0;
    dp[0]=0x3f3f3f3f;
    getrt(1,0,n);
    solve(rt);
    for(int i=1;i<=m;i++){
        int u,l,r;
        cin>>u>>l>>r;
        l=(l+last)%A;
        r=(r+last)%A;
        if(l>r)swap(l,r);
        last=query(l,r,u);
        cout<<last<<"\n";
    }
    return 0;
}