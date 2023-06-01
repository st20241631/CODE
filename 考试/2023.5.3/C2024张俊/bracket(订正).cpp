#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int n,l[1000],r[1000],dp[1000][2000];
int dfs(int now,int len){
    if(dp[now][len]>=0) return dp[now][len];
    if(len==0)return 1;
    if (len==2)return l[now]<=1&&r[now]>=1;
    dp[now][len]=0;
    for(int i=l[now];i<=r[now];i++){
        if((i&1)){
            if(i>=len) break;
            dp[now][len]=(dp[now][len]+dfs(now+1,i-1)*dfs(now+(i+1)/2,len-i-1))%mod;
        }
    }
    return dp[now][len]%mod;
}
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>l[i]>>r[i];
    memset(dp,-1,sizeof dp);
    cout<<dfs(1,2*n);
}