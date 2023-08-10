#include<bits/stdc++.h>

using namespace std;
const int N=1e6+10;
int prime[N],id[N],tot,MAX;
bool flag[N];
void init(){
    prime[++tot]=1;
    id[1]=tot;
    for(int i=2;i<N;i++){
        if(!flag[i]){
            prime[++tot]=i;
            id[i]=tot;
            if(i<1000) MAX++;
        }
        for(int j=1;j<=tot&&i*prime[j]<N;j++){
            flag[i*prime[j]]=true;
            if(i%prime[j]==0) break;
        }
    }
}
struct node{
    int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
    a[++cnt]={v,first[u]};
    first[u]=cnt;
}

int tmp[N];
void solve(int x){
    int sum=0;
    for(int i=2;i*i<=x;i++){
        if(x%i==0){
            int num=0;
            while(x%i==0) x/=i,num++;
            num%=2;
            if(num) tmp[++sum]=i;
        }
    }
    if(x>1) tmp[++sum]=x;
    if(sum==0) { puts("1"); exit(0);}
    else if(sum==1) add(1,id[tmp[1]]),add(id[tmp[1]],1);
    else add(id[tmp[1]],id[tmp[2]]),add(id[tmp[2]],id[tmp[1]]);
}

int ans=0x3f3f3f3f;
struct node2{
    int u,fa;
};
int dis[N];
void bfs(int s){
    memset(dis,0x3f,sizeof dis);
    queue<node2> q;
    q.push({s,0});
    dis[s]=0;
    while (!q.empty()){
        node2 now=q.front();
        q.pop();
        int u=now.u;
        for(int i=first[u];i;i=a[i].nex){
            int v=a[i].v;
            if(v==now.fa) continue;
            if(dis[v]==0x3f3f3f3f){
                dis[v]=dis[u]+1;
                q.push({v,u});
            }
            else{
                ans=min(ans,dis[u]+dis[v]+1);
            }
        }
    }
}
int main(){
    init();
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        solve(x);
    }
    for(int i=1;i<=MAX;i++)bfs(i);
    if(ans>n) { puts("-1");return 0;}
    cout<<ans;
    return 0;
}