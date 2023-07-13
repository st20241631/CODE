#include <bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define int long long
const int N=3000005;
const ull p=1331;
ull po[N],_hash[N];

char s[N];

ull idx;
unordered_map<ull,ull> mp;
ull a[N];

ull block;
struct node{
    ull l,r,id;
}q[N];
bool cmp(node x,node y){
    if(x.l/block!=y.l/block) return x.l<y.l;
    return (x.l/block)&1?x.r<y.r:x.r>y.r;
}
ull ans[N];
ull sum=0;
ull cnt[N];
void add(ull x){
    sum+=cnt[x];
    cnt[x]++;
}
void del(ull x){
    cnt[x]--;
    sum-=cnt[x];
}
signed main(){
    ull n,m,k;
    cin>>n>>m>>k;
    po[0]=1;
    for(ull i=1;i<=n+10;i++) po[i]=po[i-1]*p;
    cin>>(s+1);
    for(ull i=n;i;i--) _hash[i]=(_hash[i+1]*p+s[i]);
    for(ull i=1;i+k-1<=n;i++){
        ull tmp=_hash[i]-_hash[(i+k-1)+1]*po[k];
        if(!mp.count(tmp)) mp[tmp]=++idx;
        a[i]=mp[tmp];
    }

    for(ull i=1;i<=m;i++){
        cin>>q[i].l>>q[i].r;
        q[i].id=i;
        if(q[i].r>n-k+1) q[i].r=n-k+1;
        if(q[i].l>q[i].r)q[i].l=1,q[i].r=0;
    }
    block=n/sqrt(m);
    sort(q+1,q+m+1,cmp);
    ull l=1,r=0;
    for(ull i=1;i<=m;i++){
        while (l>q[i].l) add(a[--l]);
        while (r<q[i].r) add(a[++r]);
        while (l<q[i].l) del(a[l++]);
        while (r>q[i].r) del(a[r--]);
        ans[q[i].id]=sum;
    }
    for(ull i=1;i<=m;i++){
        cout<<ans[i]<<"\n";
    }
}