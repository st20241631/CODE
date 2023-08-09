#include<bits/stdc++.h>
using namespace std;
int rd(int x=0,char c=getchar()){while(!isdigit(c))c=getchar();while(isdigit(c))x=x*10+c-48,c=getchar();return x;}
int n,x;
long long s;
using ll=long long;
int a[1000001];
ll p[1000005];
ll k=1e6+1;
void solve(){
    n=rd();
    s=0;
    for(int i=0;i<=n;i++)a[i]=rd(),p[k-i]+=a[i];
    if(a[0])return void(puts("Alice"));
    for(int i=1e6-n;i<=1e6;i++){
        p[i+1]+=p[i]/2;
        p[i]=0;
    }
    if(p[k])puts("Alice");
    else puts("Bob");
    p[k]=0;
}
int main(){
    int t=rd();
    while(t--)solve();
    return 0;
}