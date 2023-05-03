#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2*1e5+10;
int n,t;
int a[N],b[N];
int tmp[N];
int ans1,ans2,ans[N];
void dfs(int now,int sum,int cnt){
    if(now>n){
        int num=0;
        if(sum>t)return;
        for(int i=1;i<=cnt;i++){
            if(b[tmp[i]]<=sum)num++;
        }
        if(num>ans1){
            ans1=num;
            ans2=cnt;
            for(int i=1;i<=cnt;i++)ans[i]=tmp[i];
        }
        return;
    }
    if(sum+a[now]<=t) {
        tmp[cnt+1]=now;
        dfs(now+1,sum+a[now],cnt+1);
        tmp[cnt+1]=0;
    }
    dfs(now+1,sum,cnt);
}
void solve(){
    cin>>n>>t;
    for(int i=1;i<=n;i++)cin>>a[i]>>b[i];
    ans1=ans2=0;
    dfs(1,0,0);
    cout<<ans1<<"\n"<<ans2<<" ";
    for(int i=1;i<=ans2;i++) cout<<ans[i]<<" ";
    cout<<"\n";
}
signed main(){
    freopen("easy.in","r",stdin);
    freopen("easy.out","w",stdout);
    int T;
    cin>>T;
    while(T--)solve();
}