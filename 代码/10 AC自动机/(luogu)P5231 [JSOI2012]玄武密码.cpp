#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int tree[N][30];
int fail[N];
int cnt=0;
void insert(string s){
    int now=0;
    int siz=s.size();
    for(int i=0;i<siz;i++){
        if(!tree[now][s[i]-'A']) tree[now][s[i]-'A']=++cnt;
        now=tree[now][s[i]-'A'];
    }
}
queue<int> q;
void build(){
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
bool vis[N];
void build2(string s){
    int now=0;
    int siz=s.size();
    for(int i=0;i<siz;i++){
        now=tree[now][s[i]-'A'];
        for(int j=now;j&&!vis[j];j=fail[j]) vis[j]=1;
    }
}
int query(string s){
    int now=0;
    int siz=s.size();
    int ans=0;
    for(int i=0;i<siz;i++){
        now=tree[now][s[i]-'A'];
        if(vis[now]) ans=i+1;
    }
    return ans;
}
string t[N];
int main(){
    int n,m;
    cin>>n>>m;
    string s;
    cin>>s;
    for(int i=1;i<=m;i++){
        cin>>t[i];
        insert(t[i]);
    }
    build();
    build2(s);
    for(int i=1;i<=m;i++){
        cout<<query(t[i])<<"\n";
    }

}