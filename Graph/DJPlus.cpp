
#if 0

#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
using namespace std;
#define endl "\n"

const int MAXN = 1e5 + 5;
const int MAXM = 2e5 + 5;
const int INF = 0x3f3f3f3f;

int cnt = 0;
int head[MAXN];
int nexts[MAXM];
int to[MAXM];
int weight[MAXM];

// 存储 节点编号 + distance
// 下标i是在堆的编号 ---> 数组index
int heap[MAXN][2];
int heapSize = 0;

int Where[MAXN];

int dist[MAXN];

int n, m,s;

void addEdge(int u, int v, int w) {
	nexts[++cnt] = head[u];
	to[cnt] = v;
	weight[cnt] = w;
	head[u] = cnt;
}

void build() {
	memset(head, 0, sizeof(head));
	memset(nexts, 0, sizeof(nexts));
	memset(Where, -1, sizeof(Where));
	memset(dist, INF, sizeof(dist));

	cnt = 0;
	heapSize = 0;
}

//堆上节点交换
// 传入节点编号
void Swap(int i, int j) {
	//到达的节点
	int vi = heap[i][0];
	int vj = heap[j][0];
	Where[vi] = j;//
	Where[vj] = i;

	std::swap(heap[i][0], heap[j][0]);
	std::swap(heap[i][1], heap[j][1]);
}


//小根堆
//上浮
void heapInsert(int i) {
	while (i>0&&heap[i][1] < heap[(i - 1) / 2][1]) {
		Swap(i, (i - 1) / 2);
		i = (i - 1) / 2;
	}
}

//下沉
void heapify(int i) {
	int leftSide = 2 * i + 1;
	while (leftSide < heapSize) {
		int small = leftSide + 1 < heapSize && heap[leftSide][1] > heap[leftSide + 1][1] ? leftSide + 1 : leftSide;
		small = heap[i][1] < heap[small][1] ? i : small;
		if (small == i) {
			break;
		}
		Swap(i, small);
		i = small;
		leftSide = i * 2 + 1;
	}
}

//传入的是 头边号
void addOrUpdate(int i ,int dis) {
	int v = to[i], w = weight[i];
	if (Where[v] == -2) {
		return;
	}
	else if (Where[v] == -1) {//未入堆，现在入堆
		heap[heapSize][0] = v;
		heap[heapSize][1] = dis + w;
		dist[v] = dis + w;
		Where[v] = heapSize;
		heapInsert(heapSize++);
	}
	else if (Where[v] >= 0) {
		dist[v] = std::min(dist[v], dis + w);
		heap[Where[v]][1] = dist[v];
		//变小 -->上浮
		heapInsert(Where[v]);
	}
}

void pop(int& v) {
	v = heap[0][0];// dis可以借助dist数组取到
	//先 Swap 再Where  *** 大错误 
	Swap(0, --heapSize);
	heapify(0);
	Where[v] = -2;
}

void DJ() {
	//起点为s
	dist[s] = 0;
	Where[s] = 0;
	heap[0][0] = s;
	heap[0][1] = 0;
	heapSize++;

	while (heapSize > 0) {
		int v;
		pop(v);
		for (int ei = head[v]; ei > 0; ei = nexts[ei]) {
			addOrUpdate(ei, dist[v]);
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
	build();
	for (int i = 0, u, v, w; i < m; i++) {
		cin >> u >> v >> w;
		addEdge(u, v, w);
	}
	DJ();
}

#endif