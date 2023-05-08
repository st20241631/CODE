#include <bits/stdc++.h>

using namespace std;
int n, m,ans;
int a[205][205];
int match[205];
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
int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        a[x][y] = 1;
    }
    for (int i = 1; i <= n; i++)a[i][i] = 1;
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                a[i][j]|=a[i][k]&&a[k][j];
            }
        }
    }
    for(int i=1;i<=n;i++) a[i][i]=0;
    ans=n;
    for(int i=1;i<=n;i++){
        memset(vis,0,sizeof vis);
        ans-=dfs(i);
    }
    cout<<ans;
}