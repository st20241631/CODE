#include <bits/stdc++.h>
using namespace std;
int n;
struct node{
    double x,y;
}a[10000],b[10000];
double w[1005][1005];
double dis(node a,node b){
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
int match[1005];
bool va[1005],vb[1005];
double la[1005],lb[1005],delta,upd[1005];
bool dfs(int x){
    va[x]= true;
    for(int y=1;y<=n;y++){
        if(!vb[y]){
            if(abs(la[x]+lb[y]-w[x][y])<1e-7){
                vb[y]= true;
                if(!match[y]||dfs(match[y])){
                    match[y]=x;
                    return true;
                }
            }
            else upd[y]=min(upd[y],la[x]+lb[y]-w[x][y]);
        }
    }
    return false;
}
void KM(){
    for(int i=1;i<=n;i++){
        la[i]=-0x3f3f3f3f;
        lb[i]=0;
        for(int j=1;j<=n;j++)la[i]=max(la[i],w[i][j]);
    }
    for(int i=1;i<=n;i++){
        while(true){
            memset(va,false,sizeof va);
            memset(vb,false,sizeof vb);
            for(int j=1;j<=n;j++) upd[j]=0x3f3f3f3f;
            if(dfs(i)) break;
            delta=0x3f3f3f3f;
            for(int j=1;j<=n;j++)if(!vb[j]) delta=min(delta,upd[j]);
            for(int j=1;j<=n;j++){
                if(va[j]) la[j]-=delta;
                if(vb[j]) lb[j]+=delta;
            }
        }
    }
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i].x>>a[i].y;
    for(int i=1;i<=n;i++)cin>>b[i].x>>b[i].y;
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)w[j][i]=-dis(a[i],b[j]);
    KM();
    for(int i=1;i<=n;i++)cout<<match[i]<<"\n";
}