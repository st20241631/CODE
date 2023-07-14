#include <bits/stdc++.h>
using namespace std;
long long exgcd(long long a,long long b,long long &x,long long &y){
    if(b==0){
        x=1,y=0;
        return a;
    }
    long long g=exgcd(b,a%b,y,x);
    y-=a/b*x;
    return g;
}
long long a[1000000],m[1000000],n;
long long mul(long long a,long long b,long long mod){
    long long ans=0;
    while(b){
        if(b&1)ans=(ans+a)%mod;
        b>>=1;
        a=(a+a)%mod;
    }
    return ans;
}
long long crt(){
    long long ans=0,M=1;
    for(long long i=1;i<=n;i++)M*=m[i];
    for(long long i=1;i<=n;i++){
        long long Mi=M/m[i],x,y;
        exgcd(Mi,m[i],x,y);
        x=(x%m[i]+m[i])%m[i];
        ans=(ans%M+mul(a[i]*Mi%M,x,M)%M)%M;
    }
    return (ans%M+M)%M;
}
int main(){
    cin>>n;
    for(long long i=1;i<=n;i++)cin>>m[i]>>a[i];
    cout<<crt();
}