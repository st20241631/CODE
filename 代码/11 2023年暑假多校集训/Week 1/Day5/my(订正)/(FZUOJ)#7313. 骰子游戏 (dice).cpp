#include <bits/stdc++.h>

using namespace std;

int main(){
    int n,k;
    cin>>n>>k;
    cout<<"Yes\n";
    for(int i=1;i<=n;i++){
        cout<<0<<" "<<k<<" "<<(k<<6)+k<<" "<<(k<<12)+(k<<6)+k<<" "<<(k<<12)+k<<" "<<(k<<12)+(k<<6)<<"\n";
    }
}