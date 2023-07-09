#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1e9+7;
const int N=1e6+10;
int jc[N],inv[N];
int qpow(int a,int b){
    int ans=1;
    while(b){
        if(b&1)ans=(ans%mod*a%mod)%mod;
        b>>=1;
        a=(a%mod*a%mod)%mod;
    }
    return ans%mod;
}
void init(){
    jc[0]=inv[0]=inv[1]=1;
    for(int i=1;i<N;i++)jc[i]=jc[i-1]*i%mod;
    for(int i=2;i<N;i++)inv[i]=(mod-mod/i)*inv[mod%i]%mod;
    for(int i=1;i<N;i++)inv[i]=inv[i-1]*inv[i]%mod;
}
int c(int n,int k){return jc[n]*inv[k]%mod*inv[n-k]%mod;}
int dp[5000][5000];
int a[N],b[N];
const int S=2050;
signed main(){
    init();
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i]>>b[i];
        dp[S-a[i]][S-b[i]]++;
    }
    for(int i=1;i<=S*2;i++){
        for(int j=1;j<=S*2;j++){
            dp[i][j]=(dp[i][j]+(dp[i-1][j]+dp[i][j-1])%mod)%mod;
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        ans=(ans+dp[S+a[i]][S+b[i]])%mod;
        ans=(ans-c(2*a[i]+2*b[i],2*a[i])%mod+mod)%mod;
    }
    ans=(ans*500000004)%mod;  //inv2=500000004
    cout<<ans;
    return 0;

}