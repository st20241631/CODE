#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+7;
int ans[N];
signed main(){
    ans[1]=ans[2]=0;
    for(int i=3;i<N;i++){
        ans[i]=ans[i-1]+(i-2)*(i-2)/4;
    }
    int n;
    cin>>n;
    while(n>=3){
        cout<<ans[n]<<"\n";
        cin>>n;
    }
}