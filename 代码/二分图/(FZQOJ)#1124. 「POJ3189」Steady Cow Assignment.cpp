#include <bits/stdc++.h>
using namespace std;
const int MAXN=1010,MAXM=30;
int n,m,a[MAXN][MAXM],match[MAXM][MAXN],b[MAXN];
bool vis[MAXM];
bool dfs(int x,int l,int r){
    for(int i=l;i<=r;i++){
        int y=a[x][i];
        if(!vis[y]){
            vis[y]=true;
            if(match[y][0]<b[y]){
                match[y][++match[y][0]]=x;
                return true;
            }
            for(int j=1;j<=match[y][0];j++){
                if(dfs(match[y][j],l,r)){
                    match[y][j]=x;
                    return true;
                }
            }
        }
    }
    return false;
}
bool check(int mid){
    for(int l=1;l+mid-1<=m;l++){
        int r=l+mid-1;
        int sum=0;
        memset(match,0,sizeof match);
        for(int j=1;j<=n;j++){
            memset(vis, false,sizeof vis);
            if(dfs(j,l,r)) sum++;
        }
        if(sum==n) return true;
    }
    return false;
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>a[i][j];
        }
    }
    for(int i=1;i<=m;i++)cin>>b[i];
    int l=1,r=m;
    while (l<r){
        int mid=(l+r)>>1;
        if(check(mid)) r=mid;
        else l=mid+1;
    }
    cout<<l;
}