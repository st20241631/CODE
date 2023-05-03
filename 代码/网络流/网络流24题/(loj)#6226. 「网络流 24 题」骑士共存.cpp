#include <bits/stdc++.h>
#define int long long
const int MAX=1ll<<40;
using namespace std;
int s,t;
struct Node{
    int v,w,nex;
}a[1000000];
int cnt=1,first[500000];
void add(int u,int v,int w){
    a[++cnt]=Node{v,w,first[u]};
    first[u]=cnt;
}
void insert(int u,int v,int w){
    add(u,v,w),add(v,u,0);
}
int now[1000000];//弧优化（去掉已经遍历的边）
int d[1000000];//层次（深度）（代替vis）
int bfs(){
    memset(d, false,sizeof d);
    queue<int> q;
    q.push(s);
    d[s]=1;
    now[s]=first[s];
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=first[u];i;i=a[i].nex){
            int v=a[i].v;
            if(a[i].w&&!d[v]){
                q.push(v);
                now[v]=first[v];
                d[v]=d[u]+1;
                if(v==t) return 1;
            }
        }
    }
    return 0;
}
int dinic(int x,int val){
    if(x==t) return val;
    int have=val;
    for(int i=now[x];i&&have;i=a[i].nex){
        now[x]=i;
        int v=a[i].v;
        if(a[i].w&&d[v]==d[x]+1){
            int tmp= dinic(v,min(a[i].w,have));
            if(!tmp) d[v]=0;
            a[i].w-=tmp;
            a[i^1].w+=tmp;
            have-=tmp;
        }
    }
    return val-have;
}
int Dinic(){
    int sum=0,tmp;
    while(bfs()){
        while (tmp= dinic(s,MAX)) sum+=tmp;
    }
    return sum;
}
int n,m;
int f(int x,int y){return (x-1)*m+y;}
int dx[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};
bool flag[1000][1000];
main(){
    int tmp;
    cin>>n>>tmp;
    s=n*n+1,t=n*n+2;
    m=n;
    for(int i=1;i<=tmp;i++){
        int x,y;
        cin>>x>>y;
        flag[x][y]= true;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(flag[i][j]) continue;
            if((i+j)&1){
                insert(s,f(i,j),1);
                for(int k=0;k<8;k++){
                    int tx=i+dx[k],ty=j+dy[k];
                    if(flag[tx][ty]||tx<1||ty<1||tx>n||ty>m) continue;
                    insert(f(i,j),f(tx,ty),1);
                }
            }
            else insert(f(i,j),t,1);
        }
    }
    cout<<n*m-tmp-Dinic();
}