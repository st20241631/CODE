#include <iostream>
#include <cstring>
#include <string>
#define int long long
const int N=1.1e6+100,mod=19930726;
using namespace std;
string s,s1="$";
int sum[N];
int len[2*N];
void init(){
    int len=s.size();
    for(int i=0;i<len;i++){
        s1+="#";
        s1+=s[i];
    }
    s1+="#^";
}
int MAX=-1;
void solve(){
    int Max=0,mid=0;
    int length=s1.length();
    for(int i=1;i<length-1;i++){
        if(i<Max) len[i]=min(len[mid*2-i],Max-i);
        else len[i]=1;
        while (s1[i-len[i]]==s1[i+len[i]])len[i]++;
        if(i+len[i]>Max){
            Max=i+len[i];
            mid=i;
        }
        MAX=max(MAX,len[i]-1);
        if((len[i]-1)&1) sum[len[i]-1]++;
    }
}
int qpow(int x,int y){
    int ans=1;
    while (y){
        if(y&1) ans=ans*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return ans%mod;
    
}
signed main(){
    int n,k;
    cin>>n>>k;
    cin>>s;
    init();
    solve();
    int ans=1;
    for(int i=n-1;i>=0;i--){
        sum[i]+=sum[i+1];
    }
    for(int i=n;i>=0&&k;i--){
        if(sum[i]>0&&(i&1)){
            int tmp=min(sum[i],k);
            ans=ans*qpow(i,tmp)%mod;
            k-=tmp;
        }
    }
    if(k!=0)cout<<-1;
    else cout<<ans;
}