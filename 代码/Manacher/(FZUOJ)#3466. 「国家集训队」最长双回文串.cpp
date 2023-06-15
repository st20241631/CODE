#include <iostream>
#include <cstring>
#include <string>
#define int long long
const int N=1.1e6+100;
using namespace std;
string s,s1="$";
int len[2*N];
void init(){
    int len=s.size();
    for(int i=0;i<len;i++){
        s1+="#";
        s1+=s[i];
    }
    s1+="#^";
}

int l[N],r[N];//l[i]:以i为结尾的最长回文子串的长度,r[i]:以i为开头的最长回文子串的长度
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
        l[i+(len[i]-1)]=max(l[i+(len[i]-1)],len[i]-1);
        r[i-(len[i]-1)]=max(r[i-(len[i]-1)],len[i]-1);
    }
}
int ans=-1;
signed main(){
    cin>>s;
    init();
    solve();
    int length=s1.length();
    for(int i=length-2;i>=3;i-=2) l[i]=max(l[i],l[i+2]-2);
    for(int i=3;i<length;i+=2) r[i]=max(r[i],r[i-2]-2);
    for(int i=3;i<length;i+=2)if(l[i]&&r[i]) ans=max(ans,l[i]+r[i]);
    cout<<ans;
}