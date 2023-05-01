#include <bits/stdc++.h>
using namespace std;
const int N=10000000;
int b1[N],b2[N];
int f1[N],f2[N];
int tim[N];
int n,m;

int dis[N];
bool vis[N];
void SPFA(){
    memset(dis,0x3f,sizeof dis);
    queue<int> q;
    int s=(1<<n)-1,t=0;
    dis[s]=0;
    vis[s]=true;
    q.push(s);
    while(!q.empty()){
        int now=q.front();
        q.pop();
        vis[now]= false;
        for(int i=1;i<=m;i++){
            if(((now&b2[i])==0)&&((now&b1[i])==b1[i])){
                int v=((now|f1[i])^f1[i])|f2[i];
                if(dis[v]>dis[now]+tim[i]){
                    dis[v]=dis[now]+tim[i];
                    if(!vis[v]){
                        q.push(v);
                        vis[v]=true;
                    }
                }
            }
        }
    }
    if(dis[t]==0x3f3f3f3f) cout<<0;
    else cout<<dis[t];
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>tim[i];
        string s1,s2;
        cin>>s1>>s2;
        for(int j=0;j<n;j++){
            if(s1[j]=='+') b1[i]|=(1<<j);
            if(s1[j]=='-') b2[i]|=(1<<j);

            if(s2[j]=='-') f1[i]|=(1<<j);
            if(s2[j]=='+') f2[i]|=(1<<j);
        }
    }
    SPFA();

}