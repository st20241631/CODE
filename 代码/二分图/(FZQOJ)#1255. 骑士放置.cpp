#include <bits/stdc++.h>
using namespace std;
#define PII pair<int,int>
int n,m,t;
int jin[110][110];
bool vis[110][110];
PII match[110][110];
int dx[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};
bool dfs(int x,int y){
    for(int i=0;i<8;i++){
        int nx=x+dx[i],ny=y+dy[i];
        if(nx<1||nx>n||ny<1||ny>m||jin[nx][ny]||vis[nx][ny])continue;
        vis[nx][ny]=true;
        if(!match[nx][ny].first||dfs(match[nx][ny].first,match[nx][ny].second)){
            match[nx][ny]= make_pair(x,y);
            return true;
        }
    }
    return false;
}
int main(){
    cin>>n>>m>>t;
    for(int i=1;i<=t;i++){
        int x,y;
        cin>>x>>y;
        jin[x][y]=1;
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if((i+j)&1||jin[i][j]) continue;
            memset(vis,0,sizeof vis);
            if(dfs(i,j)) ans++;
        }
    }
    cout<<n*m-t-ans;
}