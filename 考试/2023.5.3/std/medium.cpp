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
    #define mod 1000000007ll
    #define sz 211
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

ll C[sz][sz];

int n,m,V;
int a[sz];

void work() {
    read(n,m,V);
    rep(i,1,n) read(a[i]);
    sort(a+1,a+n+1);
    ll ans=0;
    // |S|<V
    rep(t,1,n) {
        static ll dp[sz][sz*sz];
        dp[1][0]=1;
        rep(i,1,n) rep(j,0,m*V) if (dp[i][j]) {
            if (i!=t&&m+a[t]-a[i]>=0) (dp[i+1][min(m*V,j+min(m,m+a[t]-a[i]))]+=dp[i][j])%=mod;
            if (i>=t) (dp[i+1][min(m*V,j+m)]+=dp[i][j])%=mod;
        }
        (ans+=dp[n+1][m*V])%=mod;
        rep(i,0,n+1) rep(j,0,m*V+1) dp[i][j]=0;
        dp[1][0]=1;
        rep(i,1,n) rep(j,0,i-1) if (dp[i][j]) {
            if (i!=t&&m+a[t]-a[i]>=0) (dp[i+1][j]+=dp[i][j])%=mod;
            if (i>=t) (dp[i+1][j+1]+=dp[i][j])%=mod;
        }
        rep(j,V,n) (ans+=mod-dp[n+1][j])%=mod;
        rep(i,0,n+1) rep(j,0,n+1) dp[i][j]=0;
    }
    // |S|>=V
    rep(t,1,n) {
        int L=1;
        while (a[L]+m<a[t]) ++L;
        static ll dp[sz][sz*sz];
        dp[L][0]=1;
        rep(i,L,n) rep(j,0,m*V) if (dp[i][j]) {
            int w=max(a[t]-a[i],0);
            if (j+w<=m*V&&i!=t) (dp[i+1][j+w]+=dp[i][j])%=mod;
            if (i<=t) (dp[i+1][j]+=dp[i][j])%=mod;
        }
        rep(j,0,m*V) (ans+=dp[n+1][j])%=mod;
        rep(i,0,n+1) rep(j,0,m*V+1) dp[i][j]=0;
        dp[L][0]=1;
        rep(i,L,n) rep(j,0,i-L) if (dp[i][j]) {
            int w=a[t]-a[i];
            if (j+w<=m*V&&i!=t) (dp[i+1][j+1]+=dp[i][j])%=mod;
            if (i<=t) (dp[i+1][j]+=dp[i][j])%=mod;
        }
        rep(j,0,V-1) (ans+=mod-dp[n+1][j])%=mod;
        rep(i,0,n+1) rep(j,0,n+1) dp[i][j]=0;
    }
    (ans+=1)%=mod;
    printf("%lld\n",ans);
}

int main() {
	
	freopen("medium.in","r",stdin);
	freopen("medium.out","w",stdout);
    rep(i,0,sz-1) C[i][0]=1;
    rep(i,1,sz-1) rep(j,1,i) C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
    int T; read(T);
    while (T--) work();
    return 0;
}
