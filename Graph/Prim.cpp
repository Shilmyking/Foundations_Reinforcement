#if 0

#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>

using namespace std;

#define endl "\n"
#define int long long

const int MAXN = 5e3 + 5;
const int MAXM = 4e5 + 4;
const int INF = 0x3f3f3f3f;

struct Edge {
	int start;
	int end;
	int weight;
	Edge(int s=-1,int e=-1,int w=-1):start(s),end(e),weight(w){}
	bool operator<(const Edge& e) {
		return weight < e.weight;
	}
};

vector<vector<Edge>>edges(MAXM);
bool Query[MAXN + 1];
int nodeCnt = 0;

Edge heap[MAXM];
int heapSize = 0;

int n, m;

void build() {
	for (int i = 0; i <= n; i++) {
		edges[i].clear();
	}
	memset(Query, false, sizeof(Query));
	nodeCnt = 0;

	heapSize = 0;
}

//小根堆实现
//  从i位置开始上浮 调整堆
void heapInsert(int i) {
	// i>0 要不要都行   (i-1)/2  
	// 左孩子  2*i+1  右孩子 2*i+2  要避免右孩子找错父亲
	while (i > 0 && (heap[i] < (heap[(i - 1 ) / 2]))) {
		std::swap(heap[i], heap[(i - 1) / 2]);
		i = (i - 1) / 2;
	}
}

// 下沉（大的下沉）
// 如果当前节点 大于 孩子节点中较小的 下沉
void heapify(int i) {
	int leftSide = 2 * i + 1;
	while (leftSide < heapSize) {
		int smallSide = leftSide + 1 < heapSize && heap[leftSide + 1] < heap[leftSide] ? leftSide + 1 : leftSide;
		smallSide = heap[i] < heap[smallSide] ? i : smallSide;//拿到最小的那个节点
		if (smallSide == i) {
			break;
		}
		std::swap(heap[i], heap[smallSide]);
		i = smallSide;
		leftSide = 2 * i + 1;
	}
}

//加节点
void add(const Edge&e) {
	heap[heapSize] = e;
	heapInsert(heapSize++);//当前位置上浮
}

Edge heapPop() {
	Edge  top = heap[0];
	//最后一个元素换到堆顶再 heapify
	std::swap(heap[0], heap[--heapSize]);
	heapify(0);
	return top;
}

void Prim() {
	int ans = 0;
	//选取1为起点开始算法
	nodeCnt = 1;
	Query[1] = true;
	for (Edge& v : edges[1]) {
		add(v);
	}

	while (heapSize > 0) {
		Edge top = heapPop();
		int u = top.start;
		int v = top.end;
		if (Query[v] == false) {
			nodeCnt++;
			Query[v] = true;
			ans += top.weight;
			for (Edge& e : edges[v]) {//遍历所有邻边  都入堆
				add(e);
			}
		}
	}
	
	if (nodeCnt == n) {
		cout << ans << endl;
	}
	else {
		cout << "orz" << endl;
	}
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	build();
	for (int i = 0,u,v,w; i < m; i++) {
		cin >> u >> v >> w;
		edges[u].push_back(Edge(u, v, w));
		edges[v].push_back(Edge(v, u, w));
	}
	Prim();
}

#endif