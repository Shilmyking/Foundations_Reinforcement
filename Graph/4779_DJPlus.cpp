
#include<iostream>
#include<vector>
#include<queue>
#include<functional>
#include<list>
#include<cstring>

using namespace std;
#define int long long
#define endl "\n"

const int MAXN = 1e5 + 5;
const int MAXM = 2e5 + 5;
const int INF = 0x3f3f3f3f3f3f3f3fLL;

int head[MAXN];
int nexts[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt;

//反向索引堆   这里可以根据index找到对应在堆上的位置 也就是无需存储 (distance,node)
//只存储 dis就行  根据Where数组获取在heap的位置
int heap[MAXN];  //存储node节点ID
int Where[MAXN]; //存储node节点在堆上的位置
int heapSize;

int Distance[MAXN];//源点到这个位置的最短路径

int n, m, s;
void build() {
	memset(head, 0, sizeof(head));
	memset(nexts, 0, sizeof(nexts));
	memset(to, 0, sizeof(to));
	memset(weight, 0, sizeof(weight));
	cnt = 1;

	heapSize = 0;
	memset(Where, -1, sizeof(Where));
	//Distance 赋值为无穷大
	//for (int i = 1; i <= n; i++) {
	//	Distance[i] = INF;
	//}
	memset(Distance, INF, sizeof(Distance));  //memset只能初始化为0和-1？？
}

void addEdge(int u, int v, int w) {
	nexts[cnt] = head[u];

	to[cnt] = v;
	weight[cnt] = w;

	head[u] = cnt++;
}

//swap 值还有
void Swap(int i, int j) {
	//需要交换的有两个  堆的值  反向索引Where数组的值
	std::swap(heap[i], heap[j]);
	//where[节点id] = 在堆上的位置
	//下面就是两个节点在堆上的位置交换
	Where[heap[i]] = i;
	Where[heap[j]] = j;
}

// 还是没理解反向索引堆
// 这里需要比较distance  所以存储在heap的是node
// 现在是要建一个小根堆
//上浮操作 从i位置开始
void heapInsert(int i) {
	//小根堆   你的Distance比父节点小 就交换
	while (i > 0 && Distance[heap[i]] < Distance[heap[(i - 1) / 2]]) {//heap[i]对应的才是节点
		Swap(i, (i - 1) / 2);
		i = (i - 1) / 2;
	}
}

//下沉  如果值更大就下沉
//小根堆是以当前节点为头节点的子树下，头节点值最小
//如果自己比左右孩子小的那个还要小就下沉  小的孩子上来
void heapify(int i) {
	int left = 2 * i + 1;
	//没有孩子 或者自己符合条件了就停
	while (left < heapSize) {
		int smallNode = left + 1 < heapSize && Distance[heap[left + 1]] < Distance[heap[left]] ? left + 1 : left;
		smallNode = Distance[heap[i]] < Distance[heap[smallNode]] ? i : smallNode;
		if (smallNode == i) {//自己就是最小的 调整好了
			break;
		}
		//自己更大一点 和小的交换
		Swap(i, smallNode);
		i = smallNode;
		left = 2 * i + 1;
	}
}

int pop() {
	int ans = heap[0];
	Swap(0, --heapSize);
	heapify(0);//堆顶开始下沉
	Where[ans] = -2;//这个节点已经真的从堆顶pop出过了
	return ans;
}

int top() {
	return heap[0];
}

bool isEmpty() {
	return heapSize == 0;
}

//是否需要处理这一条边
//传入到的节点v 和 路径w
void addOrUpdateOrIgnore(int v, int w) {
	//如果 where == -2 略过
	if (Where[v] == -1) {
		//还没有加入过
		heap[heapSize] = v;//存储节点
		Where[v] = heapSize;//这个节点在堆的这个下标位置
		Distance[v] = w;
		heapInsert(heapSize++);
	}
	else if (Where[v] >= 0) {//也存在在堆顶的可能性
		Distance[v] = std::min(Distance[v], w);//如果小就更新  
		heapInsert(Where[v]);//可能值变小了，向上调整
	}
}

//传入起点
void dj(int k) {
	addOrUpdateOrIgnore(k, 0);
	while (!isEmpty()) {
		int top = pop();//获取堆顶节点ID
		for (int ei = head[top]; ei > 0; ei = nexts[ei]) {
			//ei是头边号
			addOrUpdateOrIgnore(to[ei], Distance[top] + weight[ei]);
		}
	}
}

#if 0
signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	// 点 边 起点
	cin >> n >> m >> s;
	build();
	for (int i = 1, u, v, w; i <= m; i++) {
		cin >> u >> v >> w;
		addEdge(u, v, w);
	}
	dj(s);
	cout << Distance[1];
	for (int i = 2; i <= n; i++) {
		cout << " " << Distance[i];
	}
	cout << endl;

}
#endif


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