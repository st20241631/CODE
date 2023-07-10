#include <bits/stdc++.h>

using namespace std;

int n;
struct node1{
    int a,b,c;
}test[300];
struct node2{
    int ans[30],val;
};
map<pair<int,int>,node2> mp;
int now[30];
void dfs1(int dep,int a,int b,int c){
    if(dep==n/2+1){
        int x1=a-c;
        int x2=a-b;
        if(mp.find(make_pair(x1,x2))!=mp.end()){
            if(a<mp[make_pair(x1,x2)].val){
                return;
            }
        }
        node2 tmp;
        tmp.val=a;
        for(int i=1;i<=n/2;i++){
            tmp.ans[i]=now[i];
        }
        mp[make_pair(x1,x2)]=tmp;
        return;
    }
    now[dep]=1;
    dfs1(dep+1,a,b+test[dep].b,c+test[dep].c);
    now[dep]=2;
    dfs1(dep+1,a+test[dep].a,b,c+test[dep].c);
    now[dep]=3;
    dfs1(dep+1,a+test[dep].a,b+test[dep].b,c);
    return;
}

bool flag=false;
int Max=-0x3f3f3f3f;
int Ans[30];
void dfs2(int dep,int a,int b,int c){
    if(dep==n+1){
        int x1=c-a;
        int x2=b-a;
        if(mp.find(make_pair(x1,x2))==mp.end()){ return;}
        flag=true;
        if(a+mp[make_pair(x1,x2)].val>Max){
            node2 tmp=mp[make_pair(x1,x2)];
            Max=a+tmp.val;
            for(int i=1;i<=n/2;i++){
                Ans[i]=tmp.ans[i];
            }
            for(int i=n/2+1;i<=n;i++){
                Ans[i]=now[i];
            }
        }
        return;
    }
    now[dep]=1;
    dfs2(dep+1,a,b+test[dep].b,c+test[dep].c);
    now[dep]=2;
    dfs2(dep+1,a+test[dep].a,b,c+test[dep].c);
    now[dep]=3;
    dfs2(dep+1,a+test[dep].a,b+test[dep].b,c);
    return;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>test[i].a>>test[i].b>>test[i].c;
    }
    dfs1(1,0,0,0);
    dfs2(n/2+1,0,0,0);
    if(!flag) {puts("Impossible"); return 0;}
    for(int i=1;i<=n;i++){
        if(Ans[i]==1) puts("MW");
        else if(Ans[i]==2) puts("LW");
        else puts("LM");
    }
}