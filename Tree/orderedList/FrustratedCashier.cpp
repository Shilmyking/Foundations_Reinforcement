// 郁闷的出纳员
// 最低薪水为limit，一旦员工薪水低于limit，员工会离职，实现如下四种操作
// I x : 新来员工初始薪水是x，如果x低于limit，该员工不会入职当然也不算离职
// A x : 所有员工的薪水都加上x
// S x : 所有员工的薪水都减去x，一旦有员工低于limit那么就会离职
// F x : 查询第x多的工资，如果x大于当前员工数量，打印-1
// 所有操作完成后，打印有多少员工在操作期间离开了公司
// 测试链接 : https://www.luogu.com.cn/problem/P1486

#if 0
#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;
#define endl "\n"
const int MAXN = 3e5 + 5;
const int INF = 0x3f3f3f3f;

int cnt = 0;
int head = 0;
int key[MAXN];
int ls[MAXN];
int rs[MAXN];
int fa[MAXN];
int sz[MAXN];

int limit=0;//限制 如果结合change 小于的话离职
int change = 0;
int enter = 0;//多少人入职

void up(int i) {
	sz[i] = sz[ls[i]] + sz[rs[i]] + 1;
}
int init(int num) {
	key[++cnt] = num;
	sz[cnt] = 1;
	return cnt;
}

int leftOrRight(int i) {
	return ls[fa[i]] == i ? 0 : 1;
}

// 提一位  i节点上升一位
void Rotate(int i) {
	int f = fa[i], g = fa[f], soni = leftOrRight(i), sonf = leftOrRight(f);
	if (soni == 1) {
		//左旋
		rs[f] = ls[i];
		if (rs[f] != 0) {//如果 为0不能设置父节点  nullptr特判
			fa[rs[f]] = f;
		}
		ls[i] = f;//左接上f
	}
	else {
		ls[f] = rs[i];
		if (ls[f] != 0) {
			fa[ls[f]] = f;
		}
		rs[i] = f;
	}
	//设置爷爷节点的孩子信息
	if (g != 0) {
		if (sonf == 0) {//f原本是左孩子
			ls[g] = i;
		}
		else {
			rs[g] = i;
		}
	}
	//还需要设置 parent节点
	fa[f] = i;
	fa[i] = g;
	//汇总信息
	up(f);
	up(i);
}

//把 i  提根为 goal的孩子
void Splay(int i, int goal) {
	int f = fa[i], g = fa[f];
	while (f != goal) {
		//只要父亲不是goal 一直旋转 提根
		if (g != goal) {// 如果爷爷就是 goal了 提根一次即可
			if (leftOrRight(i) == leftOrRight(f)) {
				//一字型 先提父亲
				Rotate(f);
			}
			else {
				Rotate(i);
			}
		}
		Rotate(i);
		//这里 更新信息 再往上看i的 f和g是谁  rotate 内 up了
		f = fa[i];
		g = fa[f];
	}
	//最后完成  如果goal的话就是换根
	if (goal == 0) {
		head = i;
	}
}

//查找第rank小的节点
int find(int rank) {
	int i = head, last = head;
	while (i != 0) {
		last = i;
		if (sz[ls[i]] >= rank) {
			i = ls[i];
		}
		else if (sz[ls[i]] + 1 < rank) {
			rank -= (sz[ls[i]] + 1);
			i = rs[i];
		}
		else {
			return i;
		}
	}
	return 0;
}

void add(int num) {
	init(num);
	if (head == 0) {
		head = cnt;
	}
	else {
		int i = head, f = 0, soni = 0;
		while (i != 0) {
			f = i;
			if (key[i] >= num) {
				i = ls[i];
				soni = 0;
			}
			else {
				i = rs[i];
				soni = 1;
			}
		}
		//找到加入的位置
		if (soni == 0) {
			ls[f] = cnt;
		}
		else {
			rs[f] = cnt;
		}
		fa[cnt] = f;
		//up(f); 好像可有可无  因为splay 会调整
		Splay(cnt, 0);
	}
}

//第x小的工资
int index(int x) {
	int i = head, last = head;
	while (i != 0) {
		last = i;
		if (sz[ls[i]] >= x) {
			i = ls[i];
		}
		else if (sz[ls[i]] + 1 < x) {
			x -= sz[ls[i]] + 1;
			i = rs[i];
		}
		else {
			//break;  下面等效break
			i = 0;//可以退出了 i就是那个符合答案的值
		}
	}//last保存到了 第x小的
	Splay(last, 0);
	return key[last];
}

// 工资小于  limit + change的都离职
void Depertae() {
	// limit 1000  change -700  --->找大于 1700的
	// limit 1000  change  700   找大于300的
	int LIMIT = limit - change - 1;
	// <limit - change的都删除   > limit-change -1s的都保留
	int i = head;//去查找 中序遍历下 大于 LIMIT 且最小的 键值的下标
	int Bigger = 0;
	while (i != 0) {
		if (key[i] > LIMIT) {
			Bigger = i;//保存好  
			i = ls[i];// 左滑，只要有更小的就能更新
		}
		else {
			i = rs[i];
		}
	}
	//没找到符合的 那就是都不符合预期
	if (Bigger == 0) {
		head = 0;
	}
	else {
		Splay(Bigger, 0);
		ls[head] = 0;//左树都是 中序遍历次序下 更小的 --->值一定小 
		up(head);
	}
}

int n,k;
string op;
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> limit;//下界
	for (int i = 1; i <= n; i++) {
		cin >> op >> k;
		if (op == "I") {
			if (k >= limit) {
				add(k - change);
				enter++;
			}
		}
		else if (op == "A") {
			change += k;
		}
		else if (op == "S") {
			change -= k;
			Depertae();
		}
		else {// "F"
			//查询 第 k 多的工资  那就是总数 - k + 1 小
			if (k > sz[head]) {
				cout << -1 << endl;
			}
			else {
				cout << index(sz[head] - k + 1)+change << endl;
			}
		}
	}
	cout << (enter - sz[head]) << endl;
}

#endif