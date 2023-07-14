#include <bits/stdc++.h>
using namespace std;
long long phi[10000005],a[10000005],k,n,sum[10000005];
bool f[10000005];
main() {
    cin>>n;
    phi[1]=1;
    long long ans=0;
    for(long long i=2; i<=n; i++) {
        if(f[i]==false)a[++k]=i,phi[i]=i-1;
        for(long long j=1; j<=k&&a[j]*i<=n; j++) {
            f[a[j]*i]=true;
            if(i%a[j]==0) {
                phi[i*a[j]]=phi[i]*a[j];
                break;
            }
            else phi[a[j]*i]=phi[i]*(a[j]-1);
        }
    }
    for(long long i=2;i<=n-1;i++){
        ans+=phi[i]*2;
    }
    if(n==1)cout<<0;
    else cout<<ans+3;

}