#include <bits/stdc++.h>
using namespace std;
const double eps=1e-12;
double p[1605][1605][5];
double a[1605][1605];
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
int n,m;
int f(int x,int y){return x*m+y;}
int main(){
    cin>>n>>m;
    while(n!=0&&m!=0){
        for(int k=0;k<4;k++)for(int i=0;i<n;i++)for(int j=0;j<m;j++)cin>>p[i][j][k];
        memset(a,0,sizeof a);
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                int tmp=f(i,j);
                a[tmp][tmp]=a[tmp][n*m]=1;
                for(int k=0;k<4;k++){
                    int x=i+dx[k];
                    int y=j+dy[k];
                    if(x<0||y<0||x>=n||y>=m) continue;
                    a[tmp][f(x,y)]-=p[i][j][k];
                }
            }
        }
        for(int i=0;i<=n*m;i++) if(i!=n*m-1) a[n*m-1][i]=0;

        for(int i=n*m-1;i>=0;i--) {
            for(int k=i-1; k>=0; k--) {
                double p=a[k][i]/a[i][i];
                if(fabs(p)<eps) continue;
                for(int j=i; j>=0; j--) a[k][j] -= a[i][j] * p;
                a[k][n*m]-=a[i][n*m]*p;
            }
        }
        printf("%.11lf\n",a[0][n*m]/a[0][0]);
        cin>>n>>m;

    }
}