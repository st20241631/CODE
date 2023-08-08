#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1000050;
int a[N];
bool flag[N];
int l[N],r[N];

int n;
bool cmp(const int &x,const int &y){return x>y;}
signed main(){
    cin>>n;
    r[0]=1;
    l[n+1]=n;

    int sum=0;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        sum+=a[i];
        l[i]=i-1,r[i]=i+1;
        flag[i]=(a[i]!=0);
    }
    for(int i=3;i<=n;i=r[i]){
        while(flag[l[l[i]]]&&flag[l[i]]&&flag[i]&&a[l[i]]>=a[l[l[i]]]&&a[l[i]]>=a[i]){
            a[i]=a[l[l[i]]]+a[i]-a[l[i]];
            r[l[l[l[i]]]]=i;
            l[i]=l[l[l[i]]];
        }
    }
    int L=r[0];
    int R=l[n+1];
    int s=0;
    while(a[L]>=a[r[L]]&&flag[L]&&flag[r[L]]) s+=a[r[L]]-a[L],L=r[r[L]];
    while(a[R]>=a[l[R]]&&flag[R]&&flag[l[R]]) s+=a[l[R]]-a[R],R=l[l[R]];
    int tot=0;
    for(int i=L;i<=R;i=r[i])if(flag[i])a[++tot]=a[i];
    sort(a+1,a+tot+1,cmp);
    a[++tot]=s;

    int val=0;
    for(int i=1;i<=tot;i++){
        if(i&1) val+=a[i];
        else val-=a[i];
    }
    cout<<(sum+val)/2<<" "<<(sum-val)/2;
}