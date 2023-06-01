#include<bits/stdc++.h>
#include <vector>
using namespace std;
int n,m;
int a[1000000],b[1000000],c[1000000];
vector<int> G[1000000];
int col[1000000];
bool dfs(int u,int color){
    col[u]=color;
    for(int i:G[u]){
        if(col[i]==color)return false;
        if(!col[i]&&!dfs(i,3-color))return false;
    }
    return true;
}
bool check(int mid){
    for(int i=1;i<=n;i++)G[i].clear(),col[i]=0;
    for(int i=1;i<=m;i++){
        if(c[i]>mid)G[a[i]].push_back(b[i]),G[b[i]].push_back(a[i]);
    }
    bool flag=true;
    for(int i=1;i<=n;i++){
        if(col[i]==0){
            if(!dfs(i,1))flag=false;
        }
    }
    return flag;
}
int main(){
    cin>>n>>m;
    int Max=-1;
    for(int i=1;i<=m;i++){
        cin>>a[i]>>b[i]>>c[i];
        Max=max(Max,c[i]);
    }
    int l=0,r=Max+10;
    while(l<r){
        int mid=(l+r)>>1;
        if(check(mid))r=mid;
        else l=mid+1;
    }
    cout<<l;
}
