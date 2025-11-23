
// 替罪羊树的实现
// 实现一种结构，支持如下操作，要求单次调用的时间复杂度O(log n)
// 1，增加x，重复加入算多个词频
// 2，删除x，如果有多个，只删掉一个
// 3，查询x的排名，x的排名为，比x小的数的个数+1
// 4，查询数据中排名为x的数
// 5，查询x的前驱，x的前驱为，小于x的数中最大的数，不存在返回整数最小值
// 6，查询x的后继，x的后继为，大于x的数中最小的数，不存在返回整数最大值
// 所有操作的次数 <= 10^5
// -10^7 <= x <= +10^7
// 测试链接 : https://www.luogu.com.cn/problem/P3369

#if 0
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>
#include <cstring>

using namespace std;

#define endl "\n"
const int INF = 0x3f3f3f3f;
const double ALPHA = 0.7;
const int MAXN = 1e5+5;
int head = 0;
int cnt = 0;
int key[MAXN];
int ct[MAXN];
int ls[MAXN];
int rs[MAXN];
int sz[MAXN];
int diff[MAXN];

int collect[MAXN];
int ci;

int top;
int father;
int side;

void clear() {
	//memset(key + 1, 0, cnt * sizeof(int));
	//memset(ct + 1, 0, cnt * sizeof(int));
	//memset(ls + 1, 0, cnt * sizeof(int));
	//memset(rs + 1, 0, cnt * sizeof(int));
	//memset(sz + 1, 0, cnt * sizeof(int));
	//memset(diff + 1, 0, cnt * sizeof(int));
	//memset(collect + 1, 0, cnt * sizeof(int));

	cnt = 0;
	head = 0;
}

//构造节点 返回节点编号
int init(int num) {
	key[++cnt] = num;
	ls[cnt] = rs[cnt] = 0;
	ct[cnt]=sz[cnt] = diff[cnt] = 1;
	return cnt;
}

//汇总孩子的信息
void up(int i) {
	sz[i] = sz[ls[i]] + sz[rs[i]] + ct[i];
	// 注意运算符 优先级问题  + 高于 >  三目运算符 必须加括号
	diff[i] = diff[ls[i]] + diff[rs[i]] + (ct[i] > 0 ? 1 : 0);
}

//中序遍历收集collect数组 
void inOrder(int i) {
	if (i != 0) {
		inOrder(ls[i]);
		if (ct[i] != 0) {
			//注意 ++ci  我们标识ci=0不使用  只在 1~MAXN这些位置使用
			collect[++ci] = i;
		}
		inOrder(rs[i]);
	}
}

// l~r 范围内 二分建树
// collect 存储的是节点编号  节点编号不按照顺序排列
// 但是节点的key[ci]按序排列  二分下标找到的ci对应的key[ci]就是 非常好的key[ci]
// 同时 ci 直接作为整棵树的head
int build(int l,int r) {
	if (l > r) {
		return 0;
	}
	int m = (l + r) / 2;
	int i = collect[m];//节点编号
	//到左树 右树 建出孩子
	ls[i] = build(l, m - 1);
	rs[i] = build(m + 1, r);
	up(i);//信息汇总
	return i;//返回当前建出的子树的头节点编号
}

//内部调用 build 重建树 
// 考虑树的head   
// 1）替换整棵树的head
// 2）替换 left[f] = build(...) 
// 3) 替换 right[f] = build(...)
void rebuild() {
	//存在不平衡的节点  那就需要重建
	if (top != 0) {
		ci = 0;
		inOrder(top);//收集这颗子树的所有节点
		if (ci != 0) {//为了保险起见？？
			//整棵树 重新建  只有head节点的father为0
			if (father == 0) {
				head = build(1, ci);
			}
			//存在父节点
			else if (side == 1) {
				//左树重构
				ls[father] = build(1, ci);
			}
			else {
				rs[father] = build(1, ci);
			}
		}
	}
}

// 判断当前节点是否平衡
bool balanced(int i) {
	// 当前节点的总节点数目 * ALPHA >= 左右子树中较大的一颗子树的节点数
	return ALPHA * diff[i] >= (double)std::max(diff[ls[i]], diff[rs[i]]);
}

//当前节点编号 节点的父亲  节点在父亲的哪一侧  加入的值
void add(int i, int f, int s, int num) {
	if (i == 0) {
		//加入节点
		if (f == 0) {
			head = init(num);
		}
		else if (s == 1) {
			ls[f] = init(num);
		}
		else {
			rs[f] = init(num);
		}
	}
	else {
		if (key[i] == num) {
			ct[i]++;//存在就加词频
		}
		else if (key[i] > num) {
			// 1 代表 i 节点是 f节点的 左孩子
			add(ls[i], i, 1, num);
		}
		else {
			add(rs[i], i, 2, num);
		}
		up(i);//回溯到当前节点
		if (!balanced(i)) {
			//当前节点不平衡 就记录 top father side 
			//如果后续回溯的过程中还存在不平衡的 就再次填写(覆盖)  
			// 因为需要的是最上方的不平衡的节点 (优化)
			top = i;
			father = f;
			side = s;
		}
	}
}

void add(int num) {
	top = father = side = 0;//初始化
	add(head, 0, 0, num);
	rebuild();//检查是否需要重构
}

// 以当前i节点为head的子树 小于num的节点个数存在多少个
int small(int i, int num) {
	if (i == 0) {
		return 0;
	}
	if (key[i] >= num) {
		return small(ls[i], num);
	}
	else {
		return sz[ls[i]] + ct[i] + small(rs[i], num);
	}
}

// 当前排名  排名：小于num的数字+1
int getRank(int num) {
	return small(head, num) + 1;
}

// 当前以i节点为head的子树 求排名为x的节点
int index(int i, int x) {
	//左树完全够了
	if (sz[ls[i]] >= x) {
		return index(ls[i], x);
	}
	// 左树 + 当前位置的都不够
	else if (sz[ls[i]] + ct[i] < x) {
		return index(rs[i], x - sz[ls[i]] - ct[i]);
	}
	return key[i];//如果左树不够   左树 + 当前位置又太多了 --->当前位置就是了
}

// 求出排名为 x的 节点键值
int index(int x) {
	return index(head, x);
}

//求出前驱节点
int pre(int num) {
	int kth = getRank(num);
	if (kth == 1) {
		return -INF;
	}
	else {
		return index(kth - 1);
	}
}

//求出后继节点
int post(int num) {
	//为什么是 getRank(num+1)
	int kth = getRank(num+1);
	if (kth == sz[head] + 1) {
		return INF;
	}
	else {
		return index(kth);
	}
}

// 减少频次 参数和add一致 可能在删除的过程出现节点不平衡
void remove(int i, int f, int s, int num) {
	if (key[i] == num) {
		ct[i]--;
	}
	else if (key[i] > num) {
		 remove(ls[i], i, 1, num);
	}
	else {
		//去右树
		 remove(rs[i], i, 2, num);
	}
	up(i);
	if (!balanced(i)) {
		top = i;
		father = f;
		side = s;
	}
}

// 减少节点 num的频次
void remove(int num) {
	//先check 是否存在num
	if (getRank(num) != getRank(num + 1)) {
		top = father = side = 0;
		remove(head, 0, 0, num);
		rebuild();
	}
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;

	cin >> n;
	for (int i = 0, op, num; i < n; i++) {
		cin >> op >> num;
		if (op == 1) {
			add(num);
		}
		else if (op == 2) {
			remove(num);
		}
		else if (op == 3) {
			cout << getRank(num) << endl;
		}
		else if (op == 4) {
			cout << index(num) << endl;
		}
		else if (op == 5) {
			cout << pre(num) << endl;
		}
		else {
			cout << post(num) << endl;
		}
	}
	clear();
}
#endif