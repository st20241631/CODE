#include<bits/stdc++.h>

#define int long long
using namespace std;
const int N = 202200;
int n;
int t;
struct hh {
    int a, b, id;
} a[N];
vector<int> V[N];

struct hhh {
    int a, b;

    const hhh operator+(const hhh &x) const { return hhh{a + x.a, b + x.b}; }
};

struct BIT {
    hhh tr[N];
    void clear() { for (int i = 0; i <= n + 1; i++) tr[i] = hhh{0, 0}; }
    void add(int x, hhh w) { for (int i = x; i <= n; i += i & -i)tr[i] = tr[i] + w; }
    hhh query(int x) {
        hhh res = {0, 0};
        for (int i = x; i; i -= (i & -i))res = res + tr[i];
        return res;
    }
    hhh querycnt(int x) {
        int tmp = 0;
        hhh res = {0, 0};
        for (int i = 20; i >= 0; i--)
            if ((1 << i | tmp) <= n && (res + tr[1 << i | tmp]).a <= x)
                tmp |= 1 << i, res = res + tr[tmp];
        return res;
    }
} tr1, tr2, tr3;
vector<int> ans1;
int check(int mid) {
    ans1.clear();
    memcpy(tr2.tr, tr3.tr, sizeof(hhh) * (n + 10));
    tr1.clear();
    int tot = 0;
    for (int i = 1; i <= n; i++) {
        for (auto id: V[i]) tr1.add(id, {1, a[id].a}), tr2.add(id, {-1, -a[id].a}), ++tot;
        if (i < mid || tot < mid) continue;
        hhh w = tr1.query(i);
        w.b += tr2.query(i).b;
        if (w.b > t) return 0;
        if (w.a >= mid) {
            for (int j = 1; j <= i; j++) ans1.push_back(j);
            return 1;
        }
        hhh w1 = tr1.querycnt(mid), w2 = tr2.querycnt(i - mid);
        if (w1.b + w2.b <= t) {
            int t1 = 0, t2 = 0;
            for (int j = 1; j <= n; j++)
                if (a[j].b <= i && t1 + 1 <= mid) ++t1, ans1.push_back(j);
                else if (a[j].b > i && t2 + 1 <= i - mid) ++t2, ans1.push_back(j);
            return 1;
        }
    }
    return 0;
}
int cmp(hh x, hh y) { return x.a < y.a; }
void work() {
    cin >> n >> t;
    for (int i = 1; i <= n; i++)cin >> a[i].a >> a[i].b, a[i].id = i;
    sort(a + 1, a + n + 1, cmp);
    for (int i = 1; i <= n; i++)V[a[i].b].push_back(i);
    tr3.clear();
    for (int i = 1; i <= n; i++)tr3.add(i, {1, a[i].a});
    int l = 0, r = n, ans = 0;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid)) ans = mid, l = mid + 1;
        else r = mid - 1;
    }
    cout << ans << "\n";
    check(ans);
    cout << ans1.size() << " ";
    for (auto i: ans1)cout << a[i].id << " ";
    puts("");
    for (int i = 1; i <= n; i++) V[i].clear();
    tr3.clear();
}
signed main() {
//    freopen("easy.in", "r", stdin);
//    freopen("easy.out", "w", stdout);
    int T;
    cin >> T;
    while (T--) work();
    return 0;
}
