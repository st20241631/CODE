#include <bits/stdc++.h>

using namespace std;
struct node{
    int v,nex;
} a[1000000];
int first[1000000],cnt=1;

void add(int u,int v){
    a[++cnt]=node{v,first[u]};
    first[u]=cnt;
}

bool vis[10000000];
vector<int> q;

void dfs(int x){
    for(int i=first[x];i;i=first[x]){
        first[x]=a[i].nex;
        if(vis[i]) continue;
        vis[i]=vis[i^1]=1;
        int v=a[i].v;
        dfs(v);
    }
    q.push_back(x);
}

stack<int> s;
bool vis2[10000000];

int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        add(u,v);
        add(v,u);
    }
    dfs(1);
    for(int now: q){
        if(vis2[now]){
            cout<<now<<" ";
            while(s.top()!=now){
                cout<<s.top()<<" ";
                vis2[s.top()]=0;
                s.pop();
            }
            cout<<"\n";
        }else{
            vis2[now]=1;
            s.push(now);
        }
    }
}