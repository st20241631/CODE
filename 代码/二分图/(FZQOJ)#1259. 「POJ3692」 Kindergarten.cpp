#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
int n;
int a[505][505];
int match[5005];
bool vis[5005];
bool dfs(int x){
    for(int y=1;y<=n;y++){
        if(a[x][y]&&!vis[y]){
            vis[y]=true;
            if(!match[y]||dfs(match[y])){
                match[y]=x;
                return true;
            }
        }
    }
    return false;
}
int main(){
    int G,B,M;
    cin>>G>>B>>M;
    int sum=1;
    while(G!=0&&B!=0&&M!=0){
        n=G+B;
        memset(a,0,sizeof a);
        memset(match,0,sizeof match);
        for(int i=1;i<=B;i++)for(int j=1;j<=B;j++)a[i][j]=1;
        for(int i=B+1;i<=n;i++)for(int j=B+1;j<=n;j++)a[i][j]=1;
        for(int i=1;i<=M;i++){
            int x,y;
            cin>>x>>y;
            a[x+B][y]=1;
            a[y][x+B]=1;
        }
        for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)a[i][j]=!a[i][j];
        int ans=0;
        for(int i=1;i<=n;i++){
            memset(vis,false,sizeof(vis));
            if(dfs(i))ans++;
        }
        ans/=2;
        ans=n-ans;
        printf("Case %d: %d\n",sum,ans);
        sum++;
        cin>>G>>B>>M;
    }
}
