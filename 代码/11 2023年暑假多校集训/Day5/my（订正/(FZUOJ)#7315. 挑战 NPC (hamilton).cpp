#include <bits/stdc++.h>
#define int long long
const int MAX=1ll<<40;
using namespace std;
int n,m,s,t;
struct Node{
    int v,w,nex;
}a[1000000];
int cnt=1,first[500000];
void add(int u,int v,int w){
    a[++cnt]=Node{v,w,first[u]};
    first[u]=cnt;
}
int now[1000000];//弧优化（去掉已经遍历的边）
int d[1000000];//层次（深度）（代替vis）
int bfs(){
    memset(d, false,sizeof d);
    queue<int> q;
    q.push(s);
    d[s]=1;
    now[s]=first[s];
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=first[u];i;i=a[i].nex){
            int v=a[i].v;
            if(a[i].w&&!d[v]){
                q.push(v);
                now[v]=first[v];
                d[v]=d[u]+1;
                if(v==t) return 1;
            }
        }
    }
    return 0;
}
int ans;
int dinic(int x,int val){
    if(x==t) return val;
    int have=val;
    for(int i=now[x];i&&have;i=a[i].nex){
        now[x]=i;
        int v=a[i].v;
        if(a[i].w&&d[v]==d[x]+1){
            int tmp= dinic(v,min(a[i].w,have));
            if(!tmp) d[v]=0;
            a[i].w-=tmp;
            a[i^1].w+=tmp;
            have-=tmp;
        }
    }
    return val-have;
}
bool vis[1000000];
main(){
    cin>>n>>m;
    s=0,t=n*3+1;
    for(int i=1;i<=n;i++){
        add(s,i,1);
        add(i,s,0);
        add(i+n,t,1);
        add(t,i+n,0);
    }
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        add(u,v+n,1);
        add(v+n,u,0);
    }
    while (bfs()){
        int tmp;
        while (tmp= dinic(s,MAX)) ans+=tmp;
    }
    if(ans<n) {
        puts("NO");
        return 0;
    }
    cout<<"YES\n";
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            vector<int> G;
            int tmp=i;
            while (!vis[tmp]){
                vis[tmp]=1;
                for(int j=first[tmp];j;j=a[j].nex){
                    if(a[j].w==0){
                        int v=a[j].v;
                        if(v==s||v==t) continue;
                        tmp=v-n;
                        G.push_back(tmp);
                        break;
                    }
                }
            }
            cout<<G.size()<<" ";
            for(int j:G) cout<<j<<" ";
            cout<<"\n";
        }
    }
}