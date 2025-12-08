#if 0
//https://www.luogu.com.cn/problem/P3366
#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
using namespace std;
#define endl "\n"

const int MAXN = 5e3 + 5;
const int MAXM = 4e5 + 5;

int cnt = 0;
int head[MAXN];
int nexts[MAXM];
int to[MAXM];
int weight[MAXM];

// 还在堆上的节点就是 还没有加入到图内的节点  还在考虑是否能找到更优的边
// 一旦从 堆上pop了 就代表这个节点已经获得了最优解  不再考虑 

//存储 v + weight
// 下标i是在堆的编号 ---> 数组index
int heap[MAXN][2];
int heapSize = 0;

// 反向索引表
// 如果 Where数组的值为-2 代表进入过堆 然后pop了
// 如果 值为 -1  ，代表还未进入过堆
// 否则 节点编号 --->  在堆内的编号
// where[v] 值为 i --->节点v在堆上i位置  heap[i][0] heap[i][1]
int Where[MAXN];
int nodeCnt=0;

int n, m;

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
	cnt = 0;
	nodeCnt = 0;
	heapSize = 0;
}

// 堆上索引 i 指向的节点 和 索引j指向的节点 进行交换
void Swap(int i, int j) {
	// Where数组 维护的 (节点编号-->堆内的索引编号)
	int vi = heap[i][0];
	int vj = heap[j][0];

	Where[vi] = j;
	Where[vj] = i;

	//std::swap(Where[heap[i][0]], Where[heap[j][0]]);
	//堆上节点的值交换
	std::swap(heap[i][0], heap[j][0]);
	std::swap(heap[i][1], heap[j][1]);
}

//小根堆实现
//上浮
void heapInsert(int i) {
	while (heap[i][1] < heap[((i - 1) / 2)][1]) {
		Swap(i, (i - 1) / 2);
		i = (i - 1) / 2;
	}
}

//下沉
void heapify(int i) {
	int leftSide = i * 2 + 1;
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

//传入头边号 能够找到 to 和 weight
void addOrUpdate(int ei) {
	int v = to[ei], w = weight[ei];
	if (Where[v] == -2) {
		return;
	}
	else if (Where[v] == -1) {//v这个节点还未入堆
		heap[heapSize][0] = v;
		heap[heapSize][1] = w;
		Where[v] = heapSize++;
		heapInsert(Where[v]);//其实就是 heapSize - 1
	}
	else if (Where[v] >= 0) { //入过堆 check是否能更新在堆内的weight
		int heapIndex = Where[v];
		heap[heapIndex][1] = std::min(heap[heapIndex][1], w);
		heapInsert(heapIndex);//如果能更新 -->上浮调整
	}
}

//要传参出去 为了省事不用pair了  &即可
void heapPop(int &v,int &w) {
	v = heap[0][0];
	w = heap[0][1];
	// heapSize - 1位置是有效元素
	Swap(0, --heapSize);
	heapify(0);
	Where[v] = -2;
	nodeCnt++;
}

void Prim() {
	//还是选取任意节点开始算法
	nodeCnt = 1;
	Where[1] = -2;//选取1  设置为-2 代表不用再往堆上加入节点1
	for (int ei = head[1]; ei > 0; ei = nexts[ei]) {
		addOrUpdate(ei);
	}
	int ans = 0, v, w;
	while (heapSize > 0) {
		// 当前
		heapPop(v, w);
		ans += w;
		for (int ei = head[v]; ei > 0; ei = nexts[ei]) {
			addOrUpdate(ei);
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

	for (int i = 0,u,v,w; i < m; i++){
		cin >> u >> v >> w;
		addEdge(u, v, w);
		addEdge(v, u, w);
	}
	Prim();
}

#endif