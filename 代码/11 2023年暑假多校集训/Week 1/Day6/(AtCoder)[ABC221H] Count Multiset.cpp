#include <bits/stdc++.h>
#define int long long
using namespace std;
int dp[5005][5005];
const int mod=998244353;
signed main(){
    int n,m;
    cin>>n>>m;
    dp[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=i;j++){
            dp[i][j]=(dp[i][j]+dp[i-1][j-1]+dp[i-j][j])%mod;
            if(j>=m+1) dp[i][j]=(dp[i][j]-dp[i-j][j-(m+1)]+mod)%mod;
        }
    }
    for(int i=1;i<=n;i++) cout<<dp[n][i]%mod<<"\n";
}