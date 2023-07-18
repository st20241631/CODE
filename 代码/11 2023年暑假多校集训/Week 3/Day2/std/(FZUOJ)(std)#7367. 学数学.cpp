#include <bits/stdc++.h>
#define ll long long
#define mp make_pair
#define fi first
#define se second
#define pb push_back
#define vi vector<int>
#define pi pair<int, int>
#define mod 998244353
template<typename T> bool chkmin(T &a, T b){return (b < a) ? a = b, 1 : 0;}
template<typename T> bool chkmax(T &a, T b){return (b > a) ? a = b, 1 : 0;}
ll ksm(ll a, ll b) {if (b == 0) return 1; ll ns = ksm(a, b >> 1); ns = ns * ns % mod; if (b & 1) ns = ns * a % mod; return ns;}
using namespace std;
const int maxn = 2000005;
ll c[maxn];
int cnt = 0;
int main() {
    freopen("math.in","r",stdin);
    freopen("math.out","w",stdout);
    const ll inf = 1e18;
    for (int i = 1; 1; i++) {
        ll a = i, b = 1ll * i * i * i;
        if (b - 2 > inf) break;
        ll k = 1ll * i * i;
        c[cnt++] = b;
        if (i == 1) continue;
        while (1) {
            if (1.0 * k * b - a > 2 * inf) break;
            a = k * b - a;
            swap(a, b);
            c[cnt++] = b;

        }
    }
    sort(c, c + cnt);
    int t;
    cin >> t;
    while (t--) {
        ll n;
        scanf("%lld", &n);
        int p = lower_bound(c, c + cnt, n + 1) - c;
        printf("%d\n", p);
    }
    return 0;
}