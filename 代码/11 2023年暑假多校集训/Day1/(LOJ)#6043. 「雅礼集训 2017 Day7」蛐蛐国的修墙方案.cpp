#include <bits/stdc++.h>

using namespace std;

int n;
int a[105],sum;
vector<int> v[105];
bool vis[105];

char now[105];

void check(){
    int tmp=0;
    for(int i=1;i<=n;i++){
        tmp+=(now[i]^')'?1:-1);
        if(tmp<0) return;
    }
    puts(now+1);
    exit(0);
}

void dfs(int x){
    if(x>sum){
        check();
        return;
    }
    int siz=v[x].size();
    if(siz==2){
        now[v[x][0]]='(';
        now[v[x][1]]=')';
        dfs(x+1);
        return;
    }
    for(int i=0;i^siz;i++) now[v[x][i]]=(i&1?'(':')');
    dfs(x+1);
    for(int i=0;i^siz;i++) now[v[x][i]]=(i&1?')':'(');
    dfs(x+1);
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            sum++;
            int x=i;
            while(!vis[x]){
                vis[x]=1;
                v[sum].push_back(x);
                x=a[x];
            }
        }
    }
    dfs(1);
}