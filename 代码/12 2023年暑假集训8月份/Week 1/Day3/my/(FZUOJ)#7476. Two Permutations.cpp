#include<bits/stdc++.h>
using namespace std;
int rd(int x=0,char c=getchar()){while(!isdigit(c))c=getchar();while(isdigit(c))x=x*10+c-48,c=getchar();return x;}
const int N=3e5+5;
int n;
using ll=long long;
const ll mod=998244353;
int p[N],q[N],s[N<<1];
map<pair<int,int>,ll> mp;
ll dfs(int x,int y){
    if(mp.count({x,y}))return mp[{x,y}];
    auto&a=mp[{x,y}];
    a=0;
    if(x<n&&q[x+1]==s[x+y+1])a+=dfs(x+1,y);
    if(y<n&&p[y+1]==s[x+y+1])a+=dfs(x,y+1);
    a%=mod;
    return a;
}
void solve(){
    n=rd();
    mp.clear();
    for(int i=1;i<=n;i++)p[i]=rd();
    for(int i=1;i<=n;i++)q[i]=rd();
    for(int i=1;i<=n*2;i++)s[i]=rd();
    mp[{n,n}]=1;
    printf("%lld\n",dfs(0,0));
}
int main(){
    int t=rd();
    while(t--)solve();
    return 0;
}
