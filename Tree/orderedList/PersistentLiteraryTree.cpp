// 可持久化文艺平衡树，FHQ-Treap实现
// 一开始序列为空，实现如下操作，操作一共发生n次
// v 1 x y : 基于v版本的序列，在第x个数后插入y，生成新版本的序列
// v 2 x   : 基于v版本的序列，删除第x个数，生成新版本的序列
// v 3 x y : 基于v版本的序列，范围[x,y]所有数字翻转，生成新版本的序列
// v 4 x y : 基于v版本的序列，查询范围[x,y]所有数字的和，生成新版本的序列状况=v版本状况
// 不管什么操作，都基于某个v版本，操作完成后得到新版本的序列，但v版本不会变化
// 每种操作给定的参数都是有效的，插入数字的范围[-10^6, +10^6]
// 1 <= n <= 2 * 10^5
// 本题目要求强制在线，具体规则可以打开测试链接查看
// 测试链接 : https://www.luogu.com.cn/problem/P5055
#if 0
#include<iostream>
#include<algorithm>
#include<cstring>
#include<climits>
#include<ctime>

using namespace std;
#define endl "\n"

using LL = long long;
const int INF = 0x3f3f3f3f;
const int MAXN = 2e5 + 2;
const int MAXM = MAXN * 100;
int cnt = 0;

int head[MAXN];
int key[MAXM];
int ls[MAXM];
int rs[MAXM];
int sz[MAXM];
bool reve[MAXM];
LL sum[MAXM];
int pr[MAXM];

int init(int num) {
	key[++cnt] = num;
	sz[cnt] = 1;
	reve[cnt] = false;
	pr[cnt] = rand() % INF;
	sum[cnt] = key[cnt];
	return cnt;
}

int copyNode(int i) {
	key[++cnt] = key[i];
	ls[cnt] = ls[i];
	rs[cnt] = rs[i];
	sz[cnt] = sz[i];
	reve[cnt] = reve[i];
	sum[cnt] = sum[i];
	pr[cnt] = pr[i];
	return cnt;
}

void up(int i) {
	sz[i] = sz[ls[i]] + sz[rs[i]] + 1;
	sum[i] = sum[ls[i]] + sum[rs[i]] + key[i];
}

void down(int i) {
	if (reve[i]) {
		if (ls[i] > 0) {
			ls[i] = copyNode(ls[i]);
			reve[ls[i]] = !reve[ls[i]];
		}
		if (rs[i] > 0) {
			rs[i] = copyNode(rs[i]);
			reve[rs[i]] = !reve[rs[i]];
		}
		std::swap(ls[i], rs[i]);
		reve[i] = !reve[i];
	}
}

//根据rank 进行split
void split(int l, int r, int i, int rank) {
	if (i == 0) {
		ls[r] = rs[l] = 0;
	}
	else {
		i = copyNode(i);
		// 必须down之前copyNode
		down(i);
		if (sz[ls[i]] + 1 <= rank) {
			rs[l] = i;
			split(i, r, rs[i], rank - sz[ls[i]] - 1);
		}
		else {
			ls[r] = i;
			split(l, i, ls[i], rank);
		}
		up(i);
	}
}

int Merge(int l, int r) {
	if (l == 0 || r == 0) {
		return l + r;
	}
	if (pr[l] >= pr[r]) {
		l = copyNode(l);
		down(l);
		rs[l] = Merge(rs[l], r);
		up(l);
		return l;
	}
	else {
		r = copyNode(r);
		down(r);
		ls[r] = Merge(l, ls[r]);
		up(r);
		return r;
	}
}

//版本 v  的基础上  在rank排名之后
// 加入num 变为版本v  --->head[v]
void add(int v, int i, int rank,int num) {
	split(0, 0, i, rank);//分为 <=rank >rank
	int l = rs[0], r = ls[0];
	ls[0] = rs[0] = 0;
	head[v] = Merge(Merge(l, init(num)), r);
}

// 删除 rank大的节点
void Remove(int v, int i, int rank) {
	split(0, 0, i, rank);
	int l = rs[0], r = ls[0];
	split(0, 0, l, rank - 1);
	int ll = rs[0]; 
	ls[0] = rs[0] = 0;
	head[v] = Merge(ll, r);
}

//范围 lt - rt 翻转
void Reverse(int v, int i, int lt, int rt) {
	split(0, 0, i, rt);// <=rt  >rt
	int l = rs[0], r = ls[0];
	split(0, 0, l, lt - 1);
	int ll = rs[0], lr = ls[0];// <lt  >=lt <=rt

	reve[lr] = !reve[lr];//reverse
	head[v] = Merge(Merge(ll, lr), r);
}

//求出 lt - rt的累加和
LL getSum(int v, int i, int lt, int rt) {
	split(0, 0, i, rt);
	int l = rs[0], r = ls[0];;
	split(0, 0, l, lt - 1);
	int ll = rs[0], lr = ls[0];
	ls[0] = rs[0] = 0;//空树

	LL ans = sum[lr];
	head[v] = Merge(Merge(ll, lr), r);
	return ans;
}

LL n, v, op, x, y;
LL lastAns = 0;
signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	srand(time(0));
	cin >> n;

	for (int i = 1; i <= n; i++) {
		cin >> v >> op >> x;
		x ^= lastAns;
		if (op != 2) {
			cin >> y;
			y ^= lastAns;
		}
		if (op == 1) {
			//插入在 x 名之后  值为y
			add(i, head[v], x, y);
		}
		else if (op == 2) {
			//删除 第x名的数字
			Remove(i, head[v], x);
		}
		else if (op == 3) {
			Reverse(i, head[v], x, y);
		}
		else {
			lastAns = getSum(i, head[v], x, y);
			cout << lastAns << endl;
		}
	}
}
#endif