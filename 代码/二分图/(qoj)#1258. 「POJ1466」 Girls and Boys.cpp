#include <iostream>
#include <cstdio>
#include <string.h>
using namespace std;
int n,ans,k;
int a[505][505];
int match[2005];
bool vis[2005];
bool dfs(int x){
    for(int y=1;y<=n;y++){
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
    while(cin>>n){
        init();
        for(int i=1;i<=n;i++){
            int sum,tmp;
            scanf("%d: (%d)",&tmp,&sum);
            for(int j=1;j<=sum;j++){
                int x;
                cin>>x;
                x+=1;
                a[i][x]=1;
            }
        }
        for(int i=1;i<=n;i++){
            memset(vis,false,sizeof(vis));
            if(dfs(i)) ans++;
        }
        cout<<n-ans/2<<"\n";
    }

}