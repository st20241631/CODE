#include<bits/stdc++.h>
#define int long long
const int N=1.1e7+100;
using namespace std;
string s,s1="$";
char mp[1000];
void init(){
    cin>>s;
    int len=s.size();
    for(int i=0;i<len;i++){
        s1+="#";
        s1+=s[i];
    }
    s1+="#";
    mp['1']='0',mp['0']='1',mp['#']='#',mp['$']='$';
}

int len[2*N];
void solve(){
    int Max=1,mid=1,ans=0;
    int length=s1.length();
    for(int i=1;i<length;i+=2){
        if(i<Max) len[i]=min(len[mid*2-i],Max-i);
        else len[i]=1;
        while (mp[s1[i-len[i]]]==s1[i+len[i]])len[i]++;
        if(i+len[i]>Max){
            Max=i+len[i];
            mid=i;
        }
        ans+=len[i]>>1;

    }
    cout<<ans;
}
signed main(){
    int n;
    cin>>n;
    init();
    solve();
}