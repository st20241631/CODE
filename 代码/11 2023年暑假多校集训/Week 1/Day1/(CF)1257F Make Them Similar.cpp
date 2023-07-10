#include <bits/stdc++.h>

using namespace std;

int a[1000];
int getcnt(int x){
    int sum=0;
    while(x) x=x&(x-1),sum++;
    return sum;
}
map<vector<int>,int> mp;
int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int x=0;x<(1<<15);x++){     //枚举x的前十五位
        int b1= getcnt(x^(a[1]>>15));
        vector<int> tmp;
        for(int i=2;i<=n;i++){
            tmp.push_back(getcnt(x^(a[i]>>15))-b1);
        }
        mp[tmp]=x;
    }
    for(int x=0;x<(1<<15);x++){     //枚举x的后十五位
        int c1= getcnt(x^(a[1]&((1<<15)-1)));
        vector<int> tmp;
        for(int i=2;i<=n;i++){
            tmp.push_back(c1-getcnt(x^(a[i]&((1<<15)-1))));
        }
        if(mp.count(tmp)){
            cout<<(mp[tmp]<<15)+x;
            return 0;
        }
    }
    cout<<-1;
}