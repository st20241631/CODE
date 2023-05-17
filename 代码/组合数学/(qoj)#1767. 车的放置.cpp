#include<bits/stdc++.h>
using namespace std;
const int N=2e3+5,mod=1e5+3;
int dp[N][N],high[N];
int main(){
    int a,b,c,d,k;
    cin>>a>>b>>c>>d>>k;
    dp[0][0]=1;
    for(int i=1;i<=c;i++){high[i]=d,dp[i][0]=1;}
    for(int i=1;i<=a;i++){high[c+i]=d+b,dp[c+i][0]=1;}
    for(int j=1;j<=a+c;j++)for(int i=1;i<=k;i++)dp[j][i]=(dp[j-1][i]+dp[j-1][i-1]*(high[j]-(i-1)))%mod;
    cout<<dp[a+c][k];
}
