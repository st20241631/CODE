#include <bits/stdc++.h>
#define int long long
using namespace std;
int mod;
int A(int n,int m){
    int ans=1;
    for(int i=1;i<=m;i++){
        ans=ans*(n-i+1)%mod;
    }
    return ans;
}
signed main(){
    int n,m;
    cin>>n>>n>>m>>mod;
    cout<<A(n-m+1,m);

}