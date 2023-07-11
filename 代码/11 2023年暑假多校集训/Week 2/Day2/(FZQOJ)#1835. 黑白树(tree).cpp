#include <bits/stdc++.h>

#define int long long
using namespace std;
const int N=1e6+10;
const int mod=1e9+7;

int qpow(int x,int y){
    int ans=1;
    while(y){
        if(y&1) ans=(ans*x)%mod;
        y>>=1;
        x=(x*x)%mod;
    }
    return ans%mod;
}

struct node{
    int v,nex;
} a[N*2];
int first[N],cnt;

void add(int u,int v){
    a[++cnt]={v,first[u]};
    first[u]=cnt;
}

int dep[N];

void dfs(int u,int dad){
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==dad) continue;
        dep[v]=dep[u]+1;
        dfs(v,u);
    }
}

bool vis[N];

signed main(){
    int n;
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        add(u,v);
        add(v,u);
    }
    int x=0,y=0;    //直径的两端
    dep[1]=0;
    dfs(1,0);
    for(int i=1;i<=n;i++){
        if(dep[i]>dep[x]) x=i;
    }
    dep[x]=0;
    dfs(x,0);
    for(int i=1;i<=n;i++){
        if(dep[i]>dep[y]) y=i;
    }

    int ans=(dep[y]*qpow(2,n-1))%mod;
    priority_queue<pair<int,int> > q;
    for(int i=1;i<=n;i++)if(i!=x&&i!=y)q.push({dep[i],i});
    dep[y]=0;
    dfs(y,0);
    for(int i=1;i<=n;i++)if(i!=x&&i!=y)q.push({dep[i],i});
    int tot=2;
    while(!q.empty()){
        auto now=q.top();
        q.pop();
        if(!vis[now.second]){
            vis[now.second]=true;
            ans=(ans+qpow(2,n-tot)*(now.first)%mod)%mod;
            tot++;
        }else{
            ans=(ans+qpow(2,n-tot+1)*(now.first)%mod)%mod;
            break;
        }

    }
    cout<<ans;


}