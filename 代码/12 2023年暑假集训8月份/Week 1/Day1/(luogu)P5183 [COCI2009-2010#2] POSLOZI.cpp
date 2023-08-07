#include <bits/stdc++.h>

using namespace std;
vector<int> ans,now;
int n,m;
int dis[55][55];
int a[55];

struct node{
    int x,y;
}b[1000];

int dep;

int h(){
    int cnt=0;
    for(int i=1;i<=n;i++)cnt+=dis[a[i]][i];
    return cnt;
}
bool dfs(int depth,int pre){
    int least=h();
    if(2*depth+least>2*dep) return false;   //depth+least/2>dep
    if(least==0){
        ans=now;
        return true;
    }
    for(int i=1;i<=m;i++){
        if(i==pre) continue;
        swap(a[b[i].x],a[b[i].y]);
        now.push_back(i);
        if (dfs(depth+1,i)) return true;
        now.pop_back();
        swap(a[b[i].x],a[b[i].y]);
    }
    return false;
}
int main(){
    memset(dis,0x3f,sizeof dis);
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) dis[i][i]=0;
    for(int i=1;i<=m;i++){
        cin>>b[i].x>>b[i].y;
        dis[b[i].x][b[i].y]=dis[b[i].y][b[i].x]=min(dis[b[i].x][b[i].y],1);
    }
    for(int k=1;k<=n;k++)for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);

    while(!dfs(0,0)) dep++;
    cout<<dep<<"\n";
    for(int i:ans) cout<<i<<"\n";
    return 0;

}