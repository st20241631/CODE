#include <bits/stdc++.h>

using namespace std;
const int mod=1000000007;
int qpow(int x,int y){
    int ans=1;
    while(y){
        if(y&1) ans=(long long)ans*x%mod;
        y>>=1;
        x=(long long)x*x%mod;
    }
    return ans%mod;
}
int p[5009];
int inv(int x){return qpow(x,mod-2)%mod;}
int dp[5009][5009][2];
void solve(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        int x,y;
        cin>>x>>y;
        p[i]=(long long)x*inv(y)%mod;
    }
    for(int i=0;i<=n;i++)cin>>dp[0][i][!i];
    for(int i=1;i<=n;i++){
        int ans=0;
        for(int j=0;j<=n;j++){
            dp[i][j][0]=dp[i][j][1]=0;
            for(int k=0;k<=1;k++){
                if(j>0){
                    dp[i][j][k|(!j)]=dp[i][j][k|(!j)]+(long long)dp[i-1][j-1][k]*(1-p[i]+mod)%mod;
                    dp[i][j][k|(!j)]%=mod;
                }
                if(j<n){
                    dp[i][j][k|(!j)]=dp[i][j][k|(!j)]+(long long)dp[i-1][j+1][k]*p[i]%mod;
                    dp[i][j][k|(!j)]%=mod;
                }
            }
            ans=ans+dp[i][j][1];
            ans%=mod;
        }
        cout<<ans<<" ";
    }
    cout<<"\n";
}
signed main(){
    int t;
    cin>>t;
    while(t--) solve();
}