#include <bits/stdc++.h>
using namespace std;
int n;
char a[305][305];
char mp[305][305];
void solve(){
    cin>>n;
    int k=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>a[i][j];
            if(a[i][j]!='.') k++;
        }
    }
    int cnt;
    // 第0类的X改为O，第1类的O改为X
    cnt=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if((i+j)%3==0&&a[i][j]=='X') cnt++;
            else if((i+j)%3==1&&a[i][j]=='O') cnt++;
        }
    }
    if(cnt<=k/3){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if((i+j)%3==0&&a[i][j]=='X') cout<<'O';
                else if((i+j)%3==1&&a[i][j]=='O') cout<<'X';
                else cout<<a[i][j];
            }
            cout<<"\n";
        }
        return;
    }
    // 第1类的X改为O，第2类的O改为X
    cnt=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if((i+j)%3==1&&a[i][j]=='X') cnt++;
            else if((i+j)%3==2&&a[i][j]=='O') cnt++;
        }
    }
    if(cnt<=k/3){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if((i+j)%3==1&&a[i][j]=='X') cout<<'O';
                else if((i+j)%3==2&&a[i][j]=='O') cout<<'X';
                else cout<<a[i][j];
            }
            cout<<"\n";
        }
        return;
    }
    // 第2类的X改为O，第0类的O改为X
    cnt=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if((i+j)%3==2&&a[i][j]=='X') cnt++;
            else if((i+j)%3==0&&a[i][j]=='O') cnt++;
        }
    }
    if(cnt<=k/3){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if((i+j)%3==2&&a[i][j]=='X') cout<<'O';
                else if((i+j)%3==0&&a[i][j]=='O') cout<<'X';
                else cout<<a[i][j];
            }
            cout<<"\n";
        }
        return;
    }
}
signed  main(){
    int t;
    cin>>t;
    while (t--){
        solve();
    }
}