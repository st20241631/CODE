#include<bits/stdc++.h>
using namespace std;
const int N=502,M=N*N;
int n[1000000],m[1000000];
bitset<M> dp[N];
signed main(){
    int MAX=-1;
    int q;
    cin>>q;
    for(int i=1;i<=q;i++) {
        cin >> n[i] >> m[i];
        MAX = max(MAX, n[i]);
    }

    dp[0][0]=1;
    for(int i=1;i<=MAX;i++){
        for(int k=1;k<=i;k++){
            dp[i]|=dp[i-k]<<((i-k)*k);
        }
    }
    for(int i=1;i<=q;i++){
        cout<<dp[n[i]][m[i]]<<"\n";
    }
}