#include <bits/stdc++.h>
using namespace std;
const int N=1e5+3;

//part 1
struct node{
    int v,nex;
}a[N<<1];
int first[N],cnt;
void add(int u,int v){
    a[++cnt]=node{v,first[u]};
    first[u]=cnt;
}
int value[N];
int n,m;
//

//part 2
struct BIT{
    int SIZE;
    vector<int> G;
    int lowbit(int x){return x&(-x);}
    void clear(int MAX){SIZE=MAX;G.resize(MAX+1);}
    void add(int x,int val){x++;for(int i=x;i<=SIZE;i+= lowbit(i))G[i]+=val;}
    int query(int x){x++;x=min(x,SIZE);int sum=0;for(int i=x;i>=1;i-= lowbit(i))sum+=G[i];return sum;}
}T1[N],T2[N];
//

//part 3
int vis[N],rt,siz[N],dp[N];
int sum;
void getrt(int u,int fa){
    siz[u]=1;
    dp[u]=0;
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==fa||vis[v]) continue;
        getrt(v,u);
        siz[u]+=siz[v];
        dp[u]=max(dp[u],siz[v]);
    }
    dp[u]=max(dp[u],sum-siz[u]);
    if(dp[u]<dp[rt]) rt=u;
}

int tot[N];
int frt[N][20],fdis[N][20];
void getdis(int u,int fa,int rt,int dep){
    frt[u][++tot[u]]=rt;
    fdis[u][tot[u]]=dep;
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(vis[v]||v==fa) continue;
        getdis(v,u,rt,dep+1);
    }
}

void solve(int u){
    int now=sum;
    vis[u]=1;
    getdis(u,0,u,0);
    T1[u].clear(now/2+1);
    T2[u].clear(now+1);
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(vis[v]) continue;
        if(siz[v]>siz[u])sum=now-siz[u];    else sum=siz[v];
        rt=0;
        dp[rt]=0x3f3f3f3f;
        getrt(v,0);
        solve(rt);
    }
}

//


//part 4

int lastans;
void change(int x,int y){
    T1[x].add(0,y);
    for(int i=tot[x];i>=2;i--){
        int tmp=fdis[x][i-1];
        T1[frt[x][i-1]].add(tmp,y);
        T2[frt[x][i]].add(tmp,y);
    }
}
int ask(int x,int y){
    int ans=T1[x].query(y);
    for(int i=tot[x];i>=2;i--){
        int tmp=fdis[x][i-1];
        if(tmp>y) continue;
        ans+=T1[frt[x][i-1]].query(y-tmp);
        ans-=T2[frt[x][i]].query(y-tmp);
    }
    return ans;
}
//
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>value[i];
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        add(u,v),add(v,u);
    }
    rt=0;
    sum=n;
    dp[0]=0x3f3f3f3f;
    getrt(1,0);
    solve(rt);
    for(int i=1;i<=n;++i)change(i,value[i]);
    for(int i=1;i<=m;i++){
        int opt,x,y;
        cin>>opt>>x>>y;
        x^=lastans,y^=lastans;
        if(opt==1){
            change(x,y-value[x]);
            value[x]=y;
        }
        else{
            lastans= ask(x,y);
            cout<<lastans<<"\n";
        }
    }

}