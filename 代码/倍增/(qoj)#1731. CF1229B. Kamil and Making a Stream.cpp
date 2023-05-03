#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1000000,mod=1e9+7;
struct node{
    int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
    a[++cnt]=node{v,first[u]};
    first[u]=cnt;
}
int w[N];
vector<pair<int,int> > v[N];
void dfs(int u,int fa){
    if(fa){
        for(auto i:v[fa]){
            int tmp=__gcd(i.first,w[u]);
            if(v[u].empty()||v[u].back().first!=tmp) v[u].push_back(make_pair(tmp,i.second));
            else v[u].back().second+=i.second;
        }
    }
    if(v[u].empty()||v[u].back().first!=w[u]) v[u].push_back(make_pair(w[u],1));
    else v[u].back().second++;
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==fa) continue;
        dfs(v,u);
    }
}
signed main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)cin>>w[i];
    for(int i=1;i<n;i++){
        int x,y;
        cin>>x>>y;
        add(x,y),add(y,x);
    }
    dfs(1,0);
    int ans=0;
    for(int i=1;i<=n;i++)for(auto j:v[i])ans=(ans+j.first*j.second)%mod;
    cout<<ans;
}