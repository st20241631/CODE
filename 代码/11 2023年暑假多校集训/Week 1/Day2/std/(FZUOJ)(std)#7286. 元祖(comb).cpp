# include <bits/stdc++.h>
using namespace std;
namespace Base{
	# define mr make_pair
	typedef long long ll;
	typedef double db;
	const int inf = 0x3f3f3f3f, INF = 0x7fffffff;
	const ll  infll = 0x3f3f3f3f3f3f3f3fll, INFll = 0x7fffffffffffffffll;
	template<typename T> void read(T &x){
    	x = 0; int fh = 1; double num = 1.0; char ch = getchar();
		while (!isdigit(ch)){ if (ch == '-') fh = -1; ch = getchar(); }
		while (isdigit(ch)){ x = x * 10 + ch - '0'; ch = getchar(); }
	    if (ch == '.'){
	    	ch = getchar();
	    	while (isdigit(ch)){num /= 10; x = x + num * (ch - '0'); ch = getchar();}
		}
		x = x * fh;
	}
	template<typename T> void chmax(T &x, T y){x = x < y ? y : x;}
	template<typename T> void chmin(T &x, T y){x = x > y ? y : x;}
}
using namespace Base;

const int N = 500050;
struct Node{
	int pl, pr, mn;
}T[N * 3];
int num[N], pre[N], nxt[N], pos[N], ch[N][2], place, n, ori[N], rt;
map <int, int> mp;
pair <int, int> may[N], can[N];

void build(int &p, int l, int r){
	p = ++place;
	T[p].mn = n + 1;
	if (l != r){
		int mid = (l + r) / 2;
		build(T[p].pl, l, mid);
		build(T[p].pr, mid + 1, r);
	}
}

int query(int p, int l, int r, int ql, int qr){
	if (l >= ql && r <= qr) return T[p].mn;
	if (l > qr || r < ql) return inf;
	int mid = (l + r) / 2;
	return min(query(T[p].pl, l, mid, ql, qr), query(T[p].pr, mid + 1, r, ql, qr));
}

void modify(int p, int l, int r, int pos, int val){
	if (l == r){
		T[p].mn = val;
		return;
	}
	int mid = (l + r) / 2;
	if (pos <= mid) modify(T[p].pl, l, mid, pos, val);
		else modify(T[p].pr, mid + 1, r, pos, val);
	T[p].mn = min(T[T[p].pl].mn, T[T[p].pr].mn); 
} 
int main(){
	freopen("comb.in", "r", stdin);
	freopen("comb.out", "w", stdout);
	read(n); 
	int cnt = 0, m = 0, id = 0;
	for (int i = 1; i <= n; i++){
		int x; read(x);
		assert(x <= n);
		if (mp.find(x) == mp.end()) mp[x] = ++cnt, ori[cnt] = x;
		num[i] = mp[x];
	}
	for (int i = 1; i <= n; i++){
		pre[i] = pos[num[i]];
		pos[num[i]] = i;
	}
	for (int i = 1; i <= cnt; i++) pos[i] = n + 1;
	for (int i = n; i >= 1; i--){
		nxt[i] = pos[num[i]];
		pos[num[i]] = i;
	}
	nxt[n + 1] = n + 1;
	for (int i = 1; i <= cnt; i++){
		int l = pos[i], r = nxt[l];
		while (r <= n){
			may[++id] = mr(r, l);
			l = r;
			r = nxt[r];
		}
/*		if (nxt[l] != n + 1) r = nxt[nxt[l]];
		while (r <= n){
			may[++id] = mr(r, l);
			l = nxt[l];
			r = nxt[r];
		}*/
	}
	sort(may + 1, may + id + 1);
	build(rt, 1, n);
	int nowpos = 0, ans = 0;
	for (int i = 1; i <= id; i++){
		int nxtpos = may[i].first - 1;
		for (int j = nowpos + 1; j <= nxtpos; j++){
			modify(rt, 1, n, j, nxt[j]);
			if (pre[j]) modify(rt, 1, n, pre[j], n + 1);
		}
		nowpos = nxtpos;
		int l = may[i].second, r = query(rt, 1, n, l + 1, nxtpos);
		if (r <= n) can[++m] = mr(r, l);
	}
	
	for (int i = 1; i <= cnt; i++){
		int l = pos[i], r = nxt[nxt[nxt[l]]];
		while (r <= n){
			can[++m] = mr(r, l);
			l = nxt[l];
			r = nxt[r];
		}
	}
	sort(can + 1, can + m + 1);
	nowpos = 0;
	for (int i = 1; i <= m; i++){
		if (can[i].second > nowpos){
			nowpos = can[i].first;
			ans++;
			ch[ans][0] = ori[num[can[i].second]];
			ch[ans][1] = ori[num[can[i].first]];
		}
	}
	printf("%d\n", ans * 4);
/*	for (int i = 1; i <= ans; i++){
		printf("%d %d %d %d", ch[i][0], ch[i][1], ch[i][0], ch[i][1]);
		if (i != ans) printf(" ");
	}
	printf("\n"); */
    return 0;
}

