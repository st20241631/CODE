#include <bits/stdc++.h>

using namespace std;
char s[2010][2010];
int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>(s[i]+1);
        for(int j=1;j<=i;j++)s[i][j]-='0';
    }
    for(int i=2;i<=n-1;i++){
        for(int j=2;j<=i-1;j++){
            if ((s[i-1][j-1]+s[i-1][j]+s[i][j-1]+s[i][j+1]+s[i+1][j]+s[i+1][j+1])&1){
                puts("No");
                return 0;
            }
        }
    }
    puts("Yes");
    return 0;
}