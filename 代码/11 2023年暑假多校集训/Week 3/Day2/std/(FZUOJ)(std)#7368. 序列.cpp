// #include<cstdio>
// using namespace std;
// #define N 100500
// #define mod 998244353
// int T,n,v[N],tr[N];
// void add(int x,int k){for(int i=x;i<=n;i+=i&-i)tr[i]=(tr[i]+k)%mod;}
// int que(int x){int as=0;for(int i=x;i;i-=i&-i)as=(as+tr[i])%mod;return as;}
// int rd(){char s=getchar();int v=0;while(s<'0'||s>'9')s=getchar();while(s>='0'&&s<='9')v=v*10+s-'0',s=getchar();return v;}
// int main()
// {
// 	freopen("sequence.in","r",stdin);
// 	freopen("sequence.out","w",stdout); 
// 	T=rd();
// 	while(T--)
// 	{
// 		n=rd();
// 		for(int i=1;i<=n;i++)v[i]=rd();
// 		for(int i=1;i<=n;i++)tr[i]=0;
// 		for(int i=1;i<=n*2;i++)
// 		{
// 			int vl=v[i<=n?n-i+1:i-n];
// 			add(vl,que(vl-1)+1);
// 		}
// 		printf("%d\n",1ll*que(n)*(mod+1)/2%mod);
// 	}
// }

#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 100000
#define mod 998244353
using namespace std;
int T,n,a[N+5],t1[N+5],t2[N+5],ans;
namespace Input
{
	const int Size=1<<21;
	char buf[Size],*p1=buf,*p2=buf;
	inline char getchar()
	{
		return p1==p2 && (p2=(p1=buf)+fread(buf,1,Size,stdin),p1==p2)?EOF:*p1++;
	}
	inline void read(int &x)
	{
		char ch=getchar();x=0;while(ch<'0') ch=getchar();
		while(ch>='0') x=(x<<1)+(x<<3)+(ch^'0'),ch=getchar();
	}
}
using Input::read;
inline void add(int &a,const int &b) {if((a+=b)>=mod) a-=mod;}
inline void add1(int x,int val) {for(;x<=n;x+=x&-x) add(t1[x],val);}
inline int query1(int x) {int ret=0;for(;x;x-=x&-x) add(ret,t1[x]);return ret;}
inline void add2(int x,int val) {for(;x;x-=x&-x) add(t2[x],val);}
inline int query2(int x) {int ret=0;for(;x<=n;x+=x&-x) add(ret,t2[x]);return ret;}
int main()
{
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout); 
	read(T);
	while(T--)
	{
		read(n),ans=0;
		memset(t1,0,sizeof t1),memset(t2,0,sizeof t2);
		for(int i=1;i<=n;++i) read(a[i]);
		for(int i=n;i;--i)
		{
			int down=query1(a[i])+1,up=query2(a[i])+1;
			ans=(ans+1ll*down*up)%mod;
			add1(a[i],down),add2(a[i],up);
		}
		printf("%d\n",ans);
	}
	return 0;
}