
// Treap树的实现
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
#include<iostream>
#include<algorithm>
#include<cstring>
#include<climits>
#include<time.h>
using namespace std;

#define endl "\n"
const int MAXN = 1e5 + 5;
const int INF = 0x3f3f3f3f;

int cnt = 0;
int head = 0;
int key[MAXN];
int ct[MAXN];
int ls[MAXN];
int rs[MAXN];
int sz[MAXN];
double pr[MAXN];

void up(int i) {
	sz[i] = sz[ls[i]] + sz[rs[i]] + ct[i];
}

int leftRoate(int i) {
	int r = rs[i];
	rs[i] = ls[r];
	ls[r] = i;

	up(i);
	up(r);
	return r;
}

int rightRoate(int i) {
	int l = ls[i];
	ls[i] = rs[l];
	rs[l] = i;

	up(i);
	up(l);
	return l;
}

int init(int num) {
	key[++cnt] = num;
	ct[cnt] = sz[cnt] = 1;
	pr[cnt] = static_cast<double>(rand())/ INF;
	return cnt;
}

int add(int i, int num) {
	if (i == 0) {
		return init(num);
	}
	else {
		if (key[i] == num) {
			ct[i]++;
		}
		else if (key[i] > num) {
			//注意是 ls[i] 左节点可能 换head 这里接上
			// 而不是 i = add(ls[i],num)这种错误的...
			// 思考一下就明白了
			ls[i] = add(ls[i], num);
		}
		else {
			rs[i] = add(rs[i], num);
		}
		//加完之后
		up(i);
		if (ls[i] != 0 && pr[i] < pr[ls[i]]) {
			//左孩子优先级高
			i = rightRoate(i);
		}
		else if (rs[i] != 0 && pr[i] < pr[rs[i]]) {
			i = leftRoate(i);
		}
	}
	return i;

}

void add(int num) {
	head = add(head, num);
}

// 当前子树i下 小于num的数字存在多少个
int small(int i, int num) {
	if (i == 0) { return 0; }
	if (key[i] >= num) {
		return small(ls[i], num);
	}
	else {
		return small(rs[i], num) + sz[ls[i]] + ct[i];
	}
}

int getRank(int num) {
	return small(head, num) + 1;
}

//当前子树i下 排名为x的节点是谁
int index(int i, int x) {
	if (sz[ls[i]] >= x) {
		return index(ls[i], x);
	}
	else if (sz[ls[i]] + ct[i] < x) {
		return index(rs[i], x - sz[ls[i]] - ct[i]);
	}
	return key[i];
}

int index(int x) {
	return index(head, x);
}

//找前驱 小于num的最大的那个
int pre(int i, int num) {
	if (i == 0) { return -INF; }
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

int post(int i, int num) {
	if (i == 0) { return INF; }
	if (key[i] <= num) {
		return post(rs[i], num);
	}
	else {
		return std::min(key[i], post(ls[i], num));
	}
}

int post(int num) {
	return post(head, num);
}

// 确认存在节点num下 在当前子树i 删除 num
int remove(int i, int num) {
	if (key[i] > num) {
		ls[i] = remove(ls[i], num);
	}
	else if (key[i] < num) {
		rs[i] = remove(rs[i], num);
	}
	else {
		if (ct[i] > 1) {
			ct[i]--;
		}
		else {
			//删除节点
			if (ls[i] == 0 && rs[i] == 0) {
				return 0;
			}
			else if (ls[i] == 0 && rs[i] != 0) {
				return rs[i];
			}
			else if (ls[i] != 0 && rs[i] == 0) {
				return ls[i];
			}
			else {
				//根据孩子谁优先级大 把谁旋转上来
				if (pr[ls[i]] >= pr[rs[i]]) {
					//左孩子优先级高 左孩子上来
					i = rightRoate(i);
					rs[i] = remove(rs[i], num);
				}
				else {
					i = leftRoate(i);
					ls[i] = remove(ls[i], num);
				}
			}
		}
	}
	//删除完了
	up(i);//汇总信息
	return i;
}

void remove(int num) {
	//注意换头  最外层调用的接口
	// 还有就是判断节点在不在  
	// 这题没有 判断 也过了
	if (getRank(num) != getRank(num + 1)) {
		head = remove(head, num);
	}
}

void clear() {
	cnt = 0;
	head = 0;
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	srand(time(0));
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