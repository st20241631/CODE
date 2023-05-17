#include<bits/stdc++.h>
#define int long long
using namespace std;
int ans1,ans2,ans3=1;
int gcd(int x,int y) {
    while(y^=x^=y^=x%=y);
    return x;
}
int f(int x){
    int cnt=0;
    while(x){cnt++;x/=10;}
    return cnt;
}
main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        int k=ans2*(n-i+1)+ans3*n;
        int l=ans3*(n-i+1);
        int g=gcd(k,l);
        k/=g,l/=g;
        ans2=k,ans3=l;
        ans1+=k/l;
        ans2-=(k/l)*l;
    }
    int g=gcd(ans2,ans3);
    ans2/=g,ans3/=g;
    if(ans3==1){
        cout<<ans1+ans2;
    }
    else {
        int tmp=f(ans1);
        for(int i=1;i<=tmp;i++)cout<<" ";
        cout<<ans2<<"\n";
        cout<<ans1;
        tmp=f(ans3);
        for(int i=1;i<=tmp;i++)cout<<"-";
        cout<<"\n";
        tmp=f(ans1);
        for(int i=1;i<=tmp;i++)cout<<" ";
        cout<<ans3<<"\n";


    }
    return 0;
}
