#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod= 1e9+7;
int n,m,k;
struct matrix{
    int a[200][200];
    void clear(){memset(a,0,sizeof a);}
    matrix operator*(const matrix b) const{
        matrix ans;
        ans.clear();
        for(int i=0;i<=m;i++){
            for(int j=0;j<=m;j++){
                for(int k=0;k<=m;k++){
                    ans.a[i][j]=(ans.a[i][j]+a[i][k]*b.a[k][j]%mod)%mod;
                }
            }
        }
        return ans;
    }
}ans,base;
void qpow(matrix x,int y){
    while(y){
        if(y&1) ans=ans*x;
        y>>=1;
        x=x*x;
    }
}
int qpow(int x,int y){
    int ans=1;
    while(y){
        if(y&1) ans=ans*x%mod;
        y>>=1;
        x=x*x%mod;
    }
    return ans;
}
int A[100000];
int a[100000],b[100000],c[100000];
signed main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++){cin>>A[i];m+=(A[i]==0);}
    int t=0;
    for(int i=1;i<=m;i++)t+=(A[i]==0);
    for(int i=0;i<=m;i++){
        a[i]=(m-i)*(m-i)%mod;
        b[i]=i*(n-2*m+i)%mod;
        c[i]=(m*(m-1)*qpow(2,mod-2)%mod+(n-m)*(n-m-1)*qpow(2,mod-2)%mod+i*(m-i)%mod+(m-i)*(n-2*m+i)%mod+mod)%mod;
    }
    ans.clear();
    for(int i=0;i<=m;i++) ans.a[i][i]=1;
    base.clear();
    base.a[0][0]=c[0];
    base.a[0][1]=b[1];
    base.a[m][m-1]=a[m-1];
    base.a[m][m]=c[m];
    for(int i=1;i<m;i++){
        base.a[i][i-1]=a[i-1];
        base.a[i][i+1]=b[i+1];
        base.a[i][i]=c[i];
    }
    qpow(base,k);
    base.clear();
    base.a[t][0]=1;
    ans=ans*base;
    int sum=0;
    for(int i=0;i<=m;i++)sum=(sum+ans.a[i][0])%mod;
    cout<<(ans.a[m][0]*qpow(sum,mod-2)%mod)%mod;

}