#include <bits/stdc++.h>

using namespace std;
#define int long long
const int MAX=1e18;
int ans[2000005],cnt;
signed main(){
    for(int i=1;;i++){
        int x=i,y=i*i*i;
        if(y>MAX+5) break;
        ans[++cnt]=y;
        if(i==1) continue;
        int tmp=i*i;
        while (1){
            if(1.0*tmp*y-x>2*MAX) break;
            x=tmp*y-x;
            swap(x,y);
            ans[++cnt]=y;
        }
    }
    sort(ans+1,ans+cnt+1);
    int t;
    cin>>t;
    while (t--){
        int n;
        cin>>n;
        cout<<lower_bound(ans+1,ans+cnt+1,n+1)-(ans+1)<<"\n";
    }
}