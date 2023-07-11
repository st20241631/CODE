#include <bits/stdc++.h>

using namespace std;
const int N=1e5+10;
struct node{
    int v,nex;
}a[N*2];
int first[N],cnt;
void add(int u,int v){
    a[++cnt]={v,first[u]};
    first[u]=cnt;
}
int dfn[N],low[N],id[N],idx;
void dfs(int u){
    dfn[u]=++idx;
    id[dfn[u]]=u;
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(dfn[v]) continue;
        dfs(v);
    }
    low[u]=idx;
}

int n,q;
struct node2{
    int tree[N];
    int lowbit(int x) {return x&(-x);}
    void add(int x,int y){for(int i=x;i<=n;i+= lowbit(i)) tree[i]+=y;}
    int query(int x){
        int ans=0;
        for(int i=x;i>0;i-= lowbit(i))ans+=tree[i];
        return ans;
    }
}A,B;

void upd(int x,int y){
    A.add(dfn[x],y);
    A.add(low[x]+1,-y);
    B.add(dfn[x],(low[x]-dfn[x]+1)*y);
}
int query(int x){return (low[x]-dfn[x]+1)*A.query(dfn[x])+B.query(low[x])-B.query(dfn[x]);}
set<int> s[N];
int main(){
    cin>>n>>q;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        add(u,v);
        add(v,u);
    }
    dfs(1);
    while (q--){
        int opt;
        cin>>opt;
        if(opt==1){
            int x,c;
            cin>>x>>c;
            auto it=s[c].upper_bound(dfn[x]);
            if(it!=s[c].begin()&&low[id[*prev(it)]]>=low[x]) continue;
            while (it!=s[c].end()&&(*it)<=low[x]) {
                upd(id[*it], -1);
                s[c].erase(it++);
            }
            s[c].insert(dfn[x]);
            upd(x,1);
        }
        else {
            int x;
            cin>>x;
            cout<<query(x)<<"\n";
        }
    }
    return 0;
}