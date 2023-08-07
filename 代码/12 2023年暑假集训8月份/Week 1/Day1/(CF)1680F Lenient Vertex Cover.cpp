#include <bits/stdc++.h>

using namespace std;
const int N=1000050;

int n,m;
pair<int,int> a[N];
vector<pair<int,int> > G[N];
int cnt1[N],cnt2[N];
int color[N];
int fa[N];
bool vis[N];
int sum;
void dfs(int u,int dad,int col){
    color[u]=col;
    vis[u]=1;
    fa[u]=dad;
    for(auto now: G[u]){
        if(now.second!=dad){
            int v=now.first;
            int id=now.second;
            if(color[v]==-1)dfs(v,id,col^1);
            else{
                if(color[v]==(col^1)&&vis[v]){
                    cnt1[id]++;
                    cnt1[dad]++;
                    cnt1[fa[v]]--;
                }else if(color[v]==col&&vis[v]){
                    sum++;
                    cnt2[id]++;
                    cnt2[dad]++;
                    cnt2[fa[v]]--;
                }
            }
        }
    }
    vis[u]=0;
}

void dfs2(int u){
    vis[u]=1;
    for(auto now: G[u]){
        if(!vis[now.first]){
            int v=now.first;
            dfs2(v);
            cnt1[fa[u]]+=cnt1[fa[v]];
            cnt2[fa[u]]+=cnt2[fa[v]];
        }
    }
}

void dfs3(int u,int col){
    color[u]=col;
    for(auto now: G[u]){
        if(color[now.first]==-1){
            int v=now.first;
            dfs3(v,col^1);
        }
    }
}

void init(){
    sum=0;
    cin>>n>>m;
    for(int i=0;i<=n+10;i++)G[i].clear();
    for(int i=0;i<=m+10;i++) cnt1[i]=0;
    for(int i=0;i<=m+10;i++) cnt2[i]=0;
    for(int i=0;i<=n+10;i++) color[i]=-1;
    for(int i=0;i<=n+10;i++) vis[i]=0;
}

void solve(){
    init();
    for(int i=0;i<m;i++){
        int x,y;
        cin>>x>>y;
        a[i]={x-1,y-1};
        G[a[i].first].push_back({a[i].second,i});
        G[a[i].second].push_back({a[i].first,i});
    }
    dfs(0,-1,0);
    for(int i=0;i<=n+10;i++) vis[i]=0;
    dfs2(0);
    int x=-1,y=-1;
    if(sum){
        for(int i=0;i<m&&x==-1;i++)if(cnt2[i]==sum&&cnt1[i]==0) x=i;
        if(x==-1){
            cout<<"NO\n";
            return;
        }
        y=a[x].first,x=a[x].second;
        sort(G[x].begin(),G[x].end());
        sort(G[y].begin(),G[y].end());
        G[x].erase(lower_bound(G[x].begin(),G[x].end(),make_pair(y,-1)));
        G[y].erase(lower_bound(G[y].begin(),G[y].end(),make_pair(x,-1)));
    }
    for(int i=0;i<=n+10;i++) color[i]=-1;
    dfs3(0,1);
    int flag=(x==-1?0:color[x]^1);
    cout<<"YES\n";
    for(int i=0;i<n;i++) cout<<(color[i]^flag);
    cout<<"\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie();cout.tie();
    int T;
    cin>>T;
    while(T--)solve();
    return 0;
}