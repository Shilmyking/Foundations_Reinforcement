
#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>

#include<cstring>

using namespace std;
#define endl "\n"

const int MAXN = 2e3 + 5;
const int MAXM = (3e3 + 5) * 2;
int INF = 0x3f3f3f3f;

int head[MAXN];
int nexts[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt=0;

const int MAXQ = 1e7 + 5;
int dist[MAXN];
int update[MAXN];//松弛的次数  如果松弛次数达到 n (1-based) --->存在负环
int que[MAXQ], l = 0, r = 0;//那些节点被放入了队列  处理负环
bool enter[MAXN];//节点是否在队列内

int t, n, m;

void build() {
	memset(head, 0, sizeof(head));
	memset(nexts, 0, sizeof(nexts));
	cnt = 0;

	memset(dist, INF, sizeof(dist));
	memset(update, 0, sizeof(update));
	memset(enter, false, sizeof(enter));
	l = r = 0;
}

void addEdge(int u,int v,int w) {
	nexts[++cnt] = head[u];
	to[cnt] = v;
	weight[cnt] = w;
	head[u] = cnt;
}

bool SPFA() {
	//源点为1
	dist[1] = 0;
	que[r++] = 1;
	enter[1] = true;
	update[1] = 1;

	while (l < r) {
		int u = que[l++];
		enter[u] = false;//出队了  后续还能入队列

		for (int ei = head[u]; ei > 0; ei = nexts[ei]) {
			if (dist[u] + weight[ei] < dist[to[ei]]) {
				//能进行松弛
				dist[to[ei]] = dist[u] + weight[ei];
				if (enter[to[ei]] == false) {//已经在队列的话 无需入队
					if (++update[to[ei]] > n - 1) {//1-based  如果松弛次数到达n次就是存在负环
						return true;
					}
					que[r++] = to[ei];
					enter[to[ei]] = true;
				}

			}
		}
	}

	return false;
}

signed main() {
	cin >> t;
	while (t--) {
		cin >> n >> m;
		build();
		for (int i = 0, u, v, w; i < m; i++) {
			cin >> u >> v >> w;
			if (w >= 0) {
				addEdge(u, v, w);
				addEdge(v, u, w);
			}
			else {
				//负边
				addEdge(u, v, w);
			}
		}
		cout << (SPFA() ? "YES" : "NO") << endl;
	}
}