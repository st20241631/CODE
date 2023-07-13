#include <bits/stdc++.h>

using namespace std;
const int N=1e6+10;
int tree[N][30],cnt;
int fa[N];

int query[N],tot;
void insert(string s){
    int now=0;
    int siz=s.size();
    for(int i=0;i<siz;i++){
        if(s[i]>='a'&&s[i]<='z'){
            if(!tree[now][s[i]-'a']) tree[now][s[i]-'a']=++cnt,fa[cnt]=now;
            now=tree[now][s[i]-'a'];
        }
        else if(s[i]=='P')query[++tot]=now;
        else now=fa[now];
    }
}
struct node{
    int v,nex;
}a[N];
int first[N],sum;
void add(int u,int v){
    a[++sum]={v,first[u]};
    first[u]=sum;
}

int fail[N];
void build(){
    queue<int> q;
    for(int i=0;i<26;i++){
        if(tree[0][i]) q.push(tree[0][i]);
    }
    while (!q.empty()){
        int now=q.front();
        q.pop();
        for(int i=0;i<26;i++){
            if(tree[now][i]){
                fail[tree[now][i]]=tree[fail[now]][i];
                q.push(tree[now][i]);
            }
            else tree[now][i]=tree[fail[now]][i];
        }
    }
    for(int i=1;i<=cnt;i++){
        add(i,fail[i]);
        add(fail[i],i);
    }
}

int dfn[N],low[N],idx;
void dfs(int u,int dad){
    dfn[u]=++idx;
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==dad) continue;
        dfs(v,u);
    }
    low[u]=idx;
}

int bit[N];
int lowbit(int x) {return x&(-x);}
void update(int x,int y){
    for(int i=x;i<=idx;i+= lowbit(i))bit[i]+=y;
}
int ask(int x){
    int ans=0;
    for(int i=x;i>0;i-= lowbit(i))ans+=bit[i];
    return ans;
}

struct node2{
    int val,id;
};
vector<node2> G[N];
int ans[N];

int main(){
    string s;
    cin>>s;
    insert(s);
    build();
    dfs(0,0);
    int m;
    cin>>m;
    for(int i=1;i<=m;i++){
        int x,y;
        cin>>x>>y;
        G[y].push_back({x,i});
    }
    int siz=s.size();
    int now=0;
    int tmp=0;
    for(int i=0;i<siz;i++){
        if(s[i]=='P'){
            tmp++;
            for(auto j:G[tmp]){
                int val=j.val,id=j.id;
                ans[id]= ask(low[query[val]])- ask(dfn[query[val]]-1);
            }
        }
        if(s[i]=='B'){
            update(dfn[now],-1);
            now=fa[now];
        }
        if(s[i]>='a'&&s[i]<='z'){
            now=tree[now][s[i]-'a'];
            update(dfn[now],1);
        }
    }
    for(int i=1;i<=m;i++) cout<<ans[i]<<"\n";
}