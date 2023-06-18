#include<bits/stdc++.h>
const int N=1.1e7+100;
using namespace std;
string s,s1="$";
void init(){
    cin>>s;
    int len=s.size();
    for(int i=0;i<len;i++){
        s1+="#";
        s1+=s[i];
    }
    s1+="#";
}
bool vis[2*N];
int len[2*N];
void solve(){
    int Max=0,mid=0,ans=-1;
    int length=s1.length();
    for(int i=1;i<length;i++){
        if(i<Max) len[i]=min(len[mid*2-i],Max-i);
        else len[i]=1;
        while (s1[i-len[i]]==s1[i+len[i]])len[i]++;
        if(i+len[i]>Max){
            Max=i+len[i];
            mid=i;
        }
    }
    for(int i=length-1;i>=1;i--){
        if(i+(len[i]-1)==length-1) vis[i]=true;
        else if(vis[i+(len[i]-1)-1]&&i-(len[i]-1)==1) vis[i]=true;
    }
    for(int i=1;i<length;i++){
        if(s1[i]>='a'&&s1[i]<='z'&&vis[i])cout<<i/2<<" ";
    }
    cout<<"\n";
}
void clear(){
    s1="$";
    memset(len,0,sizeof len);
    memset(vis,false,sizeof vis);
}
int main(){
    int t;
    cin>>t;
    while(t--){
        clear();
        init();
        solve();
    }
}