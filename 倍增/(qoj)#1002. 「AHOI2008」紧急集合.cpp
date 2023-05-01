#include<bits/stdc++.h>
#define MAXN 500005
using namespace std;
int n,m,first[MAXN],cnt,f[MAXN][20],height[MAXN];
struct bian {
    int v,nex;
} a[2*MAXN];
void add(int u,int v) {
    a[++cnt].v=v;
    a[cnt].nex=first[u];
    first[u]=cnt;
}
void dfs(int u,int v) {
    f[u][0]=v;
    height[u]=height[v]+1;
    for(int i=1; i<=log2(n); i++) {
        f[u][i]=f[f[u][i-1]][i-1];
    }
    for(int i=first[u]; i; i=a[i].nex) {
        if(a[i].v!=v)
            dfs(a[i].v,u);
    }
    return;
}
int LCA(int x,int y) {
    if(height[x]<height[y])swap(x,y);
    for(int i=log2(n); i>=0; i--) {
        if(height[f[x][i]]>=height[y])
            x=f[x][i];
    }
    if(x==y)return x;
    for(int i=log2(n); i>=0; i--) {
        if(f[x][i]!=f[y][i]) {
            x=f[x][i];
            y=f[y][i];
        }
    }
    return f[x][0];
}
int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n-1;i++){
        int a,b;
        scanf("%d%d",&a,&b);
        add(a,b);
        add(b,a);
    }
    dfs(1,0);
    for(int i=1;i<=m;i++){
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        int t1=LCA(a,b);
        int t2=LCA(a,c);
        int t3=LCA(b,c);
        if(t1==t2)printf("%d ",t3);
        else if(t1==t3)printf("%d ",t2);
        else if(t2==t3)printf("%d ",t1);
        printf("%d\n",height[a]+height[b]+height[c]-height[t1]-height[t2]-height[t3]);
    }
    return 0;
}