#include <bits/stdc++.h>
using namespace std;
#define int long long
int qpow(int x,int y,int mod){
    int ans=1;
    while (y){
        if(y&1) ans=(ans*x)%mod;
        y>>=1;
        x=x*x%mod;
    }
    return ans%mod;
}
int inv(int x,int mod){
    return qpow(x,mod-2,mod)%mod;
}

int bsgs(int a,int b,int mod){  //a^x≡b % mod
    unordered_map<int,int> mp;
    if(a%mod==0) return -1;
    int m= ceil(sqrt(mod));
    int k=b%mod;
    mp[k]=0;
    for(int i=1;i<=m;i++){
        k=k*a%mod;
        mp[k]=i;
    }
    k=qpow(a,m,mod);
    int now=1;
    for(int i=1;i<=m;i++){
        now=now*k%mod;
        if(mp[now]){
            int ans=i*m-mp[now];
            return (ans%mod+mod)%mod;
        }
    }
    return -1;
}
void solve(){
    int mod,a,b,x1,t;
    cin>>mod>>a>>b>>x1>>t;
    if(t==x1){puts("1");return;}
    if(a==0){if(t==b){puts("2");return;}else {puts("-1");return;}}
    if(a==1){
        t=((t-x1)%mod+mod)%mod;
        if(t%__gcd(b,mod)){
            puts("-1");
            return;
        }
        else{
            if((t*inv(b,mod)+1)%mod==0)cout<<mod<<"\n";
            else cout<<(t*inv(b,mod)+1)%mod<<"\n";
            return;
        }
    }
    int ans=bsgs(a,(t-b*inv(1-a,mod)%mod)%mod*inv((x1-b*inv(1-a,mod)%mod)%mod,mod),mod);
    if(ans==-1)puts("-1");
    else cout<<ans+1<<"\n";
}
signed main(){
    int t;
    cin>>t;
    while (t--)solve();
}