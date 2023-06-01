#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1e4+7;
const int N=1e6+10;
int jc[N],inv[N],po[N];
int qpow(int a,int b,int mod){
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
    po[0]=2;
    for(int i=1;i<N;i++)po[i]=po[i-1]*po[i-1]%mod;
}
int c(int n,int k){return jc[n]*inv[k]*inv[n-k]%mod;}
long long a,b,k,n,m;
main(){
    cin>>a>>b>>k>>n>>m;
    init();
    cout<<c(k,n)%mod*qpow(a,n,mod)%mod*qpow(b,k-n,mod)%mod;
}