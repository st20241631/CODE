#include <bits/stdc++.h>
using namespace std;
int mp[305][305];
main(){

    freopen("water.in","r",stdin);
    freopen("water.out","w",stdout);
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>mp[i][j];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(mp[i][j]>0){
                int x=mp[i][j];
                x=max(x,min({mp[i-1][j],mp[i][j-1],mp[i][j+1],mp[i+1][j]}));
                cout<<x-mp[i][j]<<" ";
            }
            else {
                int x=0;
                x=max(x,min({mp[i-1][j],mp[i][j-1],mp[i][j+1],mp[i+1][j]}));
                cout<<x-mp[i][j]<<" ";
            }

        }
        cout<<"\n";
    }
}