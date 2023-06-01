#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a),i##END=(b);i<=i##END;i++)
#define Rof(i,b,a) for(int i=(b),i##END=(a);i>=i##END;i--)
#define go(u) for(int i=head[u];i;i=nxt[i])
#define int long long
using namespace std;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return x*f;
}
const int N=710,p=998244353;
int n,L[N],R[N];
int f[N][N];
signed main(){
	freopen("bracket.in","r",stdin);
	freopen("bracket.out","w",stdout);
	For(i,1,n=read())L[i]=read(),R[i]=read();
	For(i,1,n)if(L[i]%2==0)L[i]++;
	For(i,1,n)L[i]++,R[i]++;
	//f[k][x]:从k开始标号的左括号，填x对括号的方案数
	For(i,1,n+1)f[i][0]=1;For(x,1,n)For(k,1,n-x+1){
		for(int i=L[k];i<=R[k]&&i<=2*x;i+=2){//枚举[1,i]是第k对括号 
			(f[k][x]+=f[k+1][i/2-1]*f[k+i/2][x-i/2])%=p;
		}
//		printf("f[%d][%d] = %d\n",k,x,f[k][x]);
	}cout<<f[1][n]<<endl;
	return 0;
}
