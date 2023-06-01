#include <iostream>
#define int long long
using namespace std;
const int N=2e6+7;
int a[N];
int sum[N];
int mod[N];
int n,c;
void solve(){
    sum[0]=0;
    for(int i=1;i<=n;i++) mod[i]=-1;
    for(int i=1;i<=n;i++) { cin >> a[i], sum[i] = sum[i - 1] + a[i]; }
    for(int i=1;i<=n;i++){
        if(mod[sum[i]%c]!=-1){
            for(int j=mod[sum[i]%c]+1;j<=i;j++) cout<<j<<" ";
            cout<<"\n";
            break;
        }
        mod[sum[i]%c]=i;
    }
}
signed main(){
    cin>>c>>n;
    while (n!=0||c!=0){
        solve();
        cin>>c>>n;
    }
}