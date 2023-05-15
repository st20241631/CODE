#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int qpow(int a,int b){
    int ans=1;
    while (b){
        if(b&1) ans=ans*a%mod;
        b>>=1;
        a=a*a%mod;
    }
    return ans%mod;
}
signed main(){
    int n,k;
    cin>>n>>k;
    cout<<qpow(2,n*k);
}