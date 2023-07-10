#include <bits/stdc++.h>
#define int long long
using namespace std;
int dp[1000000];
int t[10000000];
int num[1000000],cost[1000000];
int last[1000000];
signed main(){
    int n,k;
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>t[i];
    for(int i=1;i<=k;i++){
        cin>>num[i]>>cost[i];
        last[i]=1;
    }
    int one;
    cin>>one;
    for(int i=0;i<1000000;i++) dp[i]=LLONG_MAX;
    dp[0]=0;
    for(int i=1;i<=n;i++){
        dp[i]=dp[i-1]+one;
        for(int j=1;j<=k;j++){
            while(t[i]-t[last[j]]+1>num[j]) last[j]++;
            dp[i]=min(dp[i],dp[last[j]-1]+cost[j]);
        }
        cout<<dp[i]-dp[i-1]<<"\n";
    }

}