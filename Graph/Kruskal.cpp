#if 0
#include<iostream>
#include<algorithm>
using namespace std;

#define endl "\n"
#define int long long

const int MAXN = 5e3 + 5;
const int MAXM = 2e5 + 1;
const int INF = 0x3f3f3f3f;

struct Edge {
	int from;
	int to;
	int weight;
	Edge(int f=-INF,int t=-INF,int w=-INF):from(f),to(t),weight(w){}
	bool operator<(const Edge& e) {
		return weight < e.weight;
	}
};
Edge edges[MAXM];

int fa[MAXN];
int sets;
int n, m;

void build() {
	for (int i = 0; i < MAXN; i++) {
		fa[i] = i;
	}
	sets = n;
}

int find(int i) {
	return fa[i] == i ? fa[i] : fa[i] = find(fa[i]);
}

bool isSameSet(int i, int j) {
	return find(i) == find(j);
}

void Union(int l, int r) {
	fa[find(l)] = find(r);
	sets--;
}

int Kruskal() {
	//从任意起点开始  
	// weight 从小到大考虑每一条边
	sort(edges + 1, edges + m);
	int ans = 0;
	for (int i = 1; i <= m; i++) {
		int u = edges[i].from;
		int v = edges[i].to;
		int w = edges[i].weight;
		if (!isSameSet(u, v)) {
			Union(u, v);
			ans += w;
		}
		if (sets == 1) {
			break;
		}
	}
	return ans;
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> n >> m;
	build();

	for (int i = 1; i <= m; i++) {
		cin >> edges[i].from >> edges[i].to >> edges[i].weight;
	}
	int ans = Kruskal();
	if (sets != 1) {
		cout << "orz" << endl;
	}
	else {
		cout << ans << endl;
	}
}

#endif