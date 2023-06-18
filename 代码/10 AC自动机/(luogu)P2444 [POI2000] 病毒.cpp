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
        if(!tree[now][s[i]-'0']) tree[now][s[i]-'0']=++cnt;
        now=tree[now][s[i]-'0'];
    }
    e[now]++;
}
queue<int> q;
void build(){
    for(int i=0;i<=1;i++)if(tree[0][i]) q.push(tree[0][i]);
    while(!q.empty()){
        int now=q.front();
        q.pop();
        for(int i=0;i<=1;i++){
            if (tree[now][i]) {
                fail[tree[now][i]]=tree[fail[now]][i];
                if(e[fail[tree[now][i]]]) e[tree[now][i]]++;
                q.push(tree[now][i]);
            }
            else tree[now][i] = tree[fail[now]][i];
        }
    }
}

int vis1[N],vis2[N];
int query(int now){
    vis1[now]=1;
    for(int i=0;i<=1;i++){
        int v=tree[now][i];
        if(vis1[v]) return 1;
        if(vis2[v]||e[v]) continue;
        vis2[v]=1;
        if(query(v)) return 1;
    }
    vis1[now]=0;
    return 0;
}
int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        string s;
        cin>>s;
        insert(s);
    }
    build();
    if(query(0)) puts("TAK");
    else puts("NIE");

}