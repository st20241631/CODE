#include <bits/stdc++.h>
const int N = 1000000;
#define int long long
using namespace std;
struct node{
    int v, nex;
} a[N];
int cnt, first[N];
void add(int u, int v){
    a[++cnt] = {v, first[u]};
    first[u] = cnt;
}
int col[N];
int siz[N], son[N];
void dfs1(int u){
    siz[u] = 1;
    for (int i = first[u]; i; i = a[i].nex){
        int v = a[i].v;
        dfs1(v);
        siz[u] += siz[v];
        if (siz[v] > siz[son[u]])son[u] = v;
    }
}
set<int> s;
int sum;
void solve(int u, int SON){
    s.insert(u);
    auto now = s.lower_bound(u);
    if (now == s.begin()){
        if (next(now) != s.end()){
            int val = abs(*now - *next(now));
            sum += val * val;
        }
    }
    else if (next(now) == s.end()){
        if (now != s.begin()){
            int val = abs(*now - *prev(now));
            sum += val * val;
        }
    }
    else{
        int val=abs(*next(now)-*prev(now));
        sum-=val*val;
        val=abs(*now-*next(now));
        sum+=val*val;
        val=abs(*now-*prev(now));
        sum+=val*val;
    }
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v!=SON) solve(v,SON);
    }
}
int ans[N];
void dfs2(int u, int opt){
    for (int i = first[u]; i; i = a[i].nex){
        int v = a[i].v;
        if (v != son[u])
            dfs2(v, 0);
    }
    if (son[u])dfs2(son[u], 1);
    solve(u, son[u]);
    ans[u] = sum;
    if (!opt){
        s.clear();
        sum = 0;
    }
}
signed main(){
    int n;
    cin >> n;
   
    for (int i = 1; i < n; i++){
        int x;
        cin>>x;
        add(x,i+1);
    }
    dfs1(1);
    dfs2(1, 1);
    for (int i = 1; i <= n; i++){
        cout << ans[i] <<"\n";
    }
}