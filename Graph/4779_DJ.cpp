
#if 0

#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
#include<queue>
#include<functional>

using namespace std;
#define endl "\n"

const int MAXN = 1e5 + 5;
const int MAXM = 2e5 + 5;
const int INF = 0x3f3f3f3f;

using PII = pair<int, int>;
struct Edge {
	int end;
	int weight;
	Edge(int e = 0, int w = 0) :end(e), weight(w) {}
	bool operator<(const Edge& e) {
		return weight < e.weight;
	}
};

//邻接表 实现
bool visited[MAXN];
int dist[MAXN];

int n, m, s;

void build() {
	memset(visited, false, sizeof(visited));
	memset(dist, INF, sizeof(dist));

}
void DJ(const vector<vector<Edge>>&Graph) {
	// dist距离 + 节点编号
	priority_queue<PII,vector<PII>,std::greater<PII>>pq;
	//起点为s
	pq.push({ 0,s });
	dist[s] = 0;
	while (!pq.empty()) {
		PII top = pq.top(); pq.pop();
		if (visited[top.second]) {
			continue;
		}
		visited[top.second] = true;
		for (auto& edge : Graph[top.second]) {
			int to = edge.end, dis = edge.weight;
			if (!visited[to] && dist[to] > dis + top.first) {
				dist[to] = dis + top.first;
				pq.push({ dist[to],to });
			}
		}
	}
	cout << dist[1];
	for (int i = 2; i <= n; i++) {
		cout << " " << dist[i];
	}
	cout << endl;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m >> s;
	//0 号为弃而不用
	build();
	vector<vector<Edge>>Graph(n+1);
	for (int i = 0, u, v, w; i < m; i++) {
		cin >> u >> v >> w;
		Graph[u].push_back(Edge(v, w));
	}
	DJ(Graph);
}

#endif