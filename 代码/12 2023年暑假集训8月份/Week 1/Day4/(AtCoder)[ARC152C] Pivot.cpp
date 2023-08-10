#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[1000000];
signed main(){
    int n;
    cin>>n;
    int d=-1;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++){
        int tmp=llabs(a[1]+a[n]-2*a[i]);
        if(tmp!=0){
            if(d==-1) d=tmp;
            else d=__gcd(d,tmp);
        }
    }
    cout<<a[1]%d+a[n]-a[1];
}