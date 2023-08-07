#include <bits/stdc++.h>
using namespace std;
const int N=500005;
int read(){
    int x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9'){
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x;
}

int u[N],v[N],w[N];
struct node1{
    int u,v,w;
} e[N];
int ans[N];

int fa[N],siz[N];
struct node2{
    int x,y,fx,fy;
} st[N];
int top;
int find(int x){
    if(fa[x]==x) return x;
    else return find(fa[x]);
}
void merge(int x,int y){
    int fx=find(x),fy=find(y);
    if(fx==fy) return;
    if(siz[fx]>siz[fy]) swap(fx,fy);
    st[++top]={x,y,fx,fy};
    siz[fy]+=siz[fx];
    fa[fx]=fy;
}

int num;
vector<int> ask[N];
bool cmp1(const node1 &x,const node1 &y){return x.w<y.w;}
bool cmp2(const int &x,const int &y){return w[x]<w[y];}
bool cmp3(const vector<int> &x,const vector<int> &y){return w[x[1]]<w[y[1]];}
int tmp[N];

int main(){
    int n,m;
    n=read();
    m=read();
    for(int i=1;i<=n;i++) fa[i]=i,siz[i]=1;
    for(int i=1;i<=m;i++){
        u[i]=read();
        v[i]=read();
        w[i]=read();
        e[i]={u[i],v[i],w[i]};
    }
    sort(e+1,e+m+1,cmp1);
    int q;
    q=read();
    for(int i=1;i<=q;i++){
        ans[i]=1;
        int k;
        k=read();
        for(int j=1;j<=k;j++) tmp[j]=read();
        sort(tmp+1,tmp+k+1,cmp2);
        for(int j=1;j<=k;j++){
            if(w[tmp[j]]!=w[tmp[j-1]]) ask[++num].push_back(i);
            ask[num].push_back(tmp[j]);
        }
    }
    sort(ask+1,ask+num+1,cmp3);
    int now=1;
    for(int i=1;i<=num;i++){
        while(now<=m&&e[now].w<w[ask[i][1]]){
            merge(e[now].u,e[now].v);
            now++;
        }
        int SIZ=ask[i].size();
        for(int j=1;j<SIZ;j++){
            int id=ask[i][j];
            if(find(u[id])==find(v[id])) ans[ask[i][0]]=0;
            else merge(u[id],v[id]);
        }
        for(int j=SIZ-1;j>=1;j--){
            int id=ask[i][j];
            while(top>0&&st[top].x==u[id]&&st[top].y==v[id]){
                fa[st[top].fx]=st[top].fx;
                siz[st[top].fy]-=siz[st[top].fx];
                top--;
            }
        }
    }
    for(int i=1;i<=q;i++){
        if(ans[i]) puts("YES");
        else puts("NO");
    }
}