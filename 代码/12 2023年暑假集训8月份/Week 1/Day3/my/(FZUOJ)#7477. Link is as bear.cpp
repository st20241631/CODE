#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
using namespace std;
#define endl "\n"
#define int long long
using namespace std;
const int siz=63;
int p[siz+1];
int n;
void ins(int s){
    for(int i=siz;~i;i--){
        if((s>>i)&1){
            if(!p[i]){
                p[i]=s;
                return;
            }else s^=p[i];
        }
    }
}
void solve(){
    IOS;
    cin>>n;
    for(int i=0;i<=siz;i++)p[i]=0;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        ins(x);
    }
    int p=0;
    for(int i=siz;~i;i--){
        if((p^::p[i])>p)p^=::p[i];
    }
    cout<<p<<endl;
    return;
}
signed main(){
    int t;
    cin>>t;
    while(t--)solve();
    return 0;
}