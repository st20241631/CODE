#include <bits/stdc++.h>

using namespace std;
struct node{
    int val,last;
}r[1000000],c[1000000];
int color(int i,int j){
    if(r[i].last>c[j].last) return r[i].val;
    else if (r[i].last<c[j].last) return c[j].val;
    return 0;
}
struct node2{
    int x,y,dis;
};
int n,m,qq;
int dx[4]={-1,0,1,0};
int dy[4]={0,1,0,-1};
int f(int x,int y){
    return (x-1)*n+y;
}
int bfs(int r1,int c1,int r2,int c2,int k){
    if(color(r1,c1)<k|| color(r2,c2)<k)return -1;
    queue<node2> q;
    unordered_map<int,bool> vis;
    q.push({r1,c1,0});
    vis[f(r1,c1)]= true;
    while (!q.empty()){
        node2 now=q.front();
        q.pop();
        if(now.x==r2&&now.y==c2) return now.dis;
        for(int i=0;i<4;i++){
            int xx=now.x+dx[i];
            int yy=now.y+dy[i];
            if(xx<1||xx>n||yy<1||yy>m)continue;
            if(!vis[f(xx,yy)]){
                vis[f(xx,yy)]= true;
                q.push({xx, yy, now.dis + 1});
            }
        }
    }
    return -1;
}
int main(){
    freopen("puxi.in","r",stdin);
    freopen("puxi.out","w",stdout);
    cin>>n>>m>>qq;
    for(int t=1;t<=qq;t++){
        int opt;
        cin>>opt;
        if(opt==1){
            int x;
            cin>>x;
            r[x].val=t;
            r[x].last=t;
        }
        if(opt==2){
            int x;
            cin>>x;
            c[x].val=t;
            c[x].last=t;
        }
        if(opt==3){
            int r1,c1,r2,c2,k;
            cin>>r1>>c1>>r2>>c2>>k;
            cout<<bfs(r1,c1,r2,c2,k)<<"\n";
        }
    }
}