#include <bits/stdc++.h>
using namespace std;

int c[10000000];
double C[105][105];
double dp[105][10005];
int main(){
    int n,x;
    cin>>n>>x;
    for(int i=1;i<=n;i++){cin>>c[i];}
    C[0][0]=1;
    for(int i=1;i<=n;i++){
        C[i][0]=1;
        for(int j=1;j<=i;j++){
            C[i][j]=C[i-1][j]+C[i-1][j-1];
        }
    }
    dp[0][0]=1;
    double sum=0;
    for(int i=1;i<=n;i++){
        for(int j=i-1;j>=0;j--){
            for(int k=sum;k>=0;k--){
                dp[j+1][k+c[i]]+=dp[j][k];
            }
        }
        sum+=c[i];
    }
    double ans=0;
    for(int i=0;i<=n-1;i++){
        for(int j=0;j<=sum;j++){
            ans+=min((sum-j)/(n-i),x/2.0*(1.0*n/(n-i)+1))*dp[i][j]/C[n][i];
        }
    }
    printf("%.9lf",ans);
}
