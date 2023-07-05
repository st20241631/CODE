#include <bits/stdc++.h>

using namespace std;
map<int,int> sg,mp;
void work(int x){
    for(int i=2;i*i<=x;i++){
        if(x%i==0){
            int cnt=0;
            while (x%i==0){
                x/=i;
                cnt++;
            }
            mp[i]|=1<<(cnt-1);
        }
    }
    if(x>1) mp[x]|=1;
}
int calc(int x){
    if(x==0) return 0;
    if(sg.count(x)) return sg[x];
    int tmp=x,sum=0;
    while(tmp>0){
        tmp>>=1;
        sum++;
    }
    map<int,int> vis;
    for(int i=1;i<=sum;i++){
        int to=(x>>i)|(x&((1<<(i-1))-1));
        vis[calc(to)]=1;
    }
    for(int i=0;;i++){
        if(!vis.count(i)){
            sg[x]=i;
            return i;
        }
    }
}
int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        work(x);
    }
    int ans=0;
    for(auto i:mp){
        ans^=calc(i.second);
    }
    if(ans!=0){puts("Mojtaba");}
    else{puts("Arpa");}

}