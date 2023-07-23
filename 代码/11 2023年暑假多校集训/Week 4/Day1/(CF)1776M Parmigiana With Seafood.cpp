#include <bits/stdc++.h>

using namespace std;
const int N=1e5+5;
int n;
vector<int> G[N];
int col[N];
void dfs(int u,int dad,int color){
    col[u]=color;
    for(int v:G[u]){
        if(v==dad||col[v]) continue;
        dfs(v,u,3-color);
    }
}


int du[N];
void dfs2(int u,int dad,int mid){
    du[u]=0;
    for(int v:G[u]){
        if(v==dad) continue;
        dfs2(v,u,mid);
        if(v>=mid || du[v]>0) du[u]++;
    }
}
bool check(int mid){
    for(int i=mid;i<=n;i++){
        if (G[i].size()==1) return true;
    }

    //异色
    bool flag1= false,flag2= false;
    for(int i=mid;i<=n;i++){
        if(col[i]==1) flag1= true;
        else if(col[i]==2) flag2= true;
    }
    if(flag1&&flag2) return true;

    //同色
    dfs2(mid,0,mid);
    du[mid]--;
    for(int i=1;i<=n;i++){
        if(col[i]==col[n] && du[i]+1>=3) return true;
    }
    return false;

}
int main(){
    cin>>n;
    if(n%2==0) {
        cout<<n;
        return 0;
    }
    for(int i=1;i<n;i++){
        int x,y;
        cin>>x>>y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    dfs(1,0,1);

    int l=1,r=n;
    while (l<r){
        int mid=(l+r+1)>>1;
        if (check(mid)) l=mid;
        else r=mid-1;
    }
    cout<<l;
}