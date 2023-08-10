#include<bits/stdc++.h>
#define int long long
using namespace std;
void solve(){
    int ans=0,cnt=0;
    int n,m1,m2;
    cin>>n>>m1>>m2;
    vector<int> a,b,c;
    for(int i=1;i*i<=m1;i++){
        if(m1%i==0){
            a.push_back(i);
            if(i*i!=m1) a.push_back(m1/i);
        }
    }
    for(int i=1;i*i<=m2;i++){
        if(m2%i==0){
            b.push_back(i);
            if(i*i!=m2) b.push_back(m2/i);
        }
    }
    for(int i:a)for(int j:b)c.push_back(i*j);
    sort(c.begin(), c.end());
    c.erase(unique(c.begin(), c.end()),c.end());
    int SIZ=c.size();
    for(int i=0;i<SIZ;i++){
        int l=0,r=i+1;
        while (l<r){
            int mid=(l+r)>>1;
            if((c[i]+c[mid]-1)/c[mid]<=n) r=mid;    //$\lceil \frac{c_i}{c_{mid}} \rceil \le n$
            else l=mid+1;
        }
        for(int j=l;j<SIZ;j++){
            if(c[j]>n) break;
            if(c[i]%c[j]==0){
                ans^=c[j];
                cnt++;
                break;
            }
        }
    }
    cout<<cnt<<" "<<ans<<"\n";
}
signed main(){
    int t;
    cin>>t;
    while(t--) solve();
}