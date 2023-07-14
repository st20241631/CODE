#include <bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int prime[N],sum[N],cnt;
int n,m;
void f(int x){
    memset(sum,0,sizeof sum);
    cnt=0;
    for(int i=2;i*i<=x;i++){
        if(x%i==0){
            prime[++cnt]=i;
            while (x%i==0){
                sum[cnt]++;
                x/=i;
            }
        }
    }
    if(x>1){
        prime[++cnt]=x;
        sum[cnt]=1;
    }
}


bool flag[1100000];
void solve(){
    f(m);
    n--;
    vector<int> ans;
    memset(flag, false,sizeof flag);
    for(int i=1;i<=cnt;i++){
        int tot=0;
        for(int j=1;j<n;j++){
            int a=n-j+1;
            int b=j;
            while (a%prime[i]==0) {
                a/=prime[i];
                tot++;
            }
            while (b%prime[i]==0){
                b/=prime[i];
                tot--;
            }
            if(tot<sum[i]){
                flag[j]=true;
            }

        }
    }
    for(int i=1;i<n;i++){
        if(!flag[i]) ans.push_back(i+1);
    }
    cout<<ans.size()<<"\n";
    for(int i=0;i<ans.size();i++){
        if(i==0) cout<<ans[i];
        else cout<<" "<<ans[i];
    }
    cout<<"\n";
}
signed main(){
    while (cin>>n>>m){
        solve();
    }
}