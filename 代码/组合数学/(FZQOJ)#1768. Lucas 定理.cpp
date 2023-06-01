#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e7+5;
int jc[N];
int mod;
int qpow(int n,int m){
    int ans=1;
    while (m){
        if(m&1)ans=ans*n%mod;
        n=n*n%mod;
        m>>=1;
    }
    return ans%mod;
}
int c(int n,int m){
    if(n<m) return 0;
    int ans1=jc[n],ans2=jc[n-m]*jc[m]%mod;
    return ans1*qpow(ans2,mod-2)%mod;
}
int lucas(int n,int m){
    if(n<mod&&m<mod) return c(n,m)%mod;
    return lucas(n/mod,m/mod)%mod*c(n%mod,m%mod)%mod;
}
int read(){
    int x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while (ch>='0'&&ch<='9'){
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x;
}
signed main(){
    int t;
    t=read(),mod=read();
    jc[0]=1;
    for(int i=1;i<N;i++){jc[i]=jc[i-1]*i%mod;}
    while(t--){
        int n,m;
        n=read(),m=read();
        cout<<lucas(n+m-1,m-1)%mod<<"\n";
    }
}