#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAX=1000000,mod=201314;

struct node{
    int v,nex;
}a[MAX];
int first[MAX],cnt;
void add(int u,int v){
    a[++cnt]={v,first[u]};
    first[u]=cnt;
}
int n,m;

int fa[MAX],siz[MAX],son[MAX],dep[MAX];
void dfs1(int u,int dad){
    fa[u]=dad;
    siz[u]=1;
    dep[u]=dep[dad]+1;
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==dad) continue;
        dfs1(v,u);
        siz[u]+=siz[v];
        if(siz[v]>siz[son[u]]) son[u]=v;
    }
}
int top[MAX],id[MAX],tot;
void dfs2(int u){
    if(son[u]){
        int v=son[u];
        id[v]=++tot;
        top[v]=top[u];
        dfs2(v);
    }
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(!top[v]) {
            id[v]=++tot;
            top[v]=v;
            dfs2(v);
        }
    }
}

int tree[MAX<<2],lazy[MAX<<2];
void pushdown(int k,int l,int r){
    if(lazy[k]){
        lazy[k<<1]+=lazy[k];
        lazy[k<<1|1]+=lazy[k];
        int mid=(l+r)>>1;
        tree[k<<1]+=(mid-l+1)*lazy[k];
        tree[k<<1|1]+=(r-mid)*lazy[k];
        lazy[k]=0;
    }
}
void update(int k,int l,int r,int x,int y){
    if(x<=l&&y>=r){
        lazy[k]+=1;
        tree[k]+=(r-l+1);
        return;
    }
    pushdown(k,l,r);
    int mid=(l+r)>>1;
    if(x<=mid) update(k<<1,l,mid,x,y);
    if(y>=mid+1) update(k<<1|1,mid+1,r,x,y);
    tree[k]=tree[k<<1]+tree[k<<1|1];
}
int query(int k,int l,int r,int x,int y){
    if(x<=l&&y>=r)return tree[k];
    pushdown(k,l,r);
    int ans=0;
    int mid=(l+r)>>1;
    if(x<=mid) ans+= query(k<<1,l,mid,x,y);
    if(y>=mid+1) ans+= query(k<<1|1,mid+1,r,x,y);
    return ans;
}

void modify(int x,int y){
    int fx=top[x],fy=top[y];
    while (fx!=fy){
        if(dep[fx]<dep[fy]){
            swap(x,y);
            swap(fx,fy);
        }
        update(1,1,n,id[fx],id[x]);
        x=fa[fx];
        fx=top[x];
    }
    if(dep[x]>dep[y]) swap(x,y);
    update(1,1,n,id[x],id[y]);
}

int ask(int x,int y){
    int ans=0;
    int fx=top[x],fy=top[y];
    while (fx!=fy){
        if(dep[fx]<dep[fy]){
            swap(x,y);
            swap(fx,fy);
        }
        ans+=query(1,1,n,id[fx],id[x]);
        ans%=mod;
        x=fa[fx];
        fx=top[x];
    }
    if(dep[x]>dep[y]) swap(x,y);
    ans+=query(1,1,n,id[x],id[y]);
    ans%=mod;
    return ans;
}

struct node2{
    int x,val,id,opt;
}b[MAX];
bool cmp(node2 x,node2 y){
    return x.x<y.x;
}
int sum;
int ans[MAX];
signed main(){
    cin>>n>>m;
    for(int i=2;i<=n;i++){
        int u;
        cin>>u;
        u++;
        add(u,i);
        add(i,u);
    }
    dfs1(1,0);
    id[1]=++tot;
    top[1]=1;
    dfs2(1);
    for(int i=1;i<=m;i++){
        int l,r,z;
        cin>>l>>r>>z;
        l++,r++,z++;
        b[++sum]={l-1,z,i,-1};
        b[++sum]={r,z,i,1};
    }
    sort(b+1,b+sum+1,cmp);

    int now=1;
    for(int i=1;i<=sum;i++){
        while (now<=b[i].x) modify(1,now++);
        ans[b[i].id]+=b[i].opt*ask(1,b[i].val);
        ans[b[i].id]+=mod;
        ans[b[i].id]%=mod;
    }
    for(int i=1;i<=m;i++)cout<<ans[i]<<"\n";
}