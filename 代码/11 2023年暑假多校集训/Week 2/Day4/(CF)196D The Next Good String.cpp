#include <bits/stdc++.h>
#define ull unsigned long long
using namespace std;
const ull p=1331,N=4e5+10;
ull hash1[N],hash2[N],po[N];
int d,n;
char s[N];

bool check(int l,int r){
    int x=hash1[r]-hash1[l-1];
    int y=(hash2[r]-hash2[l-1]*po[r-l+1])*po[l-1];
    return x==y;
}
int main(){
    po[0]=1;
    for(int i=1;i<N-5;i++) po[i]=po[i-1]*p;
    cin>>d>>(s+1);
    n= strlen(s+1);
    int last=n;
    for(int i=1;i<=n;i++){
        hash1[i]=hash1[i-1]+s[i]*po[i-1];
        hash2[i]=hash2[i-1]*p+s[i];
        if(i>=d&& check(i-d+1,i)){
            last=i;
            break;
        }
        if(i>=d+1&& check(i-(d+1)+1,i)){
            last=i;
            break;
        }
    }
    bool flag= false;
    for(int i=last;i>=1;i--){
        for(char ch=s[i]+1;ch<='z';ch++){
            s[i]=ch;
            hash1[i]=hash1[i-1]+s[i]*po[i-1];
            hash2[i]=hash2[i-1]*p+s[i];
            if(i>=d&& check(i-d+1,i)) continue;
            if(i>=d+1&& check(i-(d+1)+1,i)) continue;
            flag= true;
            break;
        }
        if(flag){
            last=i;
            break;
        }
    }
    if(!flag) { puts("Impossible");return 0;}
    for(int i=last+1;i<=n;i++){
        for(char ch='a';ch<='z';ch++){
            s[i]=ch;
            hash1[i]=hash1[i-1]+s[i]*po[i-1];
            hash2[i]=hash2[i-1]*p+s[i];
            if(i>=d&& check(i-d+1,i)) continue;
            if(i>=d+1&& check(i-(d+1)+1,i)) continue;
            break;
        }
    }
    cout<<(s+1);
}