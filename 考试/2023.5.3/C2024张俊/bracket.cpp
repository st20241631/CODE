#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int l[1000],r[1000],n;
int a[2005];
int sum1,sum2;
int ans;
struct node{
    int val,id;
};
void dfs(int now){
    if(now>2*n){
        if(sum1!=sum2)return;
        stack<node> s;
        int tmp=2*n;
        int sum=0;
        for(int i=1;i<=tmp;i++){
            if(a[i]==1){
                sum++;
                s.push(node{i,sum});
            }
            else{
                if(s.empty()) return;
                int val=s.top().val,id=s.top().id;
                s.pop();
                if (i - val < l[id] || i - val > r[id]) {
                    return;
                }
            }
        }
        ans++;
        ans%=mod;
        return;
    }
    if(sum1>n||sum2>n) return;
    sum1++;
    a[now]=1;
    dfs(now+1);
    sum1--;
    sum2++;
    a[now]=0;
    dfs(now+1);
    sum2--;
    return;

}
signed main(){
    freopen("bracket.in","r",stdin);
    freopen("bracket.out","w",stdout);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>l[i]>>r[i];
    dfs(1);
    cout<<ans;
}
