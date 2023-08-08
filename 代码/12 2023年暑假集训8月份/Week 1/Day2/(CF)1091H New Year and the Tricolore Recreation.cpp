#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=200050;
int prime[N+10],tot;
bool flag[N+10];
void init(){
    for(int i=2;i<N;i++){
        if(!flag[i]) prime[++tot]=i;
        for(int j=1;j<=tot&&i*prime[j]<N;j++){
            flag[i*prime[j]]=true;
            if(i%prime[j]==0) break;
        }
    }
}
bitset<N+10> pri,s[65];
int sg[N+10];
signed main(){
    init();
    for(int i=1;i<=tot;i++) pri[prime[i]]=1;
    int n,f;
    cin>>n>>f;
    for(int i=1;i<=tot;i++){
        for(int j=i;j<=tot;j++){
            if(prime[i]*prime[j]>=N) break;
            pri[prime[i]*prime[j]]=1;
        }
    }
    pri[f]=0;
    for(int i=1;i<N;i++){
        while (s[sg[i]][i]) sg[i]++;
        s[sg[i]]|=pri<<i;
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        int a,b,c;
        cin>>a>>b>>c;
        ans^=sg[b-a]^sg[c-b];
    }
    if(ans!=0) puts("Alice\nBob");
    else puts("Bob\nAlice");
}