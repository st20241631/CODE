#include <bits/stdc++.h>
#define int long long
using namespace std;
int fa[10010000];
int find(int x){
    if(x!=fa[x]) fa[x]= find(fa[x]);
    return fa[x];
}
int gcd(int x,int y){
    while (x^=y^=x^=y%=x);
    return y;
}
int n;
int ans;
void merge(int x,int y){
    if (!fa[x]||!fa[y]) return ;
    int fx=find(x),fy=find(y);
    if(fx!=fy){
        fa[fx]=fy;
        ans--;
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    ans=n;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        fa[x]=x;
    }
    for(int y=1;y<=1e7;y++){
        for(int x=y+1;2*x*y<=1e7&&x*x-y*y<=1e7;x++){
            int a=x*x-y*y;
            int b=2*x*y;
            int c=x*x+y*y;
            if(__gcd(a,b)==1){
                merge(a,b);
                if(c<=1e7){
                    merge(a,c);
                    merge(b,c);
                }
            }
        }
    }
    cout<<ans;
}