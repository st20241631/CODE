#include <string>
#include <iostream>
#include <cstring>
using namespace std;
int n,m;
int dis[150][150];
int ax[150],ay[150],bx[150],by[150];
int cnta,cntb;
void init(){
    cnta=cntb=0;
    for(int i=0;i<n;i++){
        string s;
        cin>>s;
        for(int j=0;j<m;j++){
            if(s[j]=='m') {cnta++;ax[cnta]=i;ay[cnta]=j;}
            else if(s[j]=='H') {cntb++;bx[cntb]=i,by[cntb]=j;}
        }
    }
    for(int i=1;i<=cnta;i++){
        for(int j=1;j<=cntb;j++){
            dis[i][j]=-(abs(ax[i]-bx[j])+abs(ay[i]-by[j]));
        }
    }
}
int la[1005],lb[1005];
bool va[1005],vb[1005];
int match[1005];
int upd[1005];
bool dfs(int x){
    va[x]=true;
    for(int y=1;y<=cnta;y++){
        if(!vb[y]){
            int tmp=la[x]+lb[y]-dis[x][y];
            if(tmp==0){
                vb[y]=true;
                if(!match[y]||dfs(match[y])){
                    match[y]=x;
                    return true;
                }
            }
            else upd[y]=min(upd[y],la[x]+lb[y]-dis[x][y]);
        }

    }
    return false;
}
void solve(){
    memset(match,0,sizeof match);
    for(int i=1;i<=cnta;i++){
        la[i]=-0x3f3f3f3f;
        lb[i]=0;
        for(int j=1;j<=cnta;j++)la[i]=max(la[i],dis[i][j]);
    }
    for(int i=1;i<=cnta;i++){
        while(1){
            memset(va, false,sizeof va);
            memset(vb, false,sizeof vb);
            memset(upd,0x3f,sizeof upd);
            if(dfs(i)) break;
            int delta=0x3f3f3f3f;
            for(int j=1;j<=cnta;j++)if(!vb[j]) delta=min(delta,upd[j]);
            for(int j=1;j<=cnta;j++){
                if(va[j]) la[j]-=delta;
                if(vb[j]) lb[j]+=delta;
            }
        }
    }
    int ans=0;
    for(int i=1;i<=cnta;i++)ans+=la[i]+lb[i];
    cout<<ans*(-1)<<"\n";
}
int main(){
    cin>>n>>m;
    while(n!=0&&m!=0){
        init();
        solve();
        cin>>n>>m;
    }
}