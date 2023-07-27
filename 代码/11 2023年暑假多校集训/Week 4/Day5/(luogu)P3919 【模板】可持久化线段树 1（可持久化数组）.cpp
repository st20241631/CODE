#include <bits/stdc++.h>

using namespace std;
const int MAX=5e7+10;
struct node{
    int l,r,val;
}tree[MAX];
int a[MAX];
int tot;
int clone(int x){  //复制节点
    tot++;
    tree[tot]=tree[x];
    return tot;
}
int build(int k,int l,int r){
    k=++tot;
    if(l==r){
        tree[k].val=a[l];
        return k;
    }
    int mid=(l+r)>>1;
    tree[k].l = build(tree[k].l,l,mid);
    tree[k].r = build(tree[k].r,mid+1,r);
    return k;
}
int update(int k,int l,int r,int x,int val){
    k= clone(k);
    if(l==r){
        tree[k].val=val;
        return k;
    }
    int mid=(l+r)>>1;
    if(x<=mid) tree[k].l= update(tree[k].l,l,mid,x,val);
    else tree[k].r= update(tree[k].r,mid+1,r,x,val);
    return k;
}
int query(int k,int l,int r,int x){
    if(l==r)return tree[k].val;
    int mid=(l+r)>>1;
    if(x<=mid) return query(tree[k].l,l,mid,x);
    else return query(tree[k].r,mid+1,r,x);
}

int root[MAX];
int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    root[0]= build(0,1,n);
    for(int i=1;i<=m;i++){
        int rt,opt,x;
        scanf("%d%d%d",&rt,&opt,&x);
        if(opt==1){
            int y;
            cin>>y;
            root[i]= update(root[rt],1,n,x,y);
        }
        else {
            cout<<query(root[rt],1,n,x)<<"\n";
            root[i]=root[rt];
        }
    }
}