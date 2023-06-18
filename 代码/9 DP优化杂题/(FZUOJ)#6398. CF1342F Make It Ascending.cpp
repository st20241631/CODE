#include<bits/stdc++.h>
#define ll long long
using namespace std;
struct node{
	int x,y,z;
};
int T,n;
int a[16];
int sum[1<<15];
int dp[16][16][1<<15];
node fa[16][16][1<<15]; 
int id[15];
int main(){
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=0;i<n;i++)cin>>a[i];
        for(int s=0;s<(1<<n);s++){sum[s]=0;for(int i=0;i<n;i++)if((s&(1<<i))!=0) sum[s]+=a[i];}
        for(int i=0;i<=n;i++)for(int j=0;j<=n;j++)for(int s=0;s<(1<<n);s++)dp[i][j][s]=0x3f3f3f3f;
        dp[0][0][0]=0;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                for(int s=0;s<(1<<n);s++){
                    if(dp[i][j][s]!=0x3f3f3f3f){
                        node u={i,j,s};
                        int nex=((1<<n)-1)^s;
                        for(int s0=nex;s0;s0=(s0-1)&nex){
                            if(sum[s0]>dp[i][j][s]&&((s0>>j)!=0)){
                                node v={i+1,j+1+__builtin_ctz(s0>>j),s|s0};
                                dp[v.x][v.y][v.z]=min(dp[v.x][v.y][v.z],sum[s0]);
                                if(dp[v.x][v.y][v.z]==sum[s0]) fa[v.x][v.y][v.z]=u;
                            }
                        }
                    }
                }
            }
        }
        node ans={-1,-1,-1};
        for(int i=n;i>=1;i--){
            for(int j=1;j<=n;j++){
                if(dp[i][j][(1<<n)-1]!=0x3f3f3f3f){
                    ans={i,j,(1<<n)-1};
                    break;
                }
            }
            if(ans.x!=-1) break;
        }
        cout<<n-ans.x<<"\n";
        for(int i=0;i<n;i++) id[i]=i+1;
        while(ans.x!=0){
            node before=fa[ans.x][ans.y][ans.z];
            int s=before.z^ans.z;
            for(int i=0;i<n;i++){
                if((s&(1<<i))!=0&&i!=ans.y-1){
                    cout<<id[i]<<" "<<id[ans.y-1]<<"\n";
                    for(int j=i+1;j<n;j++) id[j]--;
                }
            }
            ans=before;

        }

	}
}