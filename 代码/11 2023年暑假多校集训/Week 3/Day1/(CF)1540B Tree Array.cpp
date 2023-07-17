#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
struct node{
    int v,nex;
}a[100000];
int first[10000],cnt;
void add(int u,int v){
    a[++cnt]={v,first[u]};
    first[u]=cnt;
}
int dep[1000000];
int fa[100000][20];
void dfs(int u,int dad){
    fa[u][0]=dad;
    dep[u]=dep[dad]+1;
    for(int i=1;i<20;i++) fa[u][i]=fa[fa[u][i-1]][i-1];
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==dad) continue;
        dfs(v,u);
    }
}
int lca(int x,int y){
    if(dep[x]<=dep[y]) swap(x,y);
    for(int i=19;i>=0;i--){
        if(dep[fa[x][i]]>=dep[y]) x=fa[x][i];
    }
    if(x==y) return x;
    for(int i=19;i>=0;i--){
        if(fa[x][i]!=fa[y][i]){
            x=fa[x][i];
            y=fa[y][i];
        }
    }
    return fa[x][0];
}

int qpow(int x,int y){
    int ans=1;
    while (y){
        if(y&1) ans=ans*x%mod;
        y>>=1;
        x=x*x%mod;
    }
    return ans%mod;
}
int inv(int x){
    return qpow(x,mod-2)%mod;
}
int dp[1005][1005];
signed main(){
    int n;
    cin>>n;
    for(int i=1;i<n;i++){
        int x,y;
        cin>>x>>y;
        add(x,y);
        add(y,x);
    }
    for(int i=1;i<=n;i++)dp[0][i]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            dp[i][j]=(dp[i-1][j]%mod+dp[i][j-1]%mod)*inv(2)%mod;
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        dfs(i,0);
        for(int j=1;j<=n;j++){
            for(int k=1;k<j;k++){
                int LCA=lca(j,k);
                ans=(ans+dp[dep[j]-dep[LCA]][dep[k]-dep[LCA]]%mod)%mod;
            }
        }
    }
    cout<<ans*inv(n)%mod;
}