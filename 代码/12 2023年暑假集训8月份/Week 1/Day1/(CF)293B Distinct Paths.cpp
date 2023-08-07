#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int dp[45][45];
int vis[45];
int col[45][45];
int n,m,k;
int dfs(int x,int y){
    if(y>m)x++,y=1;
    if(x>n)return 1;
    int now=dp[x-1][y]|dp[x][y-1];
    int cnt=0;
    for(int i=0;i<k;i++)if(!((now>>i)&1)) cnt++;
    if(cnt<(n-x)+(m-y)+1) return 0;
    int ans=0;
    int last=-1;
    for(int i=1;i<=k;i++){
        if(col[x][y]&&col[x][y]!=i) continue;
        if((now>>(i-1))&1) continue;
        dp[x][y]=now|(1<<(i-1));
        if(!vis[i]){
            vis[i]=1;
            if(last==-1)last= dfs(x,y+1);
            ans=(ans+last)%mod;
            vis[i]=0;
        }
        else ans=(ans+ dfs(x,y+1))%mod;
    }
    return ans;
}
signed main(){
    cin>>n>>m>>k;
    if(n+m-1>k) {
        puts("0");
        return 0;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>col[i][j];
            vis[col[i][j]]=1;
        }
    }
    cout<<dfs(1,1);
    return 0;
}