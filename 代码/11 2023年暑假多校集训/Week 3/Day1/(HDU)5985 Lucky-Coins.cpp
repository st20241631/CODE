#include <iostream>
#define int long long
using namespace std;
double qpow(double x,int y){
    double ans=1;
    while (y){
        if(y&1) ans=ans*x;
        y>>=1;
        x=x*x;
    }
    return ans;
}
double dp[105][1050];
void solve(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        int x;
        double y;
        cin>>x>>y;
        double tmp=1;
        for(int j=0;j<100;j++){
            dp[i][j]=qpow(1-tmp,x);
            tmp=tmp*y;
        }
    }
    for(int i=1;i<=n;i++){
        double ans=0;
        for(int j=0;j<100-1;j++){
            double tmp=1;
            for(int k=1;k<=n;k++)if(k!=i) tmp*=dp[k][j];
            ans+=(dp[i][j+1]-dp[i][j])*tmp;
        }
        printf("%.6lf ",ans);
    }
    cout<<"\n";
}
signed main(){
    int t;
    cin>>t;
    while (t--) solve();
}