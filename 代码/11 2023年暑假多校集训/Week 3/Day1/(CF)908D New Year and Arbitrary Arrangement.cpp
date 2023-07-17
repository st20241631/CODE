#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int qpow(int x,int y){
    int ans=1;
    while(y){
        if(y&1)ans=ans*x%mod;
        y>>=1;
        x=x*x%mod;
    }
    return ans%mod;
}
int inv(int x){
    return qpow(x,mod-2);
}
int dp[1005][1005];
signed main(){
    int n,pa,pb;
    cin>>n>>pa>>pb;
    int A=pa*inv(pa+pb)%mod;
    int B=pb*inv(pa+pb)%mod;
    int C=pa*inv(pb)%mod;
    for(int i=n;i>=1;i--){
        for(int j=n;j>=0;j--){
            if (i+j>=n) dp[i][j]=(C+i+j)%mod;
            else dp[i][j]=(A*dp[i+1][j]%mod+B*dp[i][j+i]%mod)%mod;
        }
    }
    cout<<dp[1][0]%mod;
}