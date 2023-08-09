#include<bits/stdc++.h>
#define int long long
using namespace std;
int prime[10000000],tot;
void solve(){
    tot=0;
    int p,q,edata;
    cin>>p>>q>>edata;
    int x=p*q-1;

    for(int i=2;i*i<=x;i++){
        if(x%i==0){
            int sum=0;
            while(x%i==0) x/=i;
            prime[++tot]=i;
        }
    }
    if(x>1) prime[++tot]=x;

    int flag=0;
    int ans=0;
    for(int i=1;i<=tot;i++){
        if(p>=prime[i]||q>=prime[i]||edata>=prime[i]) continue;
        int rdata=edata*q%prime[i];
        int tmp=rdata*p%prime[i];
        if(tmp==edata) flag++,ans=prime[i];
    }
    if(flag==1){
        cout<<edata*q%ans<<"\n";
    }
    else puts("shuanQ");

}
signed main(){
    int t;
    cin>>t;
    while(t--) solve();
    return 0;
}