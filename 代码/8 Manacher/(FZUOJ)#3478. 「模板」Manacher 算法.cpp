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
    s1+="#^";
}

int len[2*N];
void solve(){
    int Max=0,mid=0,ans=-1;
    int length=s1.length();
    for(int i=1;i<length-1;i++){
        if(i<Max) len[i]=min(len[mid*2-i],Max-i);
        else len[i]=1;
        while (s1[i-len[i]]==s1[i+len[i]])len[i]++;
        if(i+len[i]>Max){
            Max=i+len[i];
            mid=i;
        }
        ans=max(ans,len[i]-1);
    }
    cout<<ans;
}
int main(){
    init();
    solve();
}