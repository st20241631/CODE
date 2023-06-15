#include <iostream>
#include <cstring>
#include <string>
const int N=1.1e6+100;
using namespace std;
string s,s1="$";
int len[2*N];
void clear(){
    s1="$";
    memset(len,0,sizeof len);
}
void init(){
    int len=s.size();
    for(int i=0;i<len;i++){
        s1+="#";
        s1+=s[i];
    }
    s1+="#^";
}

void solve(int time){
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
    cout<<"Case "<<time<<": ";
    cout<<ans<<"\n";
}
int main(){
    int time=0;
    while (cin>>s){
        if(s=="END") return 0;
        time++;
        clear();
        init();
        solve(time);
    }
}