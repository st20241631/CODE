#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int d[100000];

int ans=0;
int dp[100000][2][2];
void solve(int len){
    memset(dp,0,sizeof dp);
    dp[0][0][0]=1;
    int m=(len>>1);
    for(int i=0;i<m;i++){
        for(int j=0;j<2;j++){
            for(int k=0;k<2;k++){
                if(!dp[i][j][k]) continue;
                for(int x=0;x<=9;x++){
                    int y=x+d[i+1]+k;
                    bool flag=false;
                    if(y>=10) {flag= true; y-=10;}
                    if(!i&&!y) continue;
                    if(y+d[len-i]==j*10+x) dp[i+1][0][flag]=(dp[i+1][0][flag]+dp[i][j][k])%mod;
                    if(y+d[len-i]+1==j*10+x) dp[i+1][1][flag]=(dp[i+1][1][flag]+dp[i][j][k])%mod;
                }
            }
        }
    }
    if(len&1){
        for(int j=0;j<2;j++){
            for(int k=0;k<2;k++){
                if(!dp[m][j][k]) continue;
                for(int x=0;x<=9;x++){
                    if(x+d[m+1]+k==x+j*10)  ans=(ans+dp[m][j][k])%mod;
                }
            }
        }
    }
    else ans=(ans+(dp[m][0][0]+dp[m][1][1])%mod)%mod;
}

char D[100000];
signed main(){
    cin>>(D+1);
    int len= strlen(D+1);
    for(int i=1;i<=len;i++)d[i]=D[len-i+1]-'0';

    for(int i=max((long long)2,len);i<=(len<<1);i++) solve(i);
    cout<<ans%mod;
}