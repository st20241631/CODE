#include <bits/stdc++.h>
using namespace std;
const int N=1000000;
struct node{
    int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
    a[++cnt]=node{v,first[u]};
    first[u]=cnt;
}
int depth[N];
double ans=0;
void dfs(int u,int dad){
    depth[u]=depth[dad]+1;
    ans+=1.0/depth[u];
    for(int i=first[u];i;i=a[i].nex)if(a[i].v!=dad) dfs(a[i].v,u);
}
int main(){
    int n;
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        add(u,v),add(v,u);
    }
    dfs(1,0);
    printf("%.20lf",ans);
}