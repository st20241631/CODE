#include <bits/stdc++.h>

using namespace std;

int a[200005];
int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+n+1);
    int k=0;
    for(int i=1;i<=n;i++){
        if(a[n-i+1]>m/i){
            k=a[n-i+1];
            break;
        }
    }
    if(k==0){
        cout<<"Alessia"<<endl;
        set<int> s;
        s.insert(m+1);
        for(int i=1;i<=n;i++){
            int ans=0;
            for(int j:s){
                if(a[n-i+1]<j-ans) break;
                ans=j;
            }
            cout<<a[n-i+1]<<" "<<ans+1<<endl;
            int tmp;
            cin>>tmp;
            s.insert(tmp);
        }
    }
    else {
        cout<<"Bernardo"<<endl;
        for(int i=1;i<=n;i++){
            int x,y;
            cin>>x>>y;
            if(x<k) cout<<y<<endl;
            else cout<<(x+y-1)/k*k<<endl;
        }
    }
    return 0;
}