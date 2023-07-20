#include <bits/stdc++.h>
using namespace std;
void solve(){
    double x11,x12,y11,y12,x21,x22,y21,y22,x31,x32,y31,y32;
    cin>>x11>>x12>>y11>>y12>>x21>>x22>>y21>>y22>>x31>>x32>>y31>>y32;
    double x,y;
    cin>>x>>y;
    double tmp1=min(x11,x12)+min(x21,x22)+min(x31,x32);
    double tmp2=max(x11,x12)+max(x21,x22)+max(x31,x32);
    double tmp3=min(y11,y12)+min(y21,y22)+min(y31,y32);
    double tmp4=max(y11,y12)+max(y21,y22)+max(y31,y32);
    if(x>=tmp1/3&&x<=tmp2/3&&y>=tmp3/3&&y<=tmp4/3) {
        puts("heihei");
    }
    else puts("yiyandingzhen");
}

int main(){
    int t;
    cin>>t;
    while(t--){solve();}
}
