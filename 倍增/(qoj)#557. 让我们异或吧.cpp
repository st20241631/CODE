#include <bits/stdc++.h>
using namespace std;
const int N=500010;
struct Node {
    int v,nex,w;
} a[N];
int first[N],cnt;
void add(int u,int v,int w) {
    a[++cnt]=Node{v,first[u],w};
    first[u]=cnt;
}

int dis[N];
void dfs(int u){
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(!dis[v]){
            dis[v]=dis[u]^a[i].w;
            dfs(v);
        }
    }
}
int main(){
    int n,q;
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        add(u,v,w);
        add(v,u,w);
    }
    dfs(1);
    cin>>q;
    for(int i=1;i<=q;i++){
        int u,v;
        cin>>u>>v;
        cout<<(dis[u]^dis[v])<<"\n";
    }

}