#include <bits/stdc++.h>
#define int long long
using namespace std;
int phi(int x){
    int sum=x;
    for(int i=2;i*i<=x;i++){
        if(x%i==0){
            sum=sum/i*(i-1);
            while (x%i==0) x/=i;
        }
    }
    if(x>1) sum=sum/x*(x-1);
    return sum;
}
signed main(){
    int n;
    cin>>n;
    int ans=0;
    for(int i=1;i<=n;i++)ans+=phi(i)*(n/i)*(n/i);
    cout<<ans;
}