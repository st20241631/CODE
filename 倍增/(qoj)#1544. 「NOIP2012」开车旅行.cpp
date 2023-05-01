#include <bits/stdc++.h>
#define int long long
using namespace std;
const int INF=3e9;
const int MAXN=100005;
int n,m,x0;
int h[MAXN];
int s[MAXN],x[MAXN];
int f[20][MAXN][2],da[20][MAXN][2],db[20][MAXN][2];

//预处理
struct city{
    int id,high;
    bool operator<(const city b)const{
        return high<b.high;
    }
};
multiset<city> S;
void init(){
    //哨兵（防止越界）
    h[0]=INF,h[n+1]=-INF;
    city sentry;
    sentry=city{0,INF};
    S.insert(sentry),S.insert(sentry);
    sentry=city{n+1,-INF};
    S.insert(sentry),S.insert(sentry);

    for(int i=n;i>=1;i--){  //倒序，保证set内的编号为i~n
        int ga=0,gb=0;  //从当前城市出发，小A和小B的下一站（小B：最近，小A：次近）
        city now=city{i,h[i]};
        S.insert(now);
        auto p=S.lower_bound(now);
        p--;    //前驱
        int qid=(*p).id,qval=(*p).high;
        p++,p++;    //后继
        int hid=(*p).id,hval=(*p).high;
        p--;    //原位置
        if(abs(qval-h[i])<=abs(hval-h[i])){//离前驱更近
            gb=qid;
            p--,p--;    //前驱的前驱
            int qqid=(*p).id,qqval=(*p).high;
            if(abs(hval-h[i])>=abs(qqval-h[i]))ga=qqid;
            else ga=hid;
        }
        else{
            gb=hid;
            p++,p++;
            int hhid=(*p).id,hhval=(*p).high;
            if(abs(qval-h[i])>abs(hhval-h[i]))ga=hhid;
            else ga=qid;
        }
        f[0][i][0]=ga;
        f[0][i][1]=gb;
        da[0][i][0]=abs(h[i]-h[ga]);
        db[0][i][1]=abs(h[i]-h[gb]);
    }

    for(int i=1;i<=18;i++){
        for(int j=1;j<=n;j++){
            for(int k=0;k<=1;k++){
                if(i==1){
                    f[1][j][k]=f[0][f[0][j][k]][1-k];
                    da[1][j][k]=da[0][j][k]+da[0][f[0][j][k]][1-k];
                    db[1][j][k]=db[0][j][k]+db[0][f[0][j][k]][1-k];
                }
                else{
                    f[i][j][k]=f[i-1][f[i-1][j][k]][k];
                    da[i][j][k]=da[i-1][j][k]+da[i-1][f[i-1][j][k]][k];
                    db[i][j][k]=db[i-1][j][k]+db[i-1][f[i-1][j][k]][k];
                }
            }
        }
    }

}

//求解
int suma,sumb;
void solve(int s,int x){
    suma=sumb=0;
    int now=s;
    for(int i=18;i>=0;i--){
        if(f[i][now][0]/*防止越界*/&&suma+sumb+da[i][now][0]+db[i][now][0]<=x){
            suma+=da[i][now][0];
            sumb+=db[i][now][0];
            now=f[i][now][0];
        }
    }
}
main(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>h[i];
    cin>>x0;
    cin>>m;
    for(int i=1;i<=m;i++)cin>>s[i]>>x[i];
    init();

    //问题1
    double ans1=INF*1.0;
    int ans2=0;
    for(int i=1;i<=n;i++){
        solve(i,x0);
        double tmp;
        if(sumb==0){
            tmp=INF*0.9;
        }
        else tmp=double(suma)/double(sumb);
        if(ans1>tmp){
            ans1=tmp;
            ans2=i;
        }
        if(ans1==tmp&&h[i]>h[ans2]){
            ans2=i;
        }
    }
    cout<<ans2<<"\n";

    //问题2
    for(int i=1;i<=m;i++){
        solve(s[i],x[i]);
        cout<<suma<<" "<<sumb<<"\n";
    }
}