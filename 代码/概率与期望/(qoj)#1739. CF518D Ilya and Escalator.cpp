#include <bits/stdc++.h>
using namespace std;
double dp[2005][2005];
int main(){
    int n,t;
    double p;
    cin>>n>>p>>t;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=t;j++){
            dp[i][j]=(1-p)*dp[i][j-1]+p*(dp[i-1][j-1]+1);
        }
    }
    printf("%.4lf",dp[n][t]);
}