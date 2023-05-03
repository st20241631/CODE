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
    #define sz 202200
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

int n; ll T;
struct hh{int a,b,id;}a[sz];
vector<int>V[sz];

struct hhh {
    int a; ll b;
    const hhh operator + (const hhh &x) const {return hhh{a+x.a,b+x.b};}
};
struct BIT {
    hhh tr[sz];
    void clear() { rep(i,0,n+1) tr[i]=hhh{0,0}; }
    void add(int x,hhh w) { while (x<=n) tr[x]=tr[x]+w,x+=x&-x; }
    hhh query(int x) { hhh res={0,0}; while (x) res=res+tr[x],x-=x&-x; return res; }
    hhh querycnt(int x) {
        int t=0; hhh res={0,0};
        drep(i,20,0) if ((1<<i|t)<=n&&(res+tr[1<<i|t]).a<=x) t|=1<<i,res=res+tr[t];
        return res;
    }
}tr1,tr2,tr3;

vector<int>ans;
int check(int cc) {
    ans.clear();
    memcpy(tr2.tr,tr3.tr,sizeof(hhh)*(n+10));
    tr1.clear();
    int tot=0;
    rep(i,1,n) {
        for (auto id:V[i]) tr1.add(id,{1,a[id].a}),tr2.add(id,{-1,-a[id].a}),++tot;
        if (i<cc||tot<cc) continue;
        hhh w=tr1.query(i);
        w.b+=tr2.query(i).b;
        if (w.b>T) return 0;
        if (w.a>=cc) {
            rep(j,1,i) ans.push_back(j);
            return 1;
        }
        hhh w1=tr1.querycnt(cc),w2=tr2.querycnt(i-cc);
        if (w1.b+w2.b<=T) {
            int t1=0,t2=0;
            rep(j,1,n)
                if (a[j].b<=i&&t1+1<=cc) ++t1,ans.push_back(j);
                else if (a[j].b>i&&t2+1<=i-cc) ++t2,ans.push_back(j);
            return 1;
        }
    }
    return 0;
}

void work() {
    read(n,T); assert(1<=n&&n<=200000),assert(1<=T&&T<=2e14);
    rep(i,1,n) read(a[i].a,a[i].b),a[i].id=i,assert(1<=a[i].a&&a[i].a<=1e9),assert(1<=a[i].b&&a[i].b<=n);
    sort(a+1,a+n+1,[](const hh &x,const hh &y){return x.a<y.a;});
    rep(i,1,n) V[a[i].b].push_back(i);
    tr3.clear();
    rep(i,1,n) tr3.add(i,{1,a[i].a});
    int l=0,r=n,ans=0;
    while (l<=r) {
        int mid=(l+r)>>1;
        if (check(mid)) ans=mid,l=mid+1;
        else r=mid-1;
    }
    printf("%d\n",ans);
    check(ans);
    printf("%d\n",(int)(::ans).size());
    for (auto t:(::ans)) printf("%d ",a[t].id);
    puts("");
    rep(i,1,n) V[i].clear();
    tr3.clear();
}

int main() {
	freopen("easy.in","r",stdin);
	freopen("easy.out","w",stdout);
    int T; read(T);
    while (T--) work();
    return 0;
}
