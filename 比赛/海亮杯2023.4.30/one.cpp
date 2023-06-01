#include <bits/stdc++.h>
using namespace std;
int n;
int a[10000000];
int MAX[10000000];
main(){
    freopen("one.in","r",stdin);
    freopen("one.out","w",stdout);
    cin>>n;
    for(int i=1;i<=n;i++) {
        cin>>a[i];
    }
    for(int i=n;i>=1;i--){
        MAX[i]=max(MAX[i+1],a[i]);
    }
    int ans=1e9;
    int Max=0,Min=1e9;
    for(int i=1;i<=n;i++){
        Max=max(Max,a[i]);
        Min=min(Min,a[i]);
        if(Min!=0)ans=min(ans,max(Max-Min,MAX[i+1]));
        else{
            ans=min(ans,max(Max,MAX[i+1]));
        }
    }
    cout<<ans;

}