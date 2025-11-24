// FHQ Treap树的实现
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
#include<algorithm>
#include<iostream>
#include<cstring>
#include<climits>
#include<time.h>

using namespace std;

const int MAXN = 2e5 + 5;
const int INF = 0x3f3f3f3f;
int head = 0;
int cnt = 0;

int key[MAXN];
int ls[MAXN];
int rs[MAXN];
int sz[MAXN];
double pr[MAXN];

int init(int num) {
	key[++cnt] = num;
	sz[cnt] = 1;
	pr[cnt] = static_cast<double>(rand()) / INF;
	return cnt;
}

void up(int i) {
	sz[i] = sz[ls[i]] + sz[rs[i]] + 1;
}

//按照key split
void split(int l, int r, int i, int num) {
	if (i == 0) {
		//走过一个树高 来到叶子节点
		ls[r] = rs[l] = 0;
	}
	else {//需要else！！ 或者你前面 return
		//不然这个 一致调用递归 栈溢出
		if (key[i] <= num) {
			//键值小的去左树
			rs[l] = i;//当前位置键值都小了 左树肯定比num小 去右树看是大还是小
			split(i, r, rs[i], num);
		}
		else {
			ls[r] = i;
			//右树肯定比 num大  去左树找
			split(l, i, ls[i], num);
		}
		up(i);//回到i位置 汇总信息
	}
}

// 必须保证l 和 r两颗子树 r树 key/rank都比l树大
// 需要保证优先级按照大根堆  键值BSTree
//返回新head
int merge(int l, int r) {
	if (l == 0 || r == 0) {
		return l + r;
	}
	if (pr[l] >= pr[r]) {
		// 左树头节点 优先级高 --->  
		// 这个节点当为头节点之后 去右孩子看  因为要维持BSTree的性质
		rs[l] = merge(rs[l], r);
		up(l);
		return l;
	}
	else {
		ls[r] = merge(l, ls[r]);
		up(r);
		return r;
	}
}

// 新增节点  和之前存在ct的add差不多 
// 只是完全无需关心 ct大小
void add(int num) {
	split(0, 0, head, num);//按照num split
	//继续 split左树
	head = merge(merge(rs[0], init(num)), ls[0]);
}

void remove(int num) {
	split(0, 0, head, num);
	// <=num			>num
	int l = rs[0], r = ls[0];
	split(0, 0, l, num - 1);//分出 <=num-1 和 ==num的部分
	// lr 就是 ==num的部分
	// ll 是<num的部分
	int ll = rs[0], lr = ls[0];
	head = merge(merge(ll, merge(ls[lr], rs[lr])), r);
}

int getRank(int num) {
	split(0, 0, head, num - 1);
	int ans = sz[rs[0]] + 1;
	head = merge(rs[0], ls[0]);//还原整棵树
	return ans;
}

int index(int i, int x) {
	if (sz[ls[i]] >= x) {
		return index(ls[i], x);
	}
	//细节问题  sz[ls[i]]+1 < x --->右树找
	else if (sz[ls[i]] + 1 < x) {
		return index(rs[i], x - sz[ls[i]] - 1);
	}
	return key[i];
}

int index(int x) {
	return index(head, x);
}

int pre(int i, int num) {
	if (i == 0) {
		return -INF;
	}
	if (key[i] >= num) {
		return pre(ls[i], num);
	}
	else {
		return std::max(key[i], pre(rs[i], num));
	}
}

int pre(int num) {
	return pre(head, num);
}

int post(int i,int num) {
	if (i == 0) {
		return INF;
	}
	if (key[i] <= num) {
		return post(rs[i], num);
	}
	else {
		return std::min(post(ls[i], num), key[i]);
	}
}

int post(int num) {
	return post(head, num);
}

void clear() {
	cnt = 0;
	head = 0;
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
}
#endif