
// 维护数列
// 初始时给定一个数列，实现如下六种操作
// INSERT posi tot ...  : 在第posi个数字之后，插入长度为tot的数组，由...代表
// DELETE posi tot      : 从第posi个数字开始，删除长度为tot的部分
// MAKE-SAME posi tot c : 从第posi个数字开始，长度为tot的部分，值都设置成c
// REVERSE posi tot     : 从第posi个数字开始，翻转长度为tot的部分
// GET-SUM posi tot     : 从第posi个数字开始，查询长度为tot的部分的累加和
// MAX-SUM              : 查询整个数列中，非空子数组的最大累加和
// 任何时刻输入保证至少有一个数字在数列中，并且所有操作都合法
// 插入数字总数很多，但是任何时刻数列中最多有5 * 10^5个数，使用总空间要和该数量有关
// 测试链接 : https://www.luogu.com.cn/problem/P2042

#if 0
#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;
#define endl "\n"
const int MAXN = 5e5 + 5;
const int INF = 0x3f3f3f3f;

int head = 0;
int arr[MAXN];//初始输入进来的数组  二分建树
int key[MAXN];
int ls[MAXN];
int rs[MAXN];
int fa[MAXN];
int sz[MAXN];

int space[MAXN], si;
int sum[MAXN];

//非空子数组最大累加和  非空！！
int all[MAXN];
// 最大前缀和  可以为空 --->保证不选择更小的值
int pre[MAXN];
// 最大后缀和 可空 ---> 不选择小值
int suf[MAXN];
//线段树 lazy tag
bool update[MAXN];
int change[MAXN];
bool rev[MAXN];

int n, m;
string op;

void up(int i) {
	int l = ls[i], r = rs[i];
	sz[i] = sz[ls[i]] + sz[rs[i]] + 1;
	sum[i] = sum[l] + sum[r] + key[i];
	all[i] = std::max({ all[l],all[r],suf[l] + key[i] + pre[r] });
	pre[i] = std::max({ pre[l],sum[l] + key[i] + pre[r],0 });
	suf[i] = std::max({ suf[r],suf[l] + key[i] + sum[r],0 });
}

// 以i为头的这颗子树 打上 需要reverse的 lazy tag
void setReverse(int i) {
	if (i != 0) {
		std::swap(pre[i], suf[i]);
		rev[i] ^= 1;//其实就是 rev[i]=!rev[i]
	}
}

// 以i这个节点为头的子树 值全部设置为val
// 如何分离出这颗子树 -->两次Splay
void setValue(int i, int val) {
	if (i != 0) {
		update[i] = true;
		change[i] = val;
		key[i] = val;

		sum[i] = sz[i] * val;
		all[i] = std::max(sum[i], val);//如果<=0 就选val
		pre[i] = std::max(sum[i], 0);//都是可以为空的
		suf[i] = std::max(sum[i], 0);
	}
}

void down(int i) {
	if (update[i]) {
		setValue(ls[i], change[i]);
		setValue(rs[i], change[i]);
		update[i] = false;
	}
	if (rev[i]) {
		std::swap(ls[i], rs[i]);
		setReverse(ls[i]);
		setReverse(rs[i]);
		rev[i] = false;
	}
}

int init(int val) {
	int i = space[si--];//里面存储的就是能使用的节点编号
	sz[i] = 1;
	key[i] = sum[i] = all[i] = val;
	pre[i] = suf[i] = std::max(key[i], 0);
	fa[i] = ls[i] = rs[i] = 0;//之前可能存在脏数据  后续的fa由调用方设置
	update[i] = rev[i] = false;
	return i;
}

//二分建平衡树
int build(int l, int r) {
	int mid = (l + r) / 2;
	int root = init(arr[mid]);
	if (l < mid) {//左侧还存在数值
		ls[root] = build(l, mid - 1);
		fa[ls[root]] = root;
	}
	if (mid < r) {

		rs[root] = build(mid+1,r);
		fa[rs[root]] = root;
	}
	up(root);
	return root;
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
	}
	if (g != 0) {
		if (sonf == 0) {
			ls[g] = i;
		}
		else {
			rs[g] = i;
		}
	}
	fa[f] = i;
	fa[i] = g;
	up(f);
	up(i);
}

void Splay(int i,int goal){
	int f = fa[i], g = fa[f];
	while (f != goal) {
		if (g != goal) {
			if (leftOrRight(i) == leftOrRight(f)) {
				//一字型
				Rotate(f);
			}
			else {//之字形
				Rotate(i);
			}
		}
		Rotate(i);
		f = fa[i];
		g = fa[f];
	}
	if (goal == 0) {
		head = i;
	}
}

int find(int rank) {
	int i = head;
	while (i != 0) {
		down(i);//来查就要down
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

//回收 以i为head的这颗子树的所有节点编号 
void recycle(int i) {
	if (i != 0) {
		space[++si] = i;
		recycle(ls[i]);
		recycle(rs[i]);
	}
}

//数组复用 arr   1~tot
void insert(int posi,int tot) {
	if (head == 0) {
		//最初始的二分建树
		head = build(1, tot);
	}
	else {
		//  posi数字后 插入这么多数字(tot长度)
		int fL = find(posi);
		int fR = find(posi + 1);
		Splay(fL, 0);
		Splay(fR, fL);
		ls[rs[head]] = build(1, tot);
		fa[ls[rs[head]]] = rs[head];
		up(rs[head]);
		up(head);
	}
}

void Delete(int posi, int tot) {
	int fL = find(posi - 1);
	int fR = find(posi + tot);
	Splay(fL, 0);//升根
	Splay(fR, fL);
	recycle(ls[rs[head]]);
	ls[rs[head]] = 0;
	up(rs[head]);
	up(head);
}

void makeSame(int posi, int tot, int val) {
	int fL = find(posi - 1);
	int fR = find(posi + tot );
	Splay(fL, 0);
	Splay(fR, fL);
	setValue(ls[rs[head]], val);
	up(rs[head]);
	up(head);
}

void Reverse(int posi, int tot) {
	int fL = find(posi - 1);
	int fR = find(posi + tot );
	Splay(fL, 0);
	Splay(fR, fL);
	setReverse(ls[rs[head]]);
	up(rs[head]);
	up(head);
}

//查询从第posi数字开始  长度为tot的部分累加和
int getSum(int posi, int tot) {
	int fL = find(posi - 1);//升根
	int fR = find(posi + tot );//升到head右孩子
	Splay(fL, 0);
	Splay(fR, fL);//右孩子
	return sum[ls[rs[head]]];
}

int getMAXSUM() {
	return all[head];
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;

	si = MAXN - 1;// 0号空间不能用
	for (int i = 1; i <= si; i++) {
		space[i] = i;
	}
	arr[1] = arr[n + 2] = all[0] = -INF;//设为无穷小

	// j=2开始  i=n  j=n+1
	// 哨兵是 1 和 n+2
	for (int i = 1, j = 2; i <= n; i++, j++) {
		cin >> arr[j];
	}
	insert(1, n + 2);

	for (int i = 1, posi, tot, val; i <= m; i++) {
		cin >> op;

		if (op == "MAX-SUM") {
			cout << getMAXSUM() << endl;
		}
		else {
			cin >> posi >> tot;
			// 输入的 pos 是物理位置，树中包含左哨兵，所以 rank = pos + 1
			// 题目描述：从第 pos 个数字开始。
			// 你的代码逻辑：pos++ 后，pos 变为"第 pos 个数字的前一个位置的 rank"（即 rank-1），
			// 这在后续操作中（find(pos), find(pos+len+1)）是对齐的。
			// 举例：DELETE 1 1。pos=1, len=1。
			// 变换后 pos=2。
			// remove(2, 1) -> find(1) (哨兵), find(3) (第2个数)。区间是第1个数
			posi++;//前面垫了一个数字
			if (op == "INSERT") {
				for (int j = 1; j <= tot; j++) {
					cin >> arr[j];
				}
				insert(posi, tot);
			}
			else if (op == "DELETE") {
				Delete(posi, tot);
			}
			else if (op == "MAKE-SAME") {
				cin >> val;
				makeSame(posi, tot, val);
			}
			else if (op == "REVERSE") {
				Reverse(posi, tot);
			}
			else if (op == "GET-SUM") {
				cout << getSum(posi, tot) << endl;
			}
		}

	}
}

#endif