#include<bits/stdc++.h>
using namespace std;
struct edge{
    int v,nex;
}a[10000000];
int first[100000],cnt;
void add(int u,int v){
    a[++cnt]=edge{v,first[u]};
    first[u]=cnt;
}
int jin[105][105];
int n,m;
int dx[4]={-1,0,1,0};
int dy[4]={0,1,0,-1};
void Add(int x,int y){
    int pos=(x-1)*n+y;
    for(int i=0;i<4;i++){
        int X=x+dx[i],Y=y+dy[i];
        int pos2=(X-1)*n+Y;
        if(X>=1&&X<=n&&Y>=1&&Y<=n){
            if(!jin[X][Y]){
                add(pos,pos2);
            }
        }
    }
}
bool vis[100000];
int pi[1000000];
int dfs(int u){
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(vis[v])continue;
        vis[v]=true;
        if(!pi[v]||dfs(pi[v])){
            pi[v]=u;
            return 1;
        }
    }
    return 0;
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int x,y;
        cin>>x>>y;
        jin[x][y]=1;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if((i+j)%2&&!jin[i][j]){
                Add(i,j);
            }
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if((i+j)%2&&!jin[i][j]){
                memset(vis,false,sizeof(vis));
                int pos=(i-1)*n+j;
                if(dfs(pos))ans++;
            }
        }
    }
    cout<<ans;
}