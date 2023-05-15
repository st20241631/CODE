#include<bits/stdc++.h>
using namespace std;
#define int long long
int m,n;
const int mod=100003;
int qpow(int a,int b){
    int ans=1;
    while(b){
        if(b&1)ans=(ans*a)%mod;
        b>>=1;
        a=(a*a)%mod;
    }
    return ans%mod;
}
main(){
    cin>>m>>n;
    m%=mod;
    cout<<(qpow(m,n)%mod-m*qpow(m-1,n-1)%mod+mod)%mod;

}