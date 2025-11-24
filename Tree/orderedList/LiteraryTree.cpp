
// 文艺平衡树，FHQ-Treap实现范围翻转
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
int head = 0;
int cnt = 0;
int key[MAXN];
int ls[MAXN];
int rs[MAXN];
double pr[MAXN];
int sz[MAXN];
bool rev[MAXN];

int ans[MAXN];
int ansi;


void up(int i) {
	sz[i] = sz[ls[i]] + sz[rs[i]] + 1;
}

//lazy 标记下发
void down(int i){
	if (i > 0 && rev[i] == true) {
		std::swap(ls[i], rs[i]);//交换左右孩子
		rev[i] = false;
		rev[ls[i]] = !rev[ls[i]];
		rev[rs[i]] = !rev[rs[i]];
	}
}

int init(int num) {
	key[++cnt] = num;
	sz[cnt] = 1;
	pr[cnt] = (static_cast<double>(rand() % INF) / INF);
	rev[cnt] = false;
	return cnt;
}

//还是按照 rank 进行 split  小于等于rank的去左树
void split(int l, int r, int i, int rank) {
	if (i == 0) {
		rs[l] = ls[r] = 0;
	}
	else {
		// i节点遇到任务 需要往下下发完lazy tag才能split
		down(i);
		// <=rank的分为左树
		if (sz[ls[i]] + 1 <= rank) {
			rs[l] = i;
			// 继续去右树查找
			split(i, r, rs[i], rank - sz[ls[i]] - 1);
		}
		else { // >rank的分为右树
			ls[r] = i;
			split(l, i, ls[i], rank);
		}
		up(i);
	}
}

int merge(int l, int r) {
	if (l == 0 || r == 0) {
		return l + r;
	}
	//按照优先级合并
	if (pr[l] >= pr[r]) {
		down(l);
		rs[l] = merge(rs[l], r);
		up(l);
		return l;
	}
	else {
		down(r);
		ls[r] = merge(l, ls[r]);
		up(r);
		return r;
	}
}

void inOrder(int i) {
	if (i != 0) {
		down(i);
		inOrder(ls[i]);
		ans[ansi++] = key[i];
		inOrder(rs[i]);
	}
}

int n, m;

void build() {
	head = cnt = 0;
	for (int i = 1; i <= n; i++) {
		head = merge(head, init(i));
	}
}

//翻转区间 Lt 到 Rt
// 两次split  打上lazy tag + merge回到原始的状态
void Reve(int Lt, int Rt) {
	split(0, 0, head, Rt);
	//   <=Rt          >Rt
	int l = rs[0], r = ls[0];
	split(0, 0, l, Lt - 1);
	// <Lt		     >=Lt  <=Rt
	int ll = rs[0], lr = ls[0];
	rev[lr] = !rev[lr];// 需要这样  
	//不能写成 rev[lr] = true这样  
	// 因为可能原本是 true  然后再次翻转就应该是原样 --> rev[lr]=false
	head = merge(merge(ll, lr), r);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	srand(time(nullptr));

	cin >> n >> m;
	build();
	// m 次 reverse
	for (int i = 0, Lt, Rt; i < m; i++) {
		cin >> Lt >> Rt;//翻转的区间
		Reve(Lt, Rt);
	}

	ansi = 0;
	inOrder(head);
	cout << ans[0];
	for (int i = 1; i < ansi; i++) {
		cout << " " << ans[i];
	}
	cout << endl;
}

#endif