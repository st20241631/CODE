#include <bits/stdc++.h>
#define int unsigned long long
const int mod=51061;
using namespace std;
const int N=3e5+10;
int a[N];
int ch[N][2],fa[N];
int lazy[N];
int nroot(int x){return ch[fa[x]][0]==x||ch[fa[x]][1]==x;}
void pushr(int x){
    swap(ch[x][0],ch[x][1]);
    lazy[x]^=1;
}

int s[N],v[N],sz[N],lm[N],la[N];
void pushup(int x){
    s[x]=(s[ch[x][0]]+s[ch[x][1]]+v[x])%mod;
    sz[x]=sz[ch[x][0]]+sz[ch[x][1]]+1;
}
void pushm(int x,int c){
    s[x]=(s[x]*c)%mod;
    v[x]=(v[x]*c)%mod;
    lm[x]=(lm[x]*c)%mod;
    la[x]=(la[x]*c)%mod;
}
void pusha(int x,int c){
    s[x]=(s[x]+c*sz[x])%mod;
    v[x]=(v[x]+c)%mod;
    la[x]=(la[x]+c)%mod;
}
void pushdown(int x){
    if(lm[x]!=1){
        pushm(ch[x][0],lm[x]);
        pushm(ch[x][1],lm[x]);
        lm[x]=1;
    }
    if(la[x]){
        pusha(ch[x][0],la[x]);
        pusha(ch[x][1],la[x]);
        la[x]=0;
    }
    if(lazy[x]){
        if(ch[x][0]) pushr(ch[x][0]);
        if(ch[x][1]) pushr(ch[x][1]);
        lazy[x]=0;
    }
}


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
    int n,q;
    cin>>n>>q;
    for(int i=1;i<=n;i++) v[i]=sz[i]=lm[i]=1;
    for(int i=1;i<n;i++) {
        int u,v;
        cin>>u>>v;
        link(u,v);
    }
    while (q--){
        int u,v,k;
        char ch;
        cin>>ch;
        switch (ch) {
            case '+':
                cin>>u>>v>>k;
                split(u,v);
                pusha(v,k);
                break;
            case '-':
                cin>>u>>v;
                cut(u,v);
                cin>>u>>v;
                link(u,v);
                break;
            case '*':
                cin>>u>>v>>k;
                split(u,v);
                pushm(v,k);
                break;
            case '/':
                cin>>u>>v;
                split(u,v);
                cout<<s[v]<<"\n";
        }
    }
}