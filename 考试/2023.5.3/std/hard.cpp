#include<bits/stdc++.h>
namespace my_std{
    using namespace std;
    #define pii pair<int,int>
    #define fir first
    #define sec second
    #define MP make_pair
    #define rep(i,x,y) for (int i=(x);i<=(y);i++)
    #define drep(i,x,y) for (int i=(x);i>=(y);i--)
    #define go(x) for (int i=head[x];i;i=edge[i].nxt)
    #define templ template<typename T>
    #define sz 202020
    typedef long long ll;
    typedef double db;
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    templ inline T rnd(T l,T r) {return uniform_int_distribution<T>(l,r)(rng);}
    templ inline bool chkmax(T &x,T y){return x<y?x=y,1:0;}
    templ inline bool chkmin(T &x,T y){return x>y?x=y,1:0;}
    templ inline void read(T& t)
    {
        t=0;char f=0,ch=getchar();double d=0.1;
        while(ch>'9'||ch<'0') f|=(ch=='-'),ch=getchar();
        while(ch<='9'&&ch>='0') t=t*10+ch-48,ch=getchar();
        if(ch=='.'){ch=getchar();while(ch<='9'&&ch>='0') t+=d*(ch^48),d*=0.1,ch=getchar();}
        t=(f?-t:t);
    }
    template<typename T,typename... Args>inline void read(T& t,Args&... args){read(t); read(args...);}
    void file()
    {
        #ifdef NTFOrz
        freopen("a.in","r",stdin);
        #endif
    }
    inline void chktime()
    {
        #ifdef NTFOrz
        cerr<<clock()/1000.0<<'\n';
        #endif
    }
    #ifdef mod
    ll ksm(ll x,int y){ll ret=1;for (;y;y>>=1,x=x*x%mod) if (y&1) ret=ret*x%mod;return ret;}
    ll inv(ll x){return ksm(x,mod-2);}
    #else
    ll ksm(ll x,int y){ll ret=1;for (;y;y>>=1,x=x*x) if (y&1) ret=ret*x;return ret;}
    #endif
}
using namespace my_std;

int n,m;
unordered_set<int>V[sz],_V[sz]; int leaf[sz];

int isleaf(int x){return (int)V[x].size()==1;}
int firstedge(int x){return *(V[x].begin());}
void deledge(int x,int y) {
    if (isleaf(x)) --leaf[y];
    if (isleaf(y)) --leaf[x];
    V[x].erase(y),V[y].erase(x);
    if (isleaf(x)) ++leaf[*(V[x].begin())];
    if (isleaf(y)) ++leaf[*(V[y].begin())];
}
void addedge(int x,int y) {
    if (isleaf(x)) --leaf[*(V[x].begin())];
    if (isleaf(y)) --leaf[*(V[y].begin())];
    V[x].insert(y),V[y].insert(x);
    if (isleaf(x)) ++leaf[y];
    if (isleaf(y)) ++leaf[x];
}

struct hh {
    int x;
    vector<int>leaves;
    vector<pii>two;
};

void work() {
    read(n,m);
    int x,y;
    while (m--) read(x,y),addedge(x,y),_V[x].insert(y),_V[y].insert(x);
    static int del[sz];
    stack<hh>S;
    drep(x,n,1) if (!del[x]&&!isleaf(x)) {
        vector<int>leaves,deled,real;
        auto tmp=V[x];
        for (auto v:tmp)
            if (isleaf(v)) leaves.push_back(v);
            else {
                deledge(x,v); deled.push_back(v);
                if (isleaf(v)&&leaf[firstedge(v)]>2) real.push_back(v);
            }
        if (!leaves.size()&&!real.size()) {
            addedge(x,deled[0]),addedge(x,deled[1]);
            continue;
        }
        hh state={x,leaves,{}};
        for (auto r:real) state.two.push_back(MP(r,firstedge(r))),deledge(r,firstedge(r));
        S.push(state);
        del[x]=1;
        for (auto l:leaves) del[l]=1;
        for (auto r:real) del[r]=1;
    }
    int cnt[2]={0,0};
    static int col[sz];
    rep(i,1,n) if (!del[i]) {
        assert(V[i].size()&&(int)V[i].size()<=2);
        int x,y;
        if (isleaf(i)) x=i;
        else {
            x=firstedge(i),y=i;
            while (!isleaf(x)&&x!=i) swap(x,y),x=*(V[y].begin())+*next(V[y].begin())-x;
        }
        vector<int>pt={x};
        int _start=x; y=x,x=firstedge(x);
        while (x!=_start) {
            pt.push_back(x);
            if (!isleaf(x)) swap(x,y),x=*(V[y].begin())+*next(V[y].begin())-x;
            else break;
        }
        rep(j,0,(int)pt.size()-1) col[pt[j]]=j&1,++cnt[j&1],del[pt[j]]=1;
        if (abs(cnt[0]-cnt[1])>1) rep(j,0,(int)pt.size()-1) col[pt[j]]=(j&1)^1,--cnt[j&1],++cnt[(j&1)^1];
        assert(abs(cnt[0]-cnt[1])<=1);
    }
    while (!S.empty()) {
        hh state=S.top(); S.pop();
        int x=state.x; auto leaves=state.leaves; auto two=state.two;
        int cc[2]={0,0};
        vector<int>vv[2];
        for (auto [r,rr]:two) cc[col[rr]]++,vv[col[rr]].push_back(r);
        if (cc[0]>cc[1]) col[x]=1;
        else if (cc[1]>cc[0]) col[x]=0;
        else col[x]=(cnt[0]>=cnt[1])^(leaves.size()==2u);
        ++cnt[col[x]];
        for (auto l:leaves) ++cnt[col[l]=col[x]^1];
        for (auto r:vv[col[x]]) ++cnt[col[r]=col[x]^1];
        for (auto r:vv[col[x]^1])
            if (cnt[col[x]]<cnt[col[x]^1]) ++cnt[col[r]=col[x]];
            else ++cnt[col[r]=col[x]^1];
        assert(abs(cnt[0]-cnt[1])<=1);
    }
    int w=0;
    rep(i,1,n) {
        int ok=0;
        for (auto v:_V[i]) if (col[v]!=col[i]) ok=1;
        assert(ok);
        w+=col[i];
    }
    assert(w==n/2||w==n-n/2);
    int t=(w==n/2);
    rep(i,1,n) if (col[i]==t) printf("%d ",i);
    puts("");
    rep(i,1,n) del[i]=leaf[i]=0,V[i].clear(),_V[i].clear();
}

int main() {
	freopen("hard.in","r",stdin);
	freopen("hard.out","w",stdout);
    int T; read(T);
    while (T--) work();
    return 0;
}
