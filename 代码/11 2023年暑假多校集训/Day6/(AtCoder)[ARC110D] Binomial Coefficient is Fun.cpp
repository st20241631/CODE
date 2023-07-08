#include<bits/stdc++.h>
#define int long long
using namespace std;
int qpow(int a,int b,int mod){
    int ans=1;
    while(b){
        if(b&1)ans=(ans*a)%mod;
        b>>=1;
        a=(a*a)%mod;
    }
    return ans;
}
int C(int n,int m,int mod){
    if(m>n)return 0;
    if(m==n)return 1;
    if(m>n-m)m=n-m;
    int ans1=1,ans2=1;
    for(int i=0;i<m;i++){
        ans1=(ans1*(i+1))%mod;
        ans2=(ans2*(n-i))%mod;
    }
    return ans2*qpow(ans1,mod-2,mod)%mod;
}
signed main(){
    int n,m;
    cin>>n>>m;
    int sum=0;
    for(int i=1;i<=n;i++) {
        int x;
        cin>>x;
        sum+=x;
    }
    cout<<C(n+m,n+sum,1e9+7);
}