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
    e[now]=siz;
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
int head[N],sign[N];
int top;
void query(string s){
    int len=s.length();
    int now=0;
    for(int i=0;i<len;i++){
        now=tree[now][s[i]-'a'];
        sign[++top]=now;
        head[top]=i;
        if(e[now]){
            top-=e[now];
            if(!top)now=0;
            else now=sign[top];
        }

    }
}

int main(){
    string s;
    cin>>s;
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        string t;
        cin>>t;
        insert(t);
    }
    build();
    query(s);
    for(int i=1;i<=top;i++)cout<<s[head[i]];


}