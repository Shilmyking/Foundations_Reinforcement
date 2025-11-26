
// 文艺平衡树，Splay实现范围翻转
// 长度为n的序列，下标从1开始，一开始序列为1, 2, ..., n
// 接下来会有k个操作，每个操作给定l，r，表示从l到r范围上的所有数字翻转
// 做完k次操作后，从左到右打印所有数字
// 1 <= n, k <= 10^5
// 测试链接 : https://www.luogu.com.cn/problem/P3391
#if 0
#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;
#define endl "\n"
const int MAXN = 1e5 + 5;
const int INF = 0x3f3f3f3f;

int cnt = 0;
int head = 0;
int key[MAXN];
int ls[MAXN];
int rs[MAXN];
int fa[MAXN];
int sz[MAXN];

bool Rev[MAXN];

int stk[MAXN];
int si = 0;//非递归 可能爆栈

int ans[MAXN];
int ansi=0;

//Splay 树实现需要左右垫一个数字  区间操作嘛

void up(int i) {
	sz[i] = sz[ls[i]] + sz[rs[i]] + 1;
}

void down(int i) {
	if (Rev[i]) {
		Rev[ls[i]] = !Rev[ls[i]];
		Rev[rs[i]] = !Rev[rs[i]];
		std::swap(ls[i], rs[i]);
		Rev[i] = false;
	}
}
int leftOrRight(int i) {
	return ls[fa[i]] == i ? 0 : 1;
}

void Rotate(int i) {
	int f = fa[i], g = fa[f], soni = leftOrRight(i), sonf = leftOrRight(f);
	if (soni == 1) {
		//左旋
		rs[f] = ls[i];
		if (rs[f] != 0) {
			fa[rs[f]] = f;
		}
		ls[i] = f;
	}
	else {
		ls[f] = rs[i];
		if (ls[f] != 0) {
			fa[ls[f]] = f;
		}
		rs[i] = f;
	}//设置好旋转关系
	// 一定是要 g 不为0  切记0节点特判
	if (g != 0) {
		if (sonf == 0) {
			ls[g] = i;
		}
		else {
			rs[g] = i;
		}
	}
	//设置fa
	fa[f] = i;
	fa[i] = g;
	up(f);
	up(i);
}

// 提根操作  大部分细节都早Rotate内 做完了
// 这里主要就是判断 三种节点上移的情况
// 设置好 i 和 f  最后一个判断goal是否为0 -->是否换head
void Splay(int i, int goal) {
	int f = fa[i], g = fa[f];
	while (f != goal) {
		//两个两个节点看  
		if (g != goal) {
			if (leftOrRight(i) == leftOrRight(f)) {
				//一字型  先提f 再提i
				Rotate(f);
			}
			else {
				Rotate(i);
			}
		}
		//大家都要做的Rotate
		Rotate(i);
		f = fa[i];
		g = fa[f];
	}
	if (goal == 0) {
		head = i;
	}
}

//查找排名为rank的 节点编号
//内置函数 不能提根
int find(int rank) {
	int i = head;
	while (i != 0) {
		//记得下发 才能正确查询信息
		down(i);
		if (sz[ls[i]] + 1 < rank) {
			rank -= sz[ls[i]] + 1;
			i = rs[i];
		}
		else if (sz[ls[i]] >= rank) {
			i = ls[i];
		}
		else if (sz[ls[i]] + 1 == rank) {
			return i;
		}
	}
	return 0;
}


// 需要在最左/最右垫一个数字  防止越界
void add(int num) {
	//每次加入一个数字  Splay到head
	key[++cnt] = num;
	fa[cnt] = head;
	sz[cnt] = 1;

	rs[head] = cnt;//因为每次都是 把新加入的数字Splay到head 
	//这题 从小到大加入数字  可以直接这样
	//标准的写法是 从head往下找到nullptr位置然后加入数字
	Splay(cnt, 0);
}

//中序遍历的 范围 l-r
void Reverse(int l, int r) {
	//这个范围内的数字 翻转 那就是两次Splay 把这个区间的节点都旋转上来
	//维护中序遍历相对次序  这里 节点编号...
	
	//先找到 对应位置的 节点编号 再Splay
	
	int fL = find(l - 1);
	Splay(fL, 0);//右侧就是都是大于的部分

	int fR = find(r + 1);
	Splay(fR, head);
	//现在 ls[rs[head]] 就是需要逆序的部分
	Rev[ls[rs[head]]] = !Rev[ls[rs[head]]];
}

// 以i节点为head的子树 开始做inOrder
void inOrder(int i) {
	if (i != 0) {
		down(i);
		inOrder(ls[i]);
		ans[++ansi] = key[i];
		inOrder(rs[i]);
	}
}

void inOrder() {
	si = 0;
	int i = head;
	while (si > 0 || i != 0) {
		//只要存在左树 就一直去左树处理
		// 然后 如果存在右树的话 去右树
		if (i != 0) {// i!=0 !!!   只要现在着个节点不为nullptr 就去左树看
			//把左树处理完
			down(i);//lazy tag下发
			stk[si++] = i;
			i = ls[i];
		}
		else{//当前节点为nullptr了  回溯
			i = stk[--si];
			//再次回到这个节点就是 第二次了  -->收集
			ans[++ansi] = key[i];
			i = rs[i];// 收集完自己的左树 + 自己 去右树查看
		}
	}
}

int n, m;
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> n >> m;
	add(0);
	for (int i = 1; i <= n; i++) {
		add(i);
	}
	add(0);
	for (int i = 0, l, r; i < m; i++) {
		cin >> l >> r;
		Reverse(l+1, r+1);//最左侧垫了一个数字
	}
	//inOrder(head);
	inOrder();
	cout << ans[2];
	for (int i = 3; i < ansi; i++) {
		cout << " " << ans[i];
	}
	cout << endl;
}
#endif