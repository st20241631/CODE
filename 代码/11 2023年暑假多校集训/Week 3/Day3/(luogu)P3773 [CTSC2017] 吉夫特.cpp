#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int dp[1000000];
signed main(){
    int n;
    cin>>n;
    int ans=0;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        for(int j=(x-1)&x;j;j=(j-1)&x) dp[j]=(dp[j]+dp[x]+1)%mod;
        ans=(ans+dp[x])%mod;
    }
    cout<<ans%mod;
}