#include <bits/stdc++.h>
using namespace std;
int sg[600000];
bool vis[100];
void init(){
    sg[0]=sg[1]=0;
    for(int i=2;i<1000;i++){
        for(int j=1;j<i;j++){
            vis[sg[j-1]^sg[i-j-1]]=true;
        }
        for(int j=0;j<100;j++){
            if(!vis[j]) {
                sg[i] = j;
                break;
            }
        }
        memset(vis,false,sizeof vis);
    }
    for(int i=1000;i<600000;i++) sg[i]=sg[i-68];
}
int main(){
    init();
    int t;
    cin>>t;
    while(t--){
        int n;
        string s;
        cin>>n>>s;
        int suma= count(s.begin(), s.end(),'R');
        int sumb= count(s.begin(), s.end(),'B');
        if(suma>sumb) puts("Alice");
        else if(sumb>suma) puts("Bob");
        else{
            int ans=0;
            int len=0;
            for(int i=0;i<n;i++){
                if(i&&s[i]==s[i-1]){
                    ans^=sg[len];
                    len=0;
                }
                len++;
            }
            ans^=sg[len];
            if(ans) puts("Alice");
            else puts("Bob");
        }
    }
}