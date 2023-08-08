#include <bits/stdc++.h>
using namespace std;
const int N=3e5+10;
int a[N];
int ch[N][2],fa[N];
int lazy[N];
int val[N];
int nroot(int x){return ch[fa[x]][0]==x||ch[fa[x]][1]==x;}
void pushr(int x){
    swap(ch[x][0],ch[x][1]);
    lazy[x]^=1;
}
void pushdown(int x){
    if(lazy[x]){
        if(ch[x][0]) pushr(ch[x][0]);
        if(ch[x][1]) pushr(ch[x][1]);
        lazy[x]=0;
    }
}
void pushup(int x){val[x]=val[ch[x][0]]^val[ch[x][1]]^a[x];}
void rotate(int x){
    int y=fa[x],z=fa[y];
    int k=(ch[y][1]==x);
    if(nroot(y))ch[z][ch[z][1]==y]=x;
    fa[x]=z;
    fa[y]=x;
    ch[y][k]=ch[x][!k];
    if(ch[x][!k]) fa[ch[x][!k]]=y;
    ch[x][!k]=y;
    pushup(y);
}
void pushall(int x){
    if(nroot(x)) pushall(fa[x]);
    pushdown(x);
}
void splay(int x){
    pushall(x);
    while(nroot(x)){
        int y=fa[x],z=fa[y];
        if(nroot(y)) rotate((ch[y][1]==x)^(ch[z][1]==y)?x:y);
        rotate(x);
    }
    pushup(x);
}
void access(int x){
    for(int y=0;x;y=x,x=fa[x]){
        splay(x);
        ch[x][1]=y;
        pushup(x);
    }
}
void makeroot(int x){
    access(x);
    splay(x);
    pushr(x);
}
void split(int x,int y){
    makeroot(x);
    access(y);
    splay(y);
}
int findroot(int x){
    access(x);
    splay(x);
    pushdown(x);
    while(ch[x][0]) x=ch[x][0],pushdown(x);
    splay(x);
    return x;
}
void link(int x,int y){
    makeroot(x);
    if(findroot(y)!=x) fa[x]=y;
}
void cut(int x,int y){
    makeroot(x);
    if(findroot(y)==x&&fa[y]==x&&!ch[y][0]){
        fa[y]=ch[x][1]=0;
        pushup(x);
    }
}
signed main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    while(m--){
        int opt,x,y;
        cin>>opt>>x>>y;
        switch(opt){
            case 0:
                split(x,y);
                cout<<val[y]<<"\n";
                break;
            case 1:
                link(x,y);
                break;
            case 2:
                cut(x,y);
                break;
            case 3:
                splay(x);
                a[x]=y;
        }
    }
    return 0;
}