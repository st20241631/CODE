#include <bits/stdc++.h>
#define int long long
using namespace std;
vector<int> G[500000];
bool vis[500000];
int cnt[3];
void dfs(int x, int color) {
    cnt[color]++;
    vis[x]=true;
    for (int y: G[x]) {
        if (vis[y]) continue;
        dfs(y, 3 - color);
    }
}
main() {
    int n;
    cin >> n;
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    dfs(1, 1);
    int ans=cnt[1]*cnt[2]-n+1;
    cout<<ans;
}