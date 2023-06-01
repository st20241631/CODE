#include <iostream>
#include <string.h>
using namespace std;
int n, m,ans,k;
int a[205][205];
int match[205];
bool vis[2005];
bool dfs(int x){
    for(int y=1;y<=m;y++){
        if(a[x][y]&&!vis[y]){
            vis[y]= true;
            if(!match[y]||dfs(match[y])){
                match[y]=x;
                return true;
            }
        }
    }
    return false;
}
void init(){
    ans=0;
    memset(a,0,sizeof a);
    memset(match,0,sizeof match);
}
int main() {
    cin>>n;
    while(n!=0){
        init();
        cin>>m>>k;
        for(int i=1;i<=k;i++){
            int x,y;
            cin>>x;
            cin>>x>>y;
            if(x!=0&&y!=0)a[x][y]=1;
        }
        for(int i=1;i<n;i++){
            memset(vis,false,sizeof(vis));
            if(dfs(i)) ans++;
        }
        cout<<ans<<"\n";
        cin>>n;
    }

}