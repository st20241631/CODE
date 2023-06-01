#include<bits/stdc++.h>
const int MAX = 1e9,N=400050;
using namespace std;
struct Node {
    int v, w, nex;
} a[N << 1];
int first[N], cnt=1;
void add(int u, int v, int w) {
    a[++cnt]=Node{v,w,first[u]};
    first[u]=cnt;
}
void insert(int u, int v, int w) {add(u, v, w), add(v, u, 0);}
int now[N];
int d[N], s, t, _s, _t;
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
int Dinic() {
    int ans = 0,tmp;
    while(bfs()){
        while(tmp=dinic(s,MAX)) ans+=tmp;
    }
    return ans;
}
int num[N], ans;
void addl(int u, int v, int l, int r) {
    if(l < r) insert(u, v, r - l);
    num[u] -= l, num[v] += l;
}
map<int, int> mpx, mpy;
int n, m, red, black;
int tot, Min[N], f[N], sum[N], id[N];
int main() {
    cin>>n>>m>>red>>black;
    int flag = 0;
    if(red > black) swap(red, black), flag = 1;
    for(int i = 1; i <= n; i ++) {
        int x, y;
        cin>>x>>y;
        if(!mpx[x]) mpx[x] = ++ tot;
        if(!mpy[y]) mpy[y] = ++ tot, f[tot] = 1;
        sum[mpx[x]] ++, sum[mpy[y]] ++;
        insert(mpx[x], mpy[y], 1);
        id[i] = cnt;
    }
    for(int i = 1; i <= tot; i ++) Min[i] = MAX;
    while(m --) {
        int op, x, y;
        cin>>op>>x>>y;
        if(op == 1) {x = mpx[x];if(!x) continue;Min[x] = min(Min[x], y);}
        else {x = mpy[x];if(!x) continue;Min[x] = min(Min[x], y);}
    }
    _s = tot + 1, _t = _s + 1, s = _t + 1, t = s + 1;
    for(int i = 1; i <= tot; i ++) {
        int tmp = min(Min[i], sum[i]);
        int l = (sum[i] - tmp + 1) / 2, r = (sum[i] + tmp) / 2;
        if(l > r) {cout<<-1; return 0; }
        if(!f[i]) addl(_s, i, l, r);
        else addl(i, _t, l, r);
    }
    for(int i = 1; i <= _t; i ++) {
        if(num[i] > 0) ans += num[i], insert(s, i, num[i]);
        if(num[i] < 0) insert(i, t, - num[i]);
    }
    insert(_t, _s, MAX);
    if(Dinic()!=ans) {cout<<-1;return 0;}
    s=_s,t=_t;
    long long tmp = Dinic() + a[cnt].w;
    cout<<tmp*red+(n-tmp)*black<<"\n";
    for(int i = 1; i <= n; i ++) {
        if(a[id[i]].w ^ flag) cout<<"r";
        else cout<<"b";
    }
    return 0;
}