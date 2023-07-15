#include <bits/stdc++.h>

using namespace std;
int read(){
    int x=0;
    char ch=getchar();
    while (ch<'0'||ch>'9'){ch=getchar();}
    while (ch>='0'&&ch<='9') {x=x*10+ch-'0';ch=getchar();}
    return x;
}
int a[1000000],b[1000000],c[1000000];
unsigned int ans=0;
int gcd(int x,int y){
    while (x^=y^=x^=y%=x);
    return y;
}
int main(){
    freopen("de.in","r",stdin);
    freopen("de.out","w",stdout);
    int n,m;
    n=read(),m=read();
    for(int i=1;i<=n;i++) a[i]=read();
    for(int i=1;i<=n;i++) b[i]=read();
    for(int i=1;i<=n;i++) c[i]=read();
    while (m--){
        int l,r;
        l=read(),r=read();
        unsigned int sum=0;
        for(int i=l;i<=r;i++){
            int x=a[i],y=b[i],z=c[i];
            sum+=x*y*z;
            for(int j=i+1;j<=r;j++){
                x&=a[j];
                y|=b[j];
                z=gcd(z,c[j]);
                sum+=x*y*z;
            }
        }
        ans^=sum;
    }
    cout<<ans;
    return 0;
}
