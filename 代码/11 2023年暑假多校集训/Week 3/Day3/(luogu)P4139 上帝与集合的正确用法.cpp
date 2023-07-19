#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e7+5;
int phi[N],prime[N],cnt;
bool flag[N];
void init(){
    for(int i=2;i<=N-5;i++){
        if(!flag[i])phi[i]=i-1,prime[++cnt]=i;
        for(int j=1;j<=cnt&&prime[j]*i<=N-5;j++){
            flag[i*prime[j]]=true;
            if(i%prime[j]==0){
                phi[i*prime[j]]=phi[i]*prime[j];
                break;
            }
            phi[i*prime[j]]=phi[i]*(prime[j]-1);
        }
    }
}
int qpow(int x,int y,int mod){
    int ans=1;
    while(y){
        if(y&1) ans=(ans*x)%mod;
        y>>=1;
        x=(x*x)%mod;
    }
    return ans%mod;
}
int calc(int p){
    if(p==1) return 0;
    return qpow(2,calc(phi[p])+phi[p],p);
}
void solve(){
    int p;
    cin>>p;
    cout<<calc(p)<<"\n";
}
signed main(){
    init();
    int t;
    cin>>t;
    while (t--)solve();
}