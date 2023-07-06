#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=3e6+5,K=5e5;//K用来区分第一棵树和第二棵树
struct node{
    int v,nex,w;
}a[MAXN];
int first[MAXN],cnt;
void add(int u,int v,int w){
    a[++cnt]={v,first[u],w};
    first[u]=cnt;
}
int tree[MAXN];
void build(int k,int l,int r){
    if(l==r){
        tree[l]=k;
        return;
    }
    int mid=(l+r)>>1;
    add(k,k<<1,0),add(k,k<<1|1,0);
    add((k<<1)+K,k+K,0),add((k<<1|1)+K,k+K,0);
    build(k<<1,l,mid);
    build(k<<1|1,mid+1,r);
}
void modify(int k,int l,int r,int x,int y,int id,int w,int opt){
    if(l>=x&&r<=y){
        if(opt==2)add(id+K,k,w);
        else add(k+K,id,w);
        return;
    }
    int mid=(l+r)>>1;
    if(x<=mid)modify(k<<1,l,mid,x,y,id,w,opt);
    if(y>mid)modify(k<<1|1,mid+1,r,x,y,id,w,opt);
}
struct node2{
    int id,val;
    bool operator<(const node2& b) const{
        return val>b.val;
    }
};
int dis[MAXN];
bool vis[MAXN];
void dij(int s){
    priority_queue<node2> q;
    memset(dis,0x3f,sizeof dis);
    memset(vis, false,sizeof vis);
    dis[s]=0;
    q.push({s,0});
    while (!q.empty()){
        node2 now=q.top();
        q.pop();
        int u=now.id;
        if(vis[u]) continue;
        vis[u]=true;
        for(int i=first[u];i;i=a[i].nex){
            int v=a[i].v;
            if(dis[v]>dis[u]+a[i].w){
                dis[v]=dis[u]+a[i].w;
                q.push({v,dis[v]});
            }
        }
    }
}
signed main(){
    int n,q,s;
    cin>>n>>q>>s;
    build(1,1,n);
    for(int i=1;i<=n;i++){
        add(tree[i],tree[i]+K,0);
        add(tree[i]+K,tree[i],0);
    }
    for(int i=1;i<=q;i++){
        int opt;
        cin>>opt;
        if(opt==1){
            int u,v,w;
            cin>>u>>v>>w;
            add(tree[u]+K,tree[v],w);
        }
        else {
            int v,l,r,w;
            cin>>v>>l>>r>>w;
            modify(1, 1, n,l,r,tree[v],w,opt);
        }
    }
    dij(tree[s]+K);
    for(int i=1;i<=n;i++){
        if(dis[tree[i]]==0x3f3f3f3f3f3f3f3fll) cout<<-1<<" ";
        else cout<<dis[tree[i]]<<" ";
    }

}