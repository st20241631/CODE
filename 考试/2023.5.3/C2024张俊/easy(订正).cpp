#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=202200;
int n,t;
vector<int> tim[N];
vector<int> ans1;
struct node1{
    int a,b,id;
    bool operator<(const node1&y)const{return a<y.a;}
}a[N];
struct node2{
    int sum1,sum2;//sum1:彻底掌握的知识，sum2:所需的时间
    node2 operator+(const node2&b)const{return node2{sum1+b.sum1,sum2+b.sum2};}
};
struct tree{
    node2 tre[N];
    void clear(){memset(tre,0,sizeof tre);}
    int lowbit(int x) {return x&(-x);}
    void add(int x,node2 v){for(int i=x;i<=n;i+= lowbit(i))tre[i]=tre[i]+v;}
    node2 query(int x){
        node2 ans={0,0};
        for (int i = x; i; i -= lowbit(i)) { ans = ans + tre[i]; }
        return ans;
    }
    node2 querycnt(int x){
        node2 ans={0,0};
        int now=0;
        for(int i=20;i>=0;i--){
            if(((1<<i|now)<=n)&&((ans+tre[1<<i|now]).sum1<=x)) {
                ans = ans + tre[now | (1 << i)];
                now |= (1 << i);
            }
        }
        return ans;
    }

    /*
     querycnt是用来查询树状数组上前缀和小于等于 $x$ 的最大下标 $t$ 并返回对应的前缀和。
     具体实现是利用二分的思想，在树状数组上从高位往低位处理。
     每次判断当前节点加上 $2^i$ 是否小于数组长度并且加上 $2^i$ 后的前缀和小于等于 $x$，如果成立则将当前下标加上 $2^i$，并将前缀和加上 $2^i$ 对应下标的值，直到处理完所有的二进制位。
     这个函数在本题中用来找到满足前缀和大于等于 $mid$ 的最小下标，并返回对应的前缀和。
     在本题中，这个函数被用来找到 $mid$ 的位置，并计算左右两侧前 $mid$ 小个带权值的数集合以及右侧剩余的前 $i-mid$ 小个带权值的数集合的权值和是否小于等于 $t$。
     如果满足条件，则说明存在一个合法的选取方案使得左侧的前 $mid$ 小个数与右侧的前 $i-mid$ 小个数权值和都小于等于 $t$。

                                                ————ChatGPT
     */

}tr1,tr2;//tr1:前缀和,tr2:后缀和
bool check(int mid){
    ans1.clear();
    tr1.clear();
    tr2.clear();
    for(int i=1;i<=n;i++) tr2.add(i,node2{1,a[i].a});
    int sum=0;
    for(int i=1;i<=n;i++){ //枚举学了多少知识
        for(auto id:tim[i]){
            tr1.add(id,node2{1,a[id].a});tr2.add(id,node2{-1,-a[id].a});
            sum++;
        }
        if(i<mid||sum<mid)continue;
        node2 now=tr1.query(i);
        now.sum2+=tr2.query(i).sum2;
        if(now.sum2>t) return false;
        if(now.sum1>=mid){
            for (int j = 1; j <= i; j++)ans1.push_back(j);
            return true;
        }
        node2 w1=tr1.querycnt(mid),w2=tr2.querycnt(i-mid);
        if(w1.sum2+w2.sum2<=t){
            int sum1=0,sum2=0;
            for(int j=1;j<=n;j++){
                if(a[j].b<=i&&sum1+1<=mid)sum1++,ans1.push_back(j);
                else if(a[j].b>i&&sum2+1<=i-mid)sum2++,ans1.push_back(j);
            }
            return true;
        }
    }
    return false;
}
void solve(){
    cin>>n>>t;
    for(int i=1;i<=n;i++){
        cin>>a[i].a>>a[i].b;
        a[i].id=i;
    }
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++)tim[i].clear();
    for(int i=1;i<=n;i++)tim[a[i].b].push_back(i);
    int l=0,r=n,ans=0;
    while (l<=r){
        int mid=(l+r)>>1;
        if(check(mid))ans=mid,l=mid+1;
        else r=mid-1;
    }
    cout<<ans<<"\n";
    check(ans);
    cout<<ans1.size()<<" ";
    for(int i:ans1) cout<<a[i].id<<" ";
    cout<<"\n";
}
signed main(){
    int T;
    cin>>T;
    while (T--)solve();
}
