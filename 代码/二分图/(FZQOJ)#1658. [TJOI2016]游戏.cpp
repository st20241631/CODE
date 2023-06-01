#include <bits/stdc++.h>

using namespace std;
string s[100];
int x[100][100], y[100][100];//记录每个点所属的横/纵块
int cntx, cnty;
vector<int> G[100000];
bool vis[100000];
int match[100000];

bool dfs(int x) {
    for (int y: G[x]) {
        if (vis[y]) continue;
        vis[y] = true;
        if (!match[y] || dfs(match[y])) {
            match[y] = x;
            return true;
        }
    }
    return false;
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)cin >> s[i];
    bool flag = false;
    for (int i = 1; i <= n; i++) {
        flag = false;
        for (int j = 0; j < m; j++) {
            if (s[i][j] == '*') {
                if (!flag) {
                    cntx++;
                    flag = true;
                }
                x[i][j] = cntx;
            } else if (s[i][j] == '#') flag = false;
        }
    }
    for (int j = 0; j < m; j++) {
        flag = false;
        for (int i = 1; i <= n; i++) {
            if (s[i][j] == '*') {
                if (!flag) {
                    cnty++;
                    flag = true;
                }
                y[i][j] = cnty;
            } else if (s[i][j] == '#') flag = false;
        }
    }
    for (int i = 1; i <= cntx; i++) G[i].clear();
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < m; j++) {
            if (x[i][j] && y[i][j]) {
                G[x[i][j]].push_back(y[i][j]);
            }
        }
    }
    int ans = 0;
    memset(match, 0, sizeof match);
    for (int i = 1; i <= cntx; i++) {
        memset(vis, false, sizeof vis);
        if (dfs(i)) ans++;
    }
    printf("%d\n", ans);


}