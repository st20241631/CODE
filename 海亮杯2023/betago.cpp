#include <bits/stdc++.h>
using namespace std;
int x,y,i,j;
int f(){
    return (x == i) && (y == j);
}
int main(){
    freopen("betago.in","r",stdin);
    freopen("betago.out","w",stdout);
    cin >> x >> y>> i >> j;
    int ans=0;
    while(1){
        if(f()){
            cout<<min(ans,72-ans);
            return 0;
        }
        if(x == 1 && y != 19){
            y++;
            ans++;
        }
        else if(y==19 && x != 19){
            x++;
            ans++;
        }
        else if(x == 19 && y != 1){
            y--;
            ans++;
        }
        else if(y==1 && x != 1){
            x--;
            ans++;
        }
    }

}