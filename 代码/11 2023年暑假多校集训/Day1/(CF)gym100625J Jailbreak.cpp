#include <bits/stdc++.h>

using namespace std;
int n,m;
char mp[200][200];

struct node{
    int x,y,val;
};

int dx[4]={-1,0,1,0};
int dy[4]={0,1,0,-1};
bool vis[105][105];
int dis[4][105][105];
void bfs(int u){
    memset(vis,false,sizeof vis);
    deque<node> q;
    for(int i=0;i<=n+1;i++){
        for(int j=0;j<=m+1;j++){
            if(mp[i][j]-'0'==u) q.push_back(node{i,j,0});
        }
    }
    while (!q.empty()){
        node now=q.front();
        q.pop_front();
        if(vis[now.x][now.y]) continue;
        vis[now.x][now.y]=1;
        dis[u][now.x][now.y]=now.val;
        for(int i=0;i<4;i++){
            int x=now.x+dx[i];
            int y=now.y+dy[i];
            if(x<0||y<0||x>n+1||y>m+1||mp[x][y]=='*') continue;
            if(mp[x][y]!='#') q.push_front(node{x,y,now.val});
            else q.push_back(node{x,y,now.val+1});
        }
    }
}
void solve(){
    cin>>n>>m;

    //将第一个犯人记为1，第二个犯人记为2，周围一圈记为3
    bool flag=true;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>mp[i][j];
            if(mp[i][j]=='$'){
                if(flag) mp[i][j]='1',flag=false;
                else mp[i][j]='2';
            }
        }
    }
    for(int i=0;i<=n+1;i++) mp[i][0]=mp[i][m+1]='3';
    for(int i=0;i<=m+1;i++) mp[0][i]=mp[n+1][i]='3';
    memset(dis,0x3f,sizeof dis);
    for(int i=1;i<=3;i++) bfs(i);
    int Min=0x3f3f3f3f;
    for(int i=0;i<=n+1;i++){
        for(int j=0;j<=m+1;j++){
            if(mp[i][j]=='*') continue;
            int ans=dis[1][i][j]+dis[2][i][j]+dis[3][i][j];
            if(mp[i][j]=='#') ans-=2;
            Min=min(Min,ans);
        }
    }
    cout<<Min<<"\n";
}
int main(){
    int t;
    cin>>t;
    while(t--){
        solve();
    }
}