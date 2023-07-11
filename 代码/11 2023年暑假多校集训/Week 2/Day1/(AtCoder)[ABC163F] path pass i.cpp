#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2*1e5+10;
int color[N];
struct node{
    int v,nex;
}a[N*2];
int first[N],cnt;
void add(int u,int v){
    a[++cnt]={v,first[u]};
    first[u]=cnt;
}
int ans[N];
int f(int x){
    return x*(x+1)/2;
}

int siz[N];
int sum[N];
void dfs(int u,int dad){
    siz[u]=1;
    int tmp1=sum[color[u]];
    int tmp2=color[u];
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==dad) continue;
        int k=sum[tmp2];
        dfs(v,u);
        siz[u]+=siz[v];
        ans[tmp2]-=f(siz[v]-(sum[tmp2]-k));
    }
    sum[tmp2]=tmp1+siz[u];
    return;
}
signed main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)cin>>color[i];
    for(int i=1;i<=n-1;i++){
        int u,v;
        cin>>u>>v;
        add(u,v);
        add(v,u);
    }
    for(int i=1;i<=n;i++)ans[i]=f(n);
    dfs(1,0);
    for(int i=1;i<=n;i++){
        cout<<ans[i]-f(n-sum[i])<<"\n";
    }
}