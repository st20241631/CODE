#include <bits/stdc++.h>

using namespace std;
const int N=3*1e5+5;
int dep[N];
int fa[N][17];
void update(int u,int dad){
    dep[u]=dep[dad]+1;
    fa[u][0]=dad;
    for(int i=1;i<=16;i++)fa[u][i]=fa[fa[u][i-1]][i-1];
}
vector<int> s1,s2;
int lca(int x,int y){
    if(dep[x]<=dep[y]) swap(x,y);
    for(int i=16;i>=0;i--){
        if(dep[fa[x][i]]>=dep[y]) x=fa[x][i];
    }
    if(x==y) return x;
    for(int i=16;i>=0;i--){
        if(fa[x][i]!=fa[y][i]) {
            x=fa[x][i];
            y=fa[y][i];
        }
    }
    return fa[x][0];
}
int getdis(int x,int y){
    return dep[x]+dep[y]-2*dep[lca(x,y)];
}
int main(){
    int m;
    cin>>m;
    m++;
    update(1,0);
    s1.push_back(1);
    int MAX=-1;
    for(int i=2;i<=m;i++){
        int x;
        cin>>x;
        update(i,x);
        int d1=s1.empty()?0:getdis(i,s1[0]);
        int d2=s2.empty()?0:getdis(i,s2[0]);
        if(max(d1,d2)>MAX){
            MAX= max(d1,d2);
            if(MAX==d1){
                for(int j:s2){
                    if(getdis(i,j)==d1) s1.push_back(j);
                }
                s2.clear();
            }
            else if(MAX==d2){
                for(int j:s1){
                    if(getdis(i,j)==d2) s2.push_back(j);
                }
                s1.clear();
            }
        }
        if(max(d1,d2)==MAX){
            if(MAX==d1) s2.push_back(i);
            else s1.push_back(i);
        }
        cout<<s1.size()+s2.size()<<"\n";
    }
}