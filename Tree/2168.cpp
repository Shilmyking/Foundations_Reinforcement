#include<iostream>
#include<algorithm>
#include<cstdalign>
#include<cstring>
#include<string>
#include<queue>

using namespace std;
#define int long long

const int MAXN = (1e5 + 100)*2;
const int MAXK = 10;// 9
int n, k;

int ans = 0;

//一个节点 Weight cnt
struct Node {
	int weight;
	int height;
	//下级节点 存储节点编号
	//int nexts[MAXK];
	//默认高度为1
	Node(int weight = 0, int height = 1) :weight(weight), height(height) {
		//memset(nexts, 0, sizeof(nexts));
	}
	bool operator<(const Node& n)const {
		//比大小  必须带上 height  ？？
		return weight == n.weight ? height > n.height : weight > n.weight;
	}
};
//下级节点

void build() {
	ans = 0;

}
Node Tree[MAXN][MAXK];//当前节点 以及下级节点
Node nodes[MAXN];
int cnt = 0;

int init(int w,int h) {
	nodes[++cnt] = Node(w, h);
	return cnt;
}



//如果最后需要建树？？

priority_queue<Node>pq;

/*
对于k叉哈夫曼树的求解,直观的想法是在贪心的基础上,改为每次从堆中去除最小的k个权值合并。
然而，仔细思考可以发现，如果在执行最后一次循环时，堆的大小在（2~k-1）之间（不足以取出k个），那么整个哈夫曼树的根的子节点个数就小于k。
这显然不是最优解————我们任意取哈夫曼树中一个深度最大的节点，改为树根的子节点，就会使∑wi​∗li变小。
因此，我们应该在执行上述贪心算法之前，补加一些额外的权值为0的叶子节点，使叶子节点的个树满足(n-1)%(k-1)=0。
*/


// K 进制字符串
// 0~k-1
// 每次K个节点 但是最后可能不足K个节点 所以借助0权值的节点 确保root节点下都存在孩子节点


// 重新编码之后的长度
// 最长字符串的最短 

// 在进行遍历节点 生成哈夫曼树的过程就可以收集答案 
// 不必担心 高度的问题 父节点会解决

void compute() {
	while (pq.size()>=k) {
		
		//每轮k个 需要记录当前的height
		int nextWeight = 0, nextHeight = 0;
		for (int i = 0; i < k; i++) {
			Node top = pq.top(); pq.pop();
			nextHeight = std::max(top.height, nextHeight);//当前层的最大值
			nextWeight += top.weight;
		}
		ans += nextWeight;
		pq.push(Node(nextWeight, nextHeight+1));//下一层
	}
	//最后算完就还有一个节点 也就是 root
	cout << ans << endl << (pq.top().height - 1) << endl;
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	// n个单词 使用k进制  1位标识k种情况
	// 对应 出现的词频
	cin >> n >> k;
	build();
	for (int i = 0,w; i < n; i++) {
		cin >> w;
		pq.push({ Node(w,1) });
	}
	//还需要满为k的倍数个
	while ((pq.size() - 1) % (k - 1) != 0) {
		pq.push(Node());
	}
	compute();
}


