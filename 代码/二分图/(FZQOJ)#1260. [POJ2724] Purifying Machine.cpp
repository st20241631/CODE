#include <cstring>
#include <string>
#include <iostream>
#include <map>
using namespace std;
int n,m;
map<int,bool> mp;
int cnt,a[2001];
bool ma[2001][2001];
void init(){
    memset(ma, false,sizeof ma);
    cnt=0;
    mp.clear();
    for(int i=1;i<=m;i++){
        string s;
        cin>>s;
        int sum=0;
        for(int j=0;j<n;j++){
            if(s[j]=='*') sum=sum<<1;
            else sum=(sum<<1)+s[j]-'0';
        }
        if(!mp[sum]){
            mp[sum]=true;
            a[++cnt]=sum;
        }
        sum=0;
        for(int j=0;j<n;j++){
            if(s[j]=='*') sum=(sum<<1)+1;
            else sum=(sum<<1)+s[j]-'0';
        }
        if(!mp[sum]){
            mp[sum]=true;
            a[++cnt]=sum;
        }
    }
    for(int i=1;i<=cnt;i++){
        for(int j=1;j<=cnt;j++){
            int tmp=a[i]^a[j];
            if(tmp&&(tmp&(tmp-1))==0) ma[i][j]=ma[j][i]=1;
        }
    }
}
bool vis[100000];
int match[100000];
bool dfs(int x){
    for(int y=1;y<=cnt;y++){
        if(ma[x][y]&&!vis[y]){
            vis[y]= true;
            if(!match[y]||dfs(match[y])){
                match[y]=x;
                return true;
            }
        }
    }
    return false;
}
void solve(){
    memset(match,0,sizeof match);
    int ans=0;
    for(int i=1;i<=cnt;i++){
        memset(vis,false,sizeof vis);
        if(dfs(i)) ans++;
    }
    cout<<cnt-ans/2<<"\n";

}
int main(){
    cin>>n>>m;
    while(n!=0||m!=0){
        init();
        solve();
        cin>>n>>m;
    }
}