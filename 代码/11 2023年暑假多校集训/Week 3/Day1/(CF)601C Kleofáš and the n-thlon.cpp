#include <bits/stdc++.h>
using namespace std;
int a[1000000];
double dp[110][100100];
double sum[100100];
int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=m;i++){
        if(i!=a[1]) dp[1][i]=1;
    }
    for(int i=2;i<=n;i++){
        for(int j=1;j<=i*m;j++){
            sum[j]=sum[j-1]+dp[i-1][j];
            if(j>=i){
                if(j>=m+1)dp[i][j]=(sum[j-1]-sum[j-m-1]-(j>=a[i]?dp[i-1][j-a[i]]:0))/(m-1);
                else dp[i][j]=(sum[j-1]-(j>=a[i]?dp[i-1][j-a[i]]:0))/(m-1);
            }
        }
    }
    double ans=1;
    int cnt=0;
    for(int i=1;i<=n;i++)cnt+=a[i];
    for(int i=1;i<cnt;i++) ans=ans+dp[n][i];
    printf("%.9lf",ans);
}
