#include<bits/stdc++.h>
using namespace std;
const double eps=1e-10;
int n,m;
double t1,t2,v;
struct node{
    int x,y;
}a[1000000],b[1000000];
double dis[500][500];
vector<int> G[500];
double f(int x1,int y1,int x2,int y2){
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
int match[50000];
bool vis[50000];
bool dfs(int x){
    for(int i=0;i<G[x].size();i++){
        int v=G[x][i];
        if(vis[v]) continue;
        vis[v]=true;
        if(!match[v]||dfs(match[v])){match[v]=x; return true;}
    }
    return false;
}
int main(){
    cin>>n>>m>>t1>>t2>>v;
    t1/=60;
    for(int i=1;i<=m;i++)cin>>a[i].x>>a[i].y;
    for(int i=1;i<=n;i++)cin>>b[i].x>>b[i].y;
    for(int i=1;i<=m;i++)for(int j=1;j<=n;j++)dis[i][j]=f(a[i].x,a[i].y,b[j].x,b[j].y)/v;
    double l=0,r=1e8;
    while(r-l>1e-8){
        double mid=(l+r)/2;
        int p=(mid+t2)/(t1+t2)+eps;
        p=min(p,m);
        for(int i=1;i<=m;i++){
            G[i].clear();
            for(int j=1;j<=n;j++)for(int k=1;k<=p;k++)if(k*t1+(k-1)*t2+dis[i][j]<mid-eps)G[i].push_back((j-1)*p+k);
        }
        memset(match,0,sizeof match);
        bool flag=true;
        for(int i=1;i<=m;i++){
            memset(vis,false,sizeof vis);
            if(!dfs(i)){
                flag=false;
                break;
            }
        }
        if(flag) r=mid;
        else l=mid;
    }
    printf("%.6lf",r);



    return 0;
}