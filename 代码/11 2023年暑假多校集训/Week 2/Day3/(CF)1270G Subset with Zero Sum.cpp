#include <bits/stdc++.h>
using namespace std;
int a[1000005];
bool vis[1000005];
int to[1000005];
void solve(){
    vector<int> ans;
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        to[i]=i-a[i];
        vis[i]= false;
    }
    int now=1;
    while (!vis[now]){
        vis[now]= true;
        now=to[now];
    }
    ans.push_back(now);
    now=to[now];
    while (now!=ans[0]){
        ans.push_back(now);
        now=to[now];
    }
    cout<<ans.size()<<"\n";
    for(int i=0;i<ans.size();i++){
        cout<<ans[i]<<" ";
    }
    cout<<"\n";
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin>>t;
    while(t--)solve();




}