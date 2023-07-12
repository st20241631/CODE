#include <bits/stdc++.h>

using namespace std;
struct node{
    int val,id;
}a[1000000];
bool cmp(node x,node y){
    if(x.val==y.val) return x.id<y.id;
    return x.val<y.val;
}
int b[10000000];
int ans1[10000000],ans2[1000000],cnt;
int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i].val;
        a[i].id=i;
    }
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++) b[i]=a[i].id;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n-i;j++){
            if(b[j]>b[j+1]){
                swap(b[j],b[j+1]);
                ans1[++cnt]=b[j];
                ans2[cnt]=b[j+1];
            }
        }
    }
    cout<<cnt<<"\n";
    for(int i=1;i<=cnt;i++){
        cout<<ans1[i]<<" "<<ans2[i]<<"\n";
    }
}