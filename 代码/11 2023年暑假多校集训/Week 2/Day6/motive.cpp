#include <bits/stdc++.h>
#define int long long
using namespace std;
int a[10000000];
int ksm(int x,int y,int mod){
    int ans=1;
    while (y){
        if(y&1) ans=(ans*x)%mod;
        y>>=1;
        x=(x*x)%mod;
    }
    return ans%mod;
}
int inv(int x,int mod){
    return ksm(x,mod-2,mod)%mod;
}
signed main(){
    freopen("motive.in","r",stdin);
    freopen("motive.out","w",stdout);
    int n,k;
    cin>>n>>k;
    for(int i=1;i<=n;i++)cin>>a[i];
    int sum1=0,cnt1=0;
    for(int l=1;l<=n-2;l++){
        int sum2=0;
        int cnt2=2;
        sum2=a[l]+a[l+1];
        int MAX=max(LLONG_MIN,a[l]);
        MAX=max(MAX,a[l+1]);

        int MIN=min(LLONG_MAX,a[l]);
        MIN=min(MIN,a[l+1]);
        for(int r=l+2;r<=n;r++){
            MAX=max(MAX,a[r]);
            MIN=min(MIN,a[r]);
            sum2+=a[r];
            cnt2++;
            int tmp=(sum2-MAX-MIN)%k*inv(cnt2-2,k)%k;
            sum1=(sum1+tmp)%k;
            cnt1++;
        }
    }
    cout<<(sum1*inv(cnt1,k)%k);
}