#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int mod=998244353,N=1e5+10;
int dp[N];
signed main(){
    dp[1]=1;
    for(int i=2;i<N;i++){
        for(int j=1;j*j<=i;j++){
            dp[i]+=dp[j];
        }
    }
    int t;
    cin>>t;
    while (t--){
        int x;
        cin>>x;
        int ans=0;
        int tmp= sqrt((long double) x);
        for(int i=1;i*i<=tmp;i++){
            ans+=(tmp-i*i+1)*dp[i];
        }
        cout<<ans<<"\n";
    }
}
