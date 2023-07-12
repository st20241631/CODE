#include <bits/stdc++.h>
using namespace std;
char mp1[1005][1005];
char mp2[1005][1005];
int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)cin>>mp1[i][j];
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)cin>>mp2[i][j];

    int cnt=0;
    //将B改为和A一样
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)if(mp2[i][j]!=mp1[i][j]) cnt++;
    if(cnt<=(n*m/2)) {
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++) cout<<mp1[i][j];
            cout<<"\n";
        }
        return 0;
    }

    cnt=0;
    //将B改为和A相反
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)if(mp2[i][j]==mp1[i][j]) cnt++;
    if(cnt<=(n*m/2)){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(mp1[i][j]=='.') cout<<'X';
                else cout<<'.';
            }
            cout<<"\n";
        }
        return 0;
    }
    cout<<"-1";
    return 0;

}