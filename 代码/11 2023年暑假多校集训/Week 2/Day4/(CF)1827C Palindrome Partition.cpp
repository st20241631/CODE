#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=500050;
int n;
int tree[N<<2],lazy[N<<2];
void build(int k,int l,int r){
    tree[k]=lazy[k]=0;
    if(l==r) return;
    int mid=(l+r)>>1;
    build(k<<1,l,mid);
    build(k<<1|1,mid+1,r);
}
void pushdown(int k){
    if(lazy[k]){
        tree[k<<1]=max(tree[k<<1],lazy[k]);
        tree[k<<1|1]=max(tree[k<<1|1],lazy[k]);
        lazy[k<<1]=max(lazy[k<<1],lazy[k]);
        lazy[k<<1|1]=max(lazy[k<<1|1],lazy[k]);
        lazy[k]=0;
    }
}
void update(int k,int l,int r,int x,int y,int val){
    if(x<=l&&y>=r){
        tree[k]= max(tree[k],val);
        lazy[k]= max(lazy[k],val);
        return;
    }
    pushdown(k);
    int mid=(l+r)>>1;
    if(x<=mid) update(k<<1,l,mid,x,y,val);
    if(y>mid) update(k<<1|1,mid+1,r,x,y,val);
    tree[k]=max(tree[k<<1],tree[k<<1|1]);
}
int query(int k,int l,int r,int x){
    if(l==r)return tree[k];
    pushdown(k);
    int mid=(l+r)>>1;
    if(x<=mid) return query(k<<1,l,mid,x);
    else return query(k<<1|1,mid+1,r,x);
}

#define ull unsigned long long
const ull p=1331;
ull hash1[N],hash2[N],po[N];
char s[N];

bool check(int l,int r){
    if(l<1||r>n) return 0;
    ull x=hash1[r]-hash1[l-1];
    ull y=(hash2[r]-hash2[l-1]*po[r-l+1])*po[l-1];
    return x==y;
}

int len[N];
int dp[N];
void solve(){
    cin>>n>>(s+1);
    build(1,1,n);
    for(int i=1;i<=n;i++){
        hash1[i]=hash1[i-1]+s[i]*po[i-1];
        hash2[i]=hash2[i-1]*p+s[i];
    }
    for(int i=1;i<n;i++){
        len[i]=0;
        int l=1,r=n;
        while (l<=r){
            int mid=(l+r)>>1;
            if(check(i-mid+1,i+mid)){
                l=mid+1;
                len[i]=mid;
            }
            else r=mid-1;
        }
        if(len[i])update(1,1,n,i+1,i+len[i],i);
    }
    for(int i=1;i<=n;i++){
        int tmp= query(1,1,n,i);
        if(tmp)tmp=(i-tmp)*2;

        if(tmp)dp[i]=dp[i-tmp]+1;
        else dp[i]=0;
    }
    int ans=0;
    for(int i=1;i<=n;i++)ans+=dp[i];
    cout<<ans<<"\n";
}

signed main(){
    po[0]=1;
    for(int i=1;i<N-10;i++) po[i]=po[i-1]*p;
    int t;
    cin>>t;
    while(t--) solve();
}