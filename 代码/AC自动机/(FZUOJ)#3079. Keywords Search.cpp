#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int tree[N][30];
int e[N];
int fail[N];
int cnt=0;
void insert(string s){
    int now=0;
    int siz=s.size();
    for(int i=0;i<siz;i++){
        if(!tree[now][s[i]-'a']) tree[now][s[i]-'a']=++cnt;
        now=tree[now][s[i]-'a'];
    }
    e[now]++;
}
void build(){
    queue<int> q;
    for(int i=0;i<26;i++)if(tree[0][i]) q.push(tree[0][i]);
    while(!q.empty()){
        int now=q.front();
        q.pop();
        for(int i=0;i<26;i++){
            if(tree[now][i])fail[tree[now][i]]=tree[fail[now]][i],q.push(tree[now][i]);
            else tree[now][i]=tree[fail[now]][i];     
        }
    }
}
int query(string s){
    int ans=0;
    int u=0;
    int siz=s.size();
    for(int i=0;i<siz;i++){
        u=tree[u][s[i]-'a'];
        for(int j=u;j&&e[j]!=-1;j=fail[j]){
            ans+=e[j];
            e[j]=-1;
        }
    }
    return ans;
}
void clear(){
    cnt=0;
    memset(tree,0,sizeof tree);
    memset(e,0,sizeof e);
    memset(fail,0,sizeof fail);
    
}
int main(){
    int T;
    cin>>T;
    while(T--){
        clear();
        int n;
        cin>>n;
        for(int i=1;i<=n;i++){
            string s;
            cin>>s;
            insert(s);
        }
        build();
        string s;
        cin>>s;
        cout<<query(s)<<"\n";
    }

}