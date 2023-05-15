#include<bits/stdc++.h>
using namespace std;

const int N = 10010;
const long long P = 100000;
int n,m;
struct BigInt{
    long long f[N],len;
    inline void clear(){memset(f,0,sizeof(f));len=0;}
    inline void give(int x){f[len=1]=x;}
    BigInt operator *(const BigInt &g)const{
        BigInt h;h.clear();h.len=len+g.len+10;
        for(int i=1;i<=len;++i)
            for(int j=1;j<=g.len;++j){
                h.f[i+j-1]+=f[i]*g.f[j];
                h.f[i+j]+=h.f[i+j-1]/P;
                h.f[i+j-1]%=P;
            }
        for(int i=1;i<=h.len;++i)
            h.f[i+1]+=h.f[i]/P,h.f[i]%=P;
        while(h.len && !h.f[h.len])h.len--;
        return h;
    }
    BigInt operator +(const BigInt &g)const{
        BigInt h;h.clear();h.len=max(len,g.len)+10;
        for(int i=1;i<=h.len;++i){
            h.f[i]+=f[i]+g.f[i];
            h.f[i+1]+=h.f[i]/P;
            h.f[i]%=P;
        }
        for(int i=1;i<=h.len;++i)
            h.f[i+1]+=h.f[i]/P,h.f[i]%=P;
        while(h.len && !h.f[h.len])h.len--;
        return h;
    }
    inline void print(){
        printf("%lld",f[len]);
        for(int i=len-1;i>=1;--i)
            printf("%05lld",f[i]);
    }
}Ans;

inline int gi(){
    int x=0,res=1;char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-')res*=-1;ch=getchar();}
    while(ch<='9'&&ch>='0')x=x*10+ch-48,ch=getchar();
    return x*res;
}

inline BigInt A(int n,int m){
    BigInt ans,x;ans.clear();ans.give(1);
    if(!m)return ans;
    if(m>n){ans.clear();return ans;}
    for(long long i=n-m+1;i<=n;++i){x.give(i);ans=ans*x;}
    return ans;
}

int main()
{
    n=gi();m=gi();
    Ans=A(n+1,2)*A(n,n)*A(n+3,m)   +   A(n,n)*A(n+1,1)*A(2,2)*A(m,1)*A(n+2,m-1);
    Ans.print();
    return 0;
}