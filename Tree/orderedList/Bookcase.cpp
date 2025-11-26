
// 书架
// 给定一个长度为n的排列，由数字1、2、3...n组成，实现如下五种操作
// Top s      : 数字s移动到最左边
// Bottom s   : 数字s移动到最右边
// Insert s t : 数字s位置假设为rank，现在移动到rank+t位置
// Ask s      : 查询数字s左边有多少数字
// Query s    : 查询从左往右第s位的数字
// 所有操作保证都是合法的
// 测试链接 : https://www.luogu.com.cn/problem/P2596
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

// 值对应节点编号
// pos[num] : 数字num所在节点的编号   数字的节点编号
// 因为题目最后输出的时候 查询的是书籍编号  需要拿到节点编号才能进行各种查询
int pos[MAXN];

void up(int i) {
	sz[i] = sz[ls[i]] + sz[rs[i]] + 1;
}

int leftOrRight(int i) {
	return ls[fa[i]] == i ? 0 : 1;
}

void Rotate(int i) {
	int f = fa[i], g = fa[f], soni = leftOrRight(i), sonf = leftOrRight(f);
	if (soni == 1) {
		rs[f] = ls[i];
		if (rs[f]!= 0) {
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
		if (sonf == 1) {
			rs[g] = i;
		}
		else {
			ls[g] = i;
		}
	}

	fa[f] = i;
	fa[i] = g;
	up(f);
	up(i);
}

void Splay(int i,int goal) {
	int f = fa[i], g = fa[f];
	while (f != goal) {
		if (g != goal) {
			if (leftOrRight(i) == leftOrRight(f)) {
				Rotate(f);
			}
			else {
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
		if (sz[ls[i]] >= rank) {
			i = ls[i];
		}
		else if (sz[ls[i]] + 1 < rank) {
			rank -= sz[ls[i]] + 1;
			i = rs[i];
		}
		else if (sz[ls[i]] + 1 == rank) {
			return i;
		}
	}
	return 0;
}

void add(int num) {
	key[++cnt] = num;
	sz[cnt] = 1;
	pos[num] = cnt;
	// 为什么还是可以直接接在 head的右孩子？？？ 
	// 维护的是中序遍历的次序
	// 每次加入一个数字  就会把这个数字的节点编号 Splay为head   
	fa[cnt] = head;
	rs[head] = cnt;
	Splay(cnt, 0);
}


//查询 节点编号为i的节点左侧存在多少个数字
int Ask(int i) {
	Splay(i, 0);
	return sz[ls[i]];
}

// 若 op 为 Insert，则后有两个整数 s,t，
// 表示若编号为 s 的书上面有 x 本书，则放回这本书时他的上面有 x+t 本书
// 先查出 pos[s]的 rank --> find()
// 
// 中序遍历次序为a的节点 移动到中序遍历为b的节点位置
// 也就是先 抠出a次序的节点  

// 中序排名为a的节点，移动到中序排名为b的位置
// 注意a不会是1和n位置，b也如此   --->垫了一个值
// 因为1位置和n位置提前加入了预备值，永远不会修改
void move(int a, int b) {
	int La = find(a - 1);
	int Ra = find(a + 1);
	Splay(La, 0);
	Splay(Ra, La);
	int cntA = ls[rs[head]];
	ls[rs[head]] = 0;//抠出a
	up(rs[head]);
	up(head);

	int Lb = find(b - 1);
	int Rb = find(b);
	Splay(Lb, 0);
	Splay(Rb, Lb);
	ls[rs[head]] = cntA;
	fa[cntA] = rs[head];

	up(rs[head]);
	up(head);
}

int Query(int s) {
	int i = find(s);
	Splay(i, 0);
	return key[i];
}

int n, m;
string op;
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> n >> m;
	add(0);//最左
	for (int i = 0, x; i < n; i++) {
		cin >> x;
		add(x);
	}
	add(n + 1);//n+1??

	n = n + 2;//垫了两个数字

	for (int i = 0, s, t; i < m; i++) {
		cin >> op >> s;
		int Rank = Ask(pos[s]) + 1;//s的Rank
		if (op == "Top") {
			//编号为s的书放在最上面
			move(Rank, 2);
		}
		else if (op == "Bottom") {
			move(Rank, n - 1);//最左侧垫了一个位置 
		}
		else if (op == "Insert") {
			cin >> t;
			move(Rank, Rank + t);
		}
		else if (op == "Ask") {
			//求的是比自己小的 + 垫了一个
			cout << (Rank - 1 - 1) << endl;
		}
		else if (op == "Query") {
			//从上面起第 s 本书的编号   给到rank查节点num
			cout << Query(s + 1) << endl;//垫了一个节点
		}
	}
}

#endif