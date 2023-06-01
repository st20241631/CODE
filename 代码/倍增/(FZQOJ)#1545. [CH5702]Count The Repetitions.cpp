#include<bits/stdc++.h>
using namespace std;
string s1, s2;
long long n1, n2;
long long dp[200][50];
void solve() {
    memset(dp, 0, sizeof dp);
    long long len1 = s1.size(), len2 = s2.size();
    for (long long i = 0; i < len1; i++) {
        dp[i][0] = 0;
        long long pos = i;
        for (long long j = 0; j < len2; j++) {
            int cnt = 0;
            while (s1[pos] != s2[j]) {
                if (++cnt >= len1){
                    cout<<"0\n";
                    return;
                }
                pos = (pos + 1) % len1;
            }
            pos = (pos + 1) % len1;
            dp[i][0] += cnt + 1;
        }
    }
    for (long long j = 1; j <= 30; j++) {
        for (long long i = 0; i < len1; i++) {
            dp[i][j] = dp[i][j - 1] + dp[(i + dp[i][j - 1]) % len1][j - 1];
        }
    }
    long long ans = 0;
    long long now = 0;
    for (long long i = 30; i >= 0; i--) {
        if (now + dp[now % len1][i] <= len1 * n1) {
            now = (now + dp[now % len1][i]);
            ans += 1 << i;
        }
    }
    cout << ans / n2 << "\n";
}
int main() {
    while (cin >> s2 >> n2 >> s1 >> n1) solve();
    return 0;
}