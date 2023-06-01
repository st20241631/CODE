#include <bits/stdc++.h>
using namespace std;
inline int re(){
    int x=0;bool f=1;
    char c=getchar();
    while(c<48||c>57){if(c==45)f=0;c=getchar();}
    while(c>47&&c<58)x=(x<<3)+(x<<1)+(c^48),c=getchar();
    return f?x:-x;
}
void wr(int x){
    if(x<0)putchar(45),x=-x;
    if(x>9)wr(x/10);
    putchar(x%10+48);
}
int n;
int MAX=-1;
vector<int> G[10005];
int vis[100005];
int cnt;
int match[100005];
bool dfs(int x){
    for(int y:G[x]){
        if(vis[y]==cnt) continue;
        vis[y]=cnt;
        if(!match[y]||dfs(match[y])){
            match[y]=x;
            return true;
        }
    }
    return false;
}
int main(){
    n=re();
    for(int i=1;i<=n;i++){
        int a,b;
        a=re(),b=re();
        MAX=max({MAX,a,b});
        G[a].push_back(i);
        G[b].push_back(i);
    }
    for(int i=1;i<=MAX+1;i++){
        cnt++;
        if(!dfs(i)){
            wr(i-1);
            return 0;
        }
    }

}