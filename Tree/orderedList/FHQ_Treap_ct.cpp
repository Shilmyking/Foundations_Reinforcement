
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

const int MAXN = 1e5 + 5;
const int INF = 0x3f3f3f3f;
int head = 0;
int cnt = 0;

int key[MAXN];
int ls[MAXN];
int rs[MAXN];
int ct[MAXN];
int sz[MAXN];
double pr[MAXN];

int init(int num) {
	key[++cnt] = num;
	ct[cnt] = sz[cnt] = 1;
	pr[cnt] = static_cast<double>(rand()) / INF;
	return cnt;
}

void up(int i) {
	sz[i] = sz[ls[i]] + sz[rs[i]] + ct[i];
}

// 这里存在ct数组计数  不采用rank split 非常复杂 可能刚好切在一个节点的中间
// l、r：上一次小于等于(大于)num的节点编号
// i：当前位置的节点编号
// num：按照num 进行划分 split
void split(int l, int r, int i, int num) {
	if (i == 0) {
		rs[l] = ls[r] = 0;//设置好nullptr
	}
	else {
		if (key[i] <= num) {
			//到右树 split  左树完全不用动
			rs[l] = i;//l 这一个上一次 小于等于num的数字 的右孩子连接到i
			split(i, r, rs[i], num);//继续到i的右孩子rs[i]split
		}
		else {
			ls[r] = i;
			split(l, i, ls[i], num);
		}
		up(i);//汇总信息
	}
}//调用完整个split接口 实现了 ls[0]就是>num的那颗子树  rs[0]就是<=num的那颗子树
//因为最初始调用split 就是 split(0,0,head,num);

//给出 两颗子树 l子树的key值or rank排名都比r树小
// 合并两颗子树 返回合并之后的新head
int merge(int l, int r) {
	if (l == 0 || r == 0) {
		return l + r;
	}
	
	if (pr[l] >= pr[r]) {
		// l的优先级高 l当爹
		rs[l] = merge(rs[l], r);//存在换head的可能性
		up(l);
		return l;
	}
	else {
		ls[r] = merge(l, ls[r]);
		up(r);
		return r;
	}

}

int find(int i,int num) {
	if (i == 0) {
		return 0;
	}
	if (key[i] > num) {
		return find(ls[i], num);
	}
	else if (key[i] < num) {
		return find(rs[i], num);
	}
	else {
		return i;
	}
}

void changeCount(int i, int num, int change) {
	if (key[i] == num) {
		ct[i] += change;
	}
	else if (key[i] > num) {
		changeCount(ls[i], num, change);
	}
	else {
		changeCount(rs[i], num, change);
	}
	up(i);
}


void add(int num) {
	if (find(head, num) > 0) {
		changeCount(head, num, 1);
	}
	else {
		//不存在 --->新建节点
		//根据 num 分裂为两部分  
		// l-->rs[0]  r-->ls[0]
		split(0, 0, head, num);
		head =  merge(merge(rs[0], init(num)), ls[0]);
	}
}

// 以i为头节点的子树 小于num的节点个数 存在多少个
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

int getRank(int num) {
	return small(head, num) + 1;
}

// 在以i为头节点的这颗子树上 查找第x大的节点
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

//小于num的 最大的那个
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

int post(int i, int num) {
	if (i == 0) {
		return INF;
	}
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

//删除操作的话 先查找是否存在 
//如果存在 那通过两次split -->找到num
void remove(int num) {
	int i = find(head, num);
	if (i > 0) {
		if (ct[i] > 1) {
			changeCount(head, num, -1);
		}
		else {
			split(0, 0, head, num);
			//分为 <=num  >num
			int l = rs[0], r = ls[0];
			split(0, 0, l, num - 1);//需要split 按照num-1  -->  <=num-1 和 ==num
			//分裂出 num节点
			int ll = rs[0];// <num
			//int lr = ls[i];// num  --->直接不要了
			head = merge(ll, r);
		}
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