#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,a[100];
int c(int n,int m){
    int ans1=1,ans2=1;
    for(int i=0;i<m;i++){
        ans1=ans1*(i+1);
        ans2=ans2*(n-i);
    }
    return ans2/ans1;
}
int ans;
void f(){
    int sum=n;
    int tmp=1;
    for(int i=0;i<=9;i++){
        if(a[i]){
            tmp*=c(sum,a[i]);
            sum-=a[i];
        }
    }
    ans+=tmp;
}
signed main(){
    string s;
    cin>>s;
    n=s.length();
    for(int i=0;i<n;i++){a[s[i]-'0']++;}
    int tmp=n;
    for(int i=0;i<tmp;i++){
        n--;
        for(int j=0;j<(s[i]-'0');j++){if(a[j]){a[j]--;f();a[j]++;}}
        a[s[i]-'0']--;
    }
    cout<<ans;
}