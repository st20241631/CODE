#include<bits/stdc++.h>
using namespace std;
const double eps=1e-6;
double a[400][400];
bool b[400][400];
int cd[400];
int main(){
    int n,m;
    double p,q;
    cin>>n>>m>>p>>q;
    p/=q;
    for(int i=1;i<=m;i++){
        int x,y;
        cin>>x>>y;
        b[x][y]=b[y][x]=1;
        cd[x]++,cd[y]++;
    }
    a[1][n+1]=1;
    for(int i=1;i<=n;i++){
        a[i][i]=1;
        for(int j=1;j<=n;j++){
            if(b[i][j]){
                a[i][j]-=(1.0-p)/cd[j];
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            if(fabs(a[j][i])>eps){
                swap(a[i],a[j]);
                break;
            }
        }
        for(int j=1;j<=n;j++){
            if(i==j) continue;
            double tmp=a[j][i]/a[i][i];
            for(int k=i;k<=n+1;k++){
                a[j][k]-=a[i][k]*tmp;
            }
        }
    }
    for(int i=1;i<=n;i++){
        printf("%.9lf\n",(a[i][n+1]/a[i][i])*p);
    }
}