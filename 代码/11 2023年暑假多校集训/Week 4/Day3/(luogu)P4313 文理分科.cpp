#include <bits/stdc++.h>
#define int long long
const int INF=0x7fffffffffffll;
using namespace std;
int n,m;
struct node{
    int v,w,nex;
}a[10000000];
int first[10000000],cnt=1;
void add(int u,int v,int w){
    a[++cnt]=node{v,w,first[u]};
    first[u]=cnt;
}
int s,t;
int now[1000000];//弧优化
int dis[1000000];
int bfs(){
    memset(dis,0,sizeof dis);
    queue<int> bfs;
    bfs.push(s);
    dis[s]=1;
    now[s]=first[s];
    while(!bfs.empty()){
        int u=bfs.front();
        bfs.pop();
        for(int i=first[u];i;i=a[i].nex){
            int v=a[i].v;
            if(!dis[v]&&a[i].w){
                dis[v]=dis[u]+1;
                now[v]=first[v];
                bfs.push(v);
                if(v==t) return 1;
            }
        }
    }
    return 0;
}
int dinic(int u, int rest){
    if(u==t) return rest;
    int have=rest;
    for(int i=now[u]; i&&have; i=a[i].nex){
        int v=a[i].v;
        now[u]=i;
        if(dis[v]== dis[u] + 1&&a[i].w){
            int tmp=dinic(v,min(have,a[i].w));
            if(!tmp) dis[v]=0;
            a[i].w-=tmp;
            a[i^1].w+=tmp;
            have-=tmp;
        }
    }
    return rest - have;
}
int dx[5]={-1,0,1,0};
int dy[5]={0,1,0,-1};
int f(int i,int j){return (i-1)*m+j;}
int f_art(int i,int j){return n*m+f(i,j);}
int f_sci(int i,int j){return n*m*2+f(i,j);}
int art[105][105],sci[105][105];
int exart[105][105],exsci[105][105];
main(){
    cin>>n>>m;
    int sum=0;
    s=n*m*3+1,t=n*m*3+2;
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){cin>>art[i][j];sum+=art[i][j];}
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){cin>>sci[i][j];sum+=sci[i][j];}
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){cin>>exart[i][j];sum+=exart[i][j];}
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){cin>>exsci[i][j];sum+=exsci[i][j];}
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            add(s,f(i,j),art[i][j]),add(f(i,j),s,0);
            add(f(i,j),t,sci[i][j]),add(t,f(i,j),0);
        }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            add(s,f_art(i,j),exart[i][j]),add(f_art(i,j),s,0);
            add(f_sci(i,j),t,exsci[i][j]),add(t,f_sci(i,j),0);
            for(int k=0;k<5;k++){
                int tx=i+dx[k],ty=j+dy[k];
                if(tx>=1&&tx<=n&&ty>=1&&ty<=m){
                    add(f_art(i,j),f(tx,ty),INF),add(f(tx,ty),f_art(i,j),0);
                    add(f(tx,ty),f_sci(i,j),INF),add(f_sci(i,j),f(tx,ty),0);
                }
            }
        }
    }
    int tmp;
    while(bfs()){
        while(tmp=dinic(s,INF)) sum-=tmp;
    }
    cout<<sum;
}