#include <bits/stdc++.h>
using namespace std;
const int N=200005;
struct node{
    int v,nex;
}a[N*2];
int first[N],cnt;
void add(int u,int v){
    a[++cnt]={v,first[u]};
    first[u]=cnt;
}
int dep[N];
int MAX;
void dfs(int u,int dad){
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==dad) continue;
        dep[v]=dep[u]+1;
        if(dep[v]>dep[MAX]) MAX=v;
        dfs(v,u);
    }
}
int main(){
    int n;
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        add(u,v);
        add(v,u);
    }
    dep[1]=1;
    dfs(1,0);
    dep[MAX]=1;
    dfs(MAX,0);
    if((dep[MAX]%3)==2) puts("Second");
    else puts("First");
}