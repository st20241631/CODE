#include <bits/stdc++.h>
using namespace std;
const int N=1000000;
int w[N];
struct node{
    int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
    a[++cnt]=node{v,first[u]};
    first[u]=cnt;
}
int n,sum;
int ans=0;
set<int> s;
int depth[N];
void dfs(int u,int fa){
    depth[u]=depth[fa]+w[u];
    s.insert(depth[u]);
    if(s.count(depth[u]-sum))ans++;
    for(int i=first[u];i;i=a[i].nex)dfs(a[i].v,u);
    s.erase(depth[u]);
}
int main(){
    cin>>n>>sum;
    for(int i=1;i<=n;i++)cin>>w[i];
    for(int i=1;i<n;i++){
        int x,y;
        cin>>x>>y;
        add(x,y);
    }
    s.insert(0);
    dfs(1,0);
    cout<<ans;
}