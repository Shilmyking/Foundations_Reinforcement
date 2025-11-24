
// 可持久化平衡树，FHQ-Treap实现，不用词频压缩
// 认为一开始是0版本的树，为空树，实现如下操作，操作一共发生n次
// v 1 x : 基于v版本的树，增加一个x，生成新版本的树
// v 2 x : 基于v版本的树，删除一个x，生成新版本的树
// v 3 x : 基于v版本的树，查询x的排名，生成新版本的树状况=v版本状况
// v 4 x : 基于v版本的树，查询数据中排名为x的数，生成新版本的树状况=v版本状况
// v 5 x : 基于v版本的树，查询x的前驱，生成新版本的树状况=v版本状况
// v 6 x : 基于v版本的树，查询x的后继，生成新版本的树状况=v版本状况
// 不管什么操作，都基于某个v版本，操作完成后得到新版本的树，但v版本不会变化
// 如果x的前驱不存在，返回-2^31 + 1，如果x的后继不存在，返回+2^31 - 1
// 1 <= n <= 5 * 10^5
// -10^9 <= x <= +10^9
// 测试链接 : https://www.luogu.com.cn/problem/P3835

#if 0
#include<iostream>
#include<algorithm>
#include<cstring>
#include<climits>


using namespace std;
#define endl "\n"

const int MAXN = 5e5 + 2;
const int MAXM = MAXN * 50;
const int INF = 0x3f3f3f3f;
int cnt = 0;
int head[MAXN];
int key[MAXM];
int ls[MAXM];
int rs[MAXM];
int sz[MAXM];
double pr[MAXM];

int init(int num) {
	key[++cnt] = num;
	sz[cnt] = 1;
	pr[cnt] = static_cast<double>(rand() % INF) / INF;
	return cnt;
}

int copy(int i) {
	key[++cnt] = key[i];
	ls[cnt] = ls[i];
	rs[cnt] = rs[i];
	sz[cnt] = sz[i];
	pr[cnt] = pr[i];
	return cnt;
}

void up(int i) {
	sz[i] = sz[ls[i]] + sz[rs[i]] + 1;
}

void split(int l, int r, int i, int num) {
	if (i == 0) {
		rs[l] = ls[r] = 0;
	}
	else {
		i = copy(i);//这个版本的新节点
		if (key[i]<=num) {
			// 分为左树  继续去i节点的右树split
			rs[l] = i;
			split(i, r, rs[i],num);
		}
		else {
			ls[r] = i;
			split(l, i, ls[i], num);
		}
		up(i);
	}
}

int merge(int l, int r) {
	if (l == 0 || r == 0) {
		return l + r;
	}
	if (pr[l] >= pr[r]) {
		//还是需要 拷贝一份作为新版本的
		l = copy(l);
		rs[l] = merge(rs[l], r);
		up(l);
		return l;
	}
	else {
		r = copy(r);
		//无需关注 右侧了
		ls[r] = merge(l, ls[r]);
		up(r);
		return r;
	}
}

// 新生成的版本是v 
// i就是当前的节点编号  最初始要传入那个基于的版本head
// 进行add数字num
// 
void add(int v, int i, int num) {
	split(0, 0,i, num);
	int l = rs[0], r = ls[0];
	ls[0] = rs[0] = 0;//清零
	head[v] = merge(merge(l, init(num)), r);
}

//split 
// v : 新生成的版本编号
// i : 基于的历史版本，树的头节点编号
// num : 删除的数字
void remove(int v, int i, int num) {
	split(0, 0, i, num);
	int l = rs[0], r = ls[0];
	split(0, 0, l, num - 1);
	int ll = rs[0], lr = ls[0];
	// 后续可能基于0版本，去生成新版本的树，所以一定要清空，保证0版本始终是空树
	ls[0] = rs[0] = 0;
	head[v] = merge(merge(ll, merge(ls[lr], rs[lr])), r);
}

int small(int i, int num) {
	if (i == 0) {
		return 0;
	}
	if (key[i] >= num) {
		return small(ls[i], num);
	}
	else {
		return sz[ls[i]] + 1 + small(rs[i], num);
	}
}

int getRank(int i,int num) {
	return small(i, num) + 1;
}

int index(int i, int x) {
	if (sz[ls[i]] >= x) {
		return index(ls[i], x);
	}
	else if (sz[ls[i]] + 1 < x) {
		return index(rs[i], x - sz[ls[i]] - 1);
	}
	return key[i];
}

//小于num 尽可能大的
int pre(int i, int num) {
	if (i == 0) {
		return INT_MIN + 1;
	}
	if (key[i] >= num) {
		return pre(ls[i], num);
	}
	else {
		return std::max(key[i], pre(rs[i], num));
	}
}

//大于num 尽可能小的
int post(int i, int num) {
	if (i == 0) {
		return INT_MAX;
	}
	if (key[i] <= num) {
		return post(rs[i], num);
	}
	else {
		return std::min(key[i], post(ls[i], num));
	}
}

int n, v, op, x;
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> v >> op >> x;
		if (op == 1) {
			add(i, head[v], x);
		}
		else if (op == 2) {
			remove(i, head[v], x);
		}
		else {
			head[i] = head[v];
			if (op == 3) {
				cout << getRank(head[v], x) << endl;
			}
			else if (op == 4) {
				cout << index(head[v], x) << endl;
			}
			else if (op == 5) {
				cout << pre(head[v], x) << endl;
			}
			else if (op == 6) {
				cout << post(head[v], x) << endl;
			}
		}
	}
}
#endif