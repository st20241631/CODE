#include<bits/stdc++.h>
using namespace std;
const long long MAXN = 100000;
long long c[5], d[5];
long long n;
long long dp[MAXN];
int main() {
    for (long long i = 1; i <= 4; i++)cin >> c[i];
    cin >> n;
    dp[0] = 1;
    for (long long i = 1; i <= 4; i++) {
        for (long long j = c[i]; j < MAXN; j++) {
            dp[j] += dp[j - c[i]];
        }
    }
    while (n--) {
        long long s;
        cin >> d[1] >> d[2] >> d[3] >> d[4] >> s;
        long long ans = dp[s];
        for (long long i = 1; i <= 15; i++) { //0001~1111(二进制表示子集)
            long long t = s, sum = 0;
            for (long long tmp = i, id = 1; tmp; tmp >>= 1, id++) {
                if (tmp & 1)sum++,t -= (d[id] * c[id] + c[id]);
            }
            if (t >= 0) {
                if (sum & 1)ans -= dp[t];
                else ans += dp[t];
            }
        }
        cout << ans << "\n";

    }
    return 0;
}
