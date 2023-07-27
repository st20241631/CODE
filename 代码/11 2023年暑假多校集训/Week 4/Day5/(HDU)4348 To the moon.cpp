#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAX=1e5+7,mod=1e9+7,inf=0x3f3f3f3f;
int n,m,root[MAX],tot;
int a[MAX];
struct node{
    int l,r,val,lazy;
}tree[MAX*32];

int clone(int k){
    ++tot;
    tree[tot]=tree[k];
    return tot;
}
void pushup(int u,int l,int r){tree[u].val=tree[tree[u].l].val+tree[tree[u].r].val+tree[u].lazy*(r-l+1);}

int build(int k,int l,int r){
    k=++tot;
    tree[k].val=tree[k].lazy=0;
    if(l==r){
        tree[k].val=a[l];return k;
    }
    int mid=(l+r)>>1;
    tree[k].l=build(tree[k].l,l,mid);
    tree[k].r=build(tree[k].r,mid+1,r);
    pushup(k,l,r);
    return k;
}

int update(int k,int old,int l,int r,int x,int y,int val){
    k=clone(old);
    if(x<=l&&r<=y){
        tree[k].lazy+=val;
        tree[k].val+=val*(r-l+1);
        return k;
    }
    int mid=(l+r)>>1;
    if(x<=mid) tree[k].l=update(tree[k].l,tree[old].l,l,mid,x,y,val);
    if(y>=mid+1) tree[k].r=update(tree[k].r,tree[old].r,mid+1,r,x,y,val);
    pushup(k,l,r);
    return k;
}

int query(int k,int l,int r,int x,int y,int val){
    if(x<=l&&r<=y){return tree[k].val+val*(r-l+1);}
    int ans=0;
    int mid=(l+r)>>1;
    if(x<=mid) ans+=query(tree[k].l,l,mid,x,y,val+tree[k].lazy);
    if(y>mid) ans+=query(tree[k].r,mid+1,r,x,y,val+tree[k].lazy);
    return ans;
}
signed main(){
    while(cin>>n>>m){
        tot=0;
        int time=0;
        for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
        root[0]=build(root[0],1,n);
        for(int i=1;i<=m;i++){
            char op[2];
            cin>>op;
            if(op[0]=='C'){
                int l,r,d;
                scanf("%lld%lld%lld",&l,&r,&d);
                ++time;
                root[time]=update(root[time],root[time-1],1,n,l,r,d);
            }
            else if(op[0]=='Q'){
                int l,r;
                scanf("%lld%lld",&l,&r);
                printf("%lld\n",query(root[time],1,n,l,r,0));
            }
            else if(op[0]=='H'){
                int l,r,t;
                scanf("%lld%lld%lld",&l,&r,&t);
                printf("%lld\n",query(root[t],1,n,l,r,0));
            }
            else scanf("%lld",&time);
        }
    }
    return 0;
}