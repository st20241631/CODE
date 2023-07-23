#include <bits/stdc++.h>

using namespace std;
const int N=5e5+10;
char s[N];
int cnt[N*2+10][2];
void solve(){
    cin>>(s+1);
    int len=strlen(s+1);
    int sum=0;
    for(int i=1;i<=len;i++){
        cnt[sum+N][s[i]-'0']++;
        if(s[i]=='0') sum--;
        else sum++;
    }
    sum=0;
    for(int i=1;i<=len;i++){
        if(cnt[sum+N][0] && cnt[sum-1+N][1]) {
            cnt[sum+N][0]--;
            sum--;
            putchar('0');
        }
        else if(cnt[sum+N][1]){
            cnt[sum+N][1]--;
            sum++;
            putchar('1');
        }
        else {
            cnt[sum+N][0]--;
            sum--;
            putchar('0');
        }
    }
    cout<<"\n";
}
int main(){
    int t;
    cin>>t;
    while (t--) solve();
}