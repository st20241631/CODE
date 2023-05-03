#include <bits/stdc++.h>
const int MAX=1<<30;
using namespace std;
int s,t;
struct Node{
    int v,w,nex,val;
}a[1000000];
int cnt=1,first[1000000];
void add(int u,int v,int w,int val){
    a[++cnt]=Node{v,w,first[u],val};
    first[u]=cnt;
}
void insert(int u,int v,int w,int val){
    add(u,v,w,val),add(v,u,0,-val);
}

bool vis[1000000];
int now[1000000];
int dis[1000000];
int spfa(){
    memset(dis,0x3f,sizeof dis);
    for(int i=0;i<1000000;i++)dis[i]=-0x3f3f3f3f;
    queue<int> q;
    q.push(s);
    dis[s]=0;
    vis[s]= true;
    now[s]=first[s];
    while(!q.empty()){
        int u=q.front();
        q.pop();
        vis[u]=false;
        for(int i=first[u];i;i=a[i].nex){
            if(a[i].w){
                int v=a[i].v;
                if(dis[v]<dis[u]+a[i].val){
                    now[v]=first[v];
                    dis[v]=dis[u]+a[i].val;
                    if(!vis[v]) q.push(v),vis[v]=true;
                }
            }
        }
    }
    if(dis[t]==-0x3f3f3f3f)return 0;
    return 1;
}
int dinic(int x,int val){
    if(x==t) return val;
    int have=val;
    vis[x]=true;
    for(int i=now[x];i&&have;i=a[i].nex){
        now[x]=i;
        int v=a[i].v;
        if(!vis[v]&&a[i].w&&dis[v]==dis[x]+a[i].val){
            int tmp= dinic(v,min(a[i].w,have));
            if(!tmp) dis[v]=0;
            a[i].w-=tmp;
            a[i^1].w+=tmp;
            have-=tmp;
        }
    }
    vis[x]=false;
    return val-have;
}
int ans1,ans2;
void Dinic(){
    int tmp;
    while(spfa()){
        while (tmp= dinic(s,MAX)) ans1+=tmp,ans2+=tmp*dis[t];
    }
}
int n,m;
string name[100000];
map<string,int> id;
void print(int u){
    if(u<=n)cout<<name[u]<<endl;
    for(int i=first[u];i;i=a[i].nex) {
        if (a[i].v != s && a[i].v != t && a[i | 1].w) {
            a[i | 1].w = 0;
            print(a[i].v);
        }
    }
}
main(){
    cin>>n>>m;
    s=201,t=202;
    insert(s,1,2,0);
    insert(n,t,2,0);
    for(int i=1;i<=n;i++) {
        cin>>name[i];
        id[name[i]]=i;
    }
    for(int i=2;i<n;i++)insert(i,i+n,1,1);
    for(int i=1;i<=m;i++){
        string u,v;
        cin>>u>>v;
        if(id[u]>id[v])swap(u,v);
        insert(id[u]+(u==name[1]?0:n),id[v],MAX,0);
    }
    Dinic();
    if(ans1<2){
        cout<<"No Solution!";
        return 0;
    }
    cout<<ans2+2<<endl;
    if(!ans2){
        cout<<name[1]<<"\n"<<name[n]<<"\n"<<name[1];
        return 0;
    }
    print(1);
    return 0;
}