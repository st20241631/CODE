#include <bits/stdc++.h>

using namespace std;
struct node{
    int a,b;
    double val;
}book[10000000];
bool cmp(node x,node y){
    return x.val<y.val;
}
double dp[10000000];
void solve(){
    int tot=0;
    int k,a,b;
    cin>>k>>a>>b;
    for(int i=0;i<a;i++){
        for(int j=0;j<b;j++){
            book[++tot]={i,j,0};
            if(i==0) book[tot].val=1e9;
            else book[tot].val=(a*j-i*j)*1.0/(i*b*1.0);
        }
    }
    sort(book+1,book+tot+1,cmp);
    for(int i=1;i<=k;i++){
        dp[i]=1e9;
        double sum1=0,sum2=0;
        for(int j=1;j<=tot;j++){
            double x=book[j].a*1.0/a;
            double y=book[j].b*1.0/b;
            sum1+=x+y-x*y;
            sum2+=1-x;
            dp[i]=min(dp[i],(a*b*1.0+dp[i-1]*1.0*sum1)/((j-sum2)*1.0));
        }
    }
    printf("%.3lf\n",dp[k]);
}
int main(){
    int t;
    cin>>t;
    while(t--) solve();
}