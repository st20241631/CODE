#include <bits/stdc++.h>

using namespace std;
const int MAX=1000000;
struct node{
    int v,nex;
}a[MAX];
int first[MAX],cnt;
void add(int u,int v){
    a[++cnt]={v,first[u]};
    first[u]=cnt;
}
int w[MAX];
int n;

int fa[MAX],son[MAX],dep[MAX],siz[MAX];
void dfs1(int u,int dad){
    fa[u]=dad;
    dep[u]=dep[dad]+1;
    siz[u]=1;
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==dad) continue;
        dfs1(v,u);
        siz[u]+=siz[v];
        if(siz[v]>siz[son[u]]) son[u]=v;
    }
}

int top[MAX],id[MAX],seq[MAX],tot;
void dfs2(int u){
    if(son[u]){
        int v=son[u];
        id[v]=++tot;
        seq[id[v]]=v;
        top[v]=top[u];
        dfs2(v);
    }
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(!top[v]){
            id[v]=++tot;
            seq[id[v]]=v;
            top[v]=v;
            dfs2(v);
        }
    }
}

int tree1[MAX<<2]/*最大权值*/,tree2[MAX<<2]/*权值和*/;
void build(int k,int l,int r){
    if(l==r){
        tree1[k]=tree2[k]=w[seq[l]];
        return;
    }
    int mid=(l+r)>>1;
    build(k<<1,l,mid);
    build(k<<1|1,mid+1,r);
    tree1[k]=max(tree1[k<<1],tree1[k<<1|1]);
    tree2[k]=tree2[k<<1]+tree2[k<<1|1];
}
void update(int k,int l,int r,int x,int y){
    if(l>r) return;
    if(l==r&&l==x){
        tree1[k]=tree2[k]=y;
        return;
    }
    int mid=(l+r)>>1;
    if(x>=l&&x<=mid) update(k<<1,l,mid,x,y);
    if(x>=mid+1&&x<=r) update(k<<1|1,mid+1,r,x,y);
    tree1[k]=max(tree1[k<<1],tree1[k<<1|1]);
    tree2[k]=tree2[k<<1]+tree2[k<<1|1];
}

int ans1,ans2;
void query(int k,int l,int r,int x,int y){
    if(x>r||y<l) return;
    if(x<=l&&y>=r){
        ans1+=tree2[k];
        ans2=max(ans2,tree1[k]);
        return;
    }
    int mid=(l+r)>>1;
    if(x<=mid) query(k<<1,l,mid,x,y);
    if(y>=mid+1) query(k<<1|1,mid+1,r,x,y);
}

void ask(int x,int y){
    int fx=top[x],fy=top[y];
    while (fx!=fy){
        if(dep[fx]<dep[fy]){
            swap(x,y);
            swap(fx,fy);
        }
        query(1,1,n,id[fx],id[x]);
        x=fa[fx];
        fx=top[x];
    }
    if(dep[x]>dep[y]) swap(x,y);
    query(1,1,n,id[x],id[y]);
}

int main(){
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        add(u,v);
        add(v,u);
    }
    for(int i=1;i<=n;i++) cin>>w[i];
    dfs1(1,0);
    id[1]=++tot;
    seq[id[1]]=1;
    top[1]=1;
    dfs2(1);
    build(1,1,n);

    int q;
    cin>>q;
    while (q--){
        string s;
        cin>>s;
        int x,y;
        cin>>x>>y;
        ans1=0;
        ans2=-100000000;
        ask(x,y);
        if(s=="CHANGE")update(1,1,n,id[x],y);
        if(s=="QMAX") cout<<ans2<<"\n";
        if(s=="QSUM") cout<<ans1<<"\n";
    }
}