#include <bits/stdc++.h>

#define int unsigned long long
using namespace std;
const int p=1331,N=305;
const double eps=1e-8;
string s[N];
int ksm[N],Hash[N][N],n,m;
double ksm2[N];
double a[N][N];

int HASH(int id,int l,int r){return Hash[id][r]-Hash[id][l-1]*ksm[r-l+1];}

signed main(){
    cin>>n>>m;
    ksm[0]=1,ksm2[0]=1;
    for(int i=1;i<N;i++)ksm[i]=ksm[i-1]*p,ksm2[i]=ksm2[i-1]/2.0;
    for(int i=1;i<=n;i++){cin>>s[i];for(int j=0;j<m;j++)Hash[i][j+1]=Hash[i][j]*p+s[i][j];}
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)for(int k=1;k<=m;k++)if(HASH(i,1,k)==HASH(j,m-k+1,m))a[i][j]+=ksm2[m-k];
    for(int i=1;i<=n;i++)a[i][n+1]=-ksm2[m],a[n+1][i]=1;
    a[n+1][n+2]=1;
    for(int i=1;i<=n+1;i++){
        for(int j=i;j<=n+1;j++){
            if(fabs(a[j][i])>eps){
                swap(a[i],a[j]);
                break;
            }
        }
        for(int j=1;j<=n+1;j++){
            if(j==i)continue;
            double tmp=a[j][i]/a[i][i];
            for(int k=i;k<=n+2;k++){a[j][k]-=a[i][k]*tmp;}
        }
    }
    for(int i=1;i<=n;i++){
        printf("%.8lf\n",a[i][n+2]/a[i][i]);
    }

}