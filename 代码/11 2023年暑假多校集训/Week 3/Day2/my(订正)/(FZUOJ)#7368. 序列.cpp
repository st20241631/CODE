#include <bits/stdc++.h>
#define int long long
const int mod=998244353;
using namespace std;
int lowbit(int x) {return x&(-x);}
int n;
int tree1[1000000];
void add1(int x,int y){
    for(int i=x;i<=n;i+= lowbit(i)) tree1[i]=(tree1[i]+y)%mod;
}
int query1(int x){
    int sum=0;
    for(int i=x;i;i-= lowbit(i))sum=(sum+tree1[i])%mod;
    return sum%mod;
}


int tree2[1000000];
void add2(int x,int y){
    for(int i=x;i;i-= lowbit(i)) tree2[i]=(tree2[i]+y)%mod;
}
int query2(int x){
    int sum=0;
    for(int i=x;i<=n;i+= lowbit(i))sum=(sum+tree2[i])%mod;
    return sum%mod;
}

int a[1000000];
void init(){
    memset(tree1,0,sizeof tree1);
    memset(tree2,0,sizeof tree2);
}
void solve(){
    init();
    int ans=0;
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=n;i;i--){
        int x= query1(a[i])+1,y= query2(a[i])+1;
        ans=(ans+x*y%mod)%mod;
        add1(a[i],x);
        add2(a[i],y);
    }
    cout<<ans<<"\n";
}
signed main(){
    int t;
    cin>>t;
    while (t--) solve();
}