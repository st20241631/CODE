#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6;
int w[N];
int n,mod;
int mo(int x,int p){
    if(x<p) return x;
    else return x%p+p;
}
unordered_map<int,int> mp;
int phi(int x){
    if(mp.count(x)) return mp[x];
    int ans=x;
    for(int i=2;i*i<=x;i++){
        if(x%i==0) {
            ans=ans/i*(i-1);
            while(x%i==0) x/=i;
        }
    }
    if(x>1) ans=ans/x*(x-1);
    mp[x]=ans;
    return ans;
}
int qpow(int x,int y,int p){
    int ans=1;
    while(y){
        if(y&1) ans=mo(ans*x,p);
        x=mo(x*x,p);
        y>>=1;
    }
    return ans;
}
int solve(int l,int r,int p){
    if(l==r||p==1) {return mo(w[l],p);}
    else return qpow(w[l],solve(l+1,r,phi(p)),p);
}
signed main(){
    cin>>n>>mod;
    for(int i=1;i<=n;i++) cin>>w[i];
    int q;
    cin>>q;
    while(q--){
        int l,r;
        cin>>l>>r;
        cout<<solve(l,r,mod)%mod<<"\n";
    }
}