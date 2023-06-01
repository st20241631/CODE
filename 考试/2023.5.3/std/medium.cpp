#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=211,mod=1000000007;
int C[N][N],n,m,V,a[N];
int max(int x,int y){
    if(x>y)return x;
    else return y;
}
void work(){
    cin>>n>>m>>V;
    for(int i=1;i<=n;i++)cin>>a[i];
    sort(a+1,a+n+1);
    int ans=0;
    //|S|<V
    for(int t=1;t<=n;t++){
        static int dp[N][N*N];
        dp[1][0]=1;
        for(int i=1;i<=n;i++){
            for(int j=0;j<=m*V;j++){
                if(dp[i][j]){
                    if(i!=t&&m+a[t]-a[i]>=0)(dp[i+1][min(m*V,j+min(m,m+a[t]-a[i]))]+=dp[i][j])%=mod;
                    if(i>=t)(dp[i+1][min(m*V,j+m)]+=dp[i][j])%=mod;
                }
            }
        }
        (ans+=dp[n+1][m*V])%=mod;
        for(int i=0;i<=n+1;i++)for(int j=0;j<=m*V+1;j++)dp[i][j]=0;
        dp[1][0]=1;
        for(int i=1;i<=n;i++){
            for(int j=0;j<=i-1;j++){
                if(dp[i][j]){
                    if(i!=t&&m+a[t]-a[i]>=0)(dp[i+1][j]+=dp[i][j])%=mod;
                    if(i>=t)(dp[i+1][j+1]+=dp[i][j])%=mod;
                }
            }
        }
        for(int j=V;j<=n;j++)(ans+=mod-dp[n+1][j])%=mod;
        for(int i=0;i<=n+1;i++)for(int j=0;j<=n+1;j++)dp[i][j]=0;
    }
    //|S|>=V
    for(int t=1;t<=n;t++){
        int L=1;
        while(a[L]+m<a[t])++L;
        static int dp[N][N*N];
        dp[L][0]=1;
        for(int i=L;i<=n;i++){
            for(int j=0;j<=m*V;j++){
                if(dp[i][j]){
                    int w=max((a[t]-a[i]),0);
                    if(j+w<=m*V&&i!=t)(dp[i+1][j+w]+=dp[i][j])%=mod;
                    if(i<=t)(dp[i+1][j]+=dp[i][j])%=mod;
                }
            }
        }
        for(int j=0;j<=m*V;j++)(ans+=dp[n+1][j])%=mod;
        for(int i=0;i<=n+1;i++)for(int j=0;j<=m*V+1;j++)dp[i][j]=0;
        dp[L][0]=1;
        for(int i=L;i<=n;i++){
            for(int j=0;j<=i-L;j++){
                if(dp[i][j]){
                    int w=a[t]-a[i];
                    if(j+w<=m*V&&i!=t)(dp[i+1][j+1]+=dp[i][j])%=mod;
                    if(i<=t)(dp[i+1][j]+=dp[i][j])%=mod;
                }
            }
        }
        for(int j=0;j<=V-1;j++)(ans+=mod-dp[n+1][j])%=mod;
        for(int i=0;i<=n+1;i++)for(int j=0;j<=n+1;j++)dp[i][j]=0;
    }
    (ans+=1)%=mod;
    printf("%lld\n",ans);
}
signed main(){
//    freopen("medium.in","r",stdin);
//    freopen("medium.out","w",stdout);
    for(int i=0;i<=N-1;i++)C[i][0]=1;
    for(int i=1;i<=N-1;i++)for(int j=1;j<=i;j++)C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
    int T;cin>>T;
    while(T--)work();
    return 0;
}
