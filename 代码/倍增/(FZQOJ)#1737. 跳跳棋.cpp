#include<bits/stdc++.h>
using namespace std;
struct node {
    int x,y,z,step;
}A,B;
int sum;
node solve(node ans,int step){
    for (sum=0;step>0;) {
        int t1=ans.y-ans.x,t2=ans.z-ans.y,tmp;
        if (t1==t2) return ans;
        else if (t1>t2){tmp=min((t1-1)/t2,step);ans.z-=tmp*t2;ans.y-=tmp*t2;}
        else if (t1<t2){tmp=min((t2-1)/t1,step);ans.x+=tmp*t1;ans.y+=tmp*t1;}
        sum+=tmp;step-=tmp;
    }
    return ans;
}
int main() {
    int a,b,c;
    cin>>a>>b>> c;
    if(a>b)swap(a,b);if(a>c)swap(a,c);if(b>c)swap(b,c);
    A=node{a,b,c,0};
    node ans1=solve(A,0x7fffffff);
    A.step=sum;
    cin>>a>>b>> c;
    if(a>b)swap(a,b);if(a>c)swap(a,c);if(b>c)swap(b,c);
    B=node{a,b,c,0};
    node ans2=solve(B,0x7fffffff);
    B.step=sum;
    if(ans1.x!=ans2.x||ans1.y!=ans2.y||ans1.z!=ans2.z){puts("NO");return 0;}
    puts("YES");
    int ans;
    if(A.step<B.step) swap(A,B);
    ans=A.step-B.step;
    A=solve(A,ans);
    int l=0,r=B.step;
    while(l<r){
        int mid=(l+r)>>1;
        node tmp1=solve(A,mid),tmp2=solve(B,mid);
        if(tmp1.x!=tmp2.x||tmp1.y!=tmp2.y||tmp1.z!=tmp2.z)l=mid+1;
        else r=mid;
    }
    cout<<l*2+ans;
    return 0;
}