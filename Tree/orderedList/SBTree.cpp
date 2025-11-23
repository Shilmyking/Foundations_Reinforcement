
//SBTree
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
#include <string>
#include <stdexcept>
#include <vector>
#include <sstream>

using namespace std;

const int MAXN = 1e5 + 5;
const int INF = 0x3f3f3f3f;
int head = 0;
int cnt = 0;

int key[MAXN];
int ct[MAXN];
int ls[MAXN];
int rs[MAXN];
int sz[MAXN];
int diff[MAXN];//计算节点个数(不关注词频)

void up(int i) {
	sz[i] = sz[ls[i]] + sz[rs[i]] + ct[i];
	diff[i] = diff[ls[i]] + diff[rs[i]] + 1;
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

// 平衡的判断是  当前来到i节点
// ls[i]  rs[i]的节点个数不能 小于两个侄子节点
//			a
//		b		c
//    d   e   f   g
// b 节点 小于f节点的节点个数  RL型
// b 节点 小于g节点的节点个数  RR型 ---> c上来当爹  g上来接替c的位置 和a节点同辈份
// c 节点 小于e节点的节点个数  LR型
// c 节点 小于d节点的节点个数  LL型
// 这样做就是让节点个数多的来到头部位置
int maintain(int i) {
	int lsz = diff[ls[i]];
	int rsz = diff[rs[i]];
	int llsz = diff[ls[ls[i]]];
	int lrsz = diff[rs[ls[i]]];
	int rlsz = diff[ls[rs[i]]];
	int rrsz = diff[rs[rs[i]]];
	if (rsz < llsz) {//LL型
		//i 节点右旋
		i = rightRoate(i); 
		// 这里就是原本的 ls[i]替代i的位置了 i变为ls[i]  
		// 新的rs[i] 是原本的 i  i节点的左孩子改变了  需要继续maitain判断是否平衡
		rs[i] = maintain(rs[i]);
		i = maintain(i);//最后递归回来了  右孩子可能又改变了 继续maintain
	}
	else if (rsz < lrsz) {//LR型
		ls[i] = leftRoate(ls[i]);
		i = rightRoate(i);
		//旋转好之后 上层满足条件 继续查看孩子是否maintain
		ls[i] = maintain(ls[i]);
		rs[i] = maintain(rs[i]);
		i = maintain(i);
	}
	else if (lsz < rlsz) {//RL型
		rs[i] = rightRoate(rs[i]);
		i = leftRoate(i);
		ls[i] = maintain(ls[i]);
		rs[i] = maintain(rs[i]);
		i = maintain(i);
	}
	else if (lsz < rrsz) {//RR型
		i = leftRoate(i);
		ls[i] = maintain(ls[i]);
		i = maintain(i);
	}
	return i;
}

int init(int num) {
	key[++cnt] = num;
	ct[cnt] = sz[cnt] = diff[cnt] = 1;
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
			ls[i]= add(ls[i], num);
		}
		else if (key[i] < num) {
			rs[i]= add(rs[i], num);
		}
	}
	// 递归回来之后  下面节点改变了
	// 汇总信息调整平衡
	up(i);
	return maintain(i);
}

void add(int num) {
	head = add(head, num);
}

// 比num小的数字存在多少个
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

//在head为i的子树上查找第rank大的节点
int index(int i, int rank) {
	if (sz[ls[i]] >= rank) {
		return index(ls[i], rank);
	}
	// 如果左树 + 当前节点还不够 取右树继续找
	else if (sz[ls[i]] + ct[i] < rank) {
		return index(rs[i], rank - sz[ls[i]] - ct[i]);
	}
	return key[i];
}

int index(int rank) {
	return index(head, rank);
}

//比num小的 最大的节点
int pre(int i,int num) {
	if (i == 0) {
		return -INF;
	}
	if (key[i] >= num) {
		return pre(ls[i], num);
	}
	else {
		//小里取大
		// 当前都更小了 肯定取看有没有更大的
		return std::max(key[i], pre(rs[i], num));
	}
}

int pre(int num) {
	return pre(head, num);
}

// 比num大的 最小的那个节点
//大里取小
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

//递归删除前驱节点
int removeMostLeft(int i, int j) {
	if (i == j) {
		return rs[i];//前驱节点 返回右孩子给父节点
	}
	else {
		ls[i] = removeMostLeft(ls[i], j);
		//真的删除完之后 要汇总信息 返回父节点当前子树的新head
		up(i);
		return maintain(i);
	}
}
//一定存在这个节点才调用  
// 在以i为head的这颗子树 删除key为num的节点
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
			// 真的要删除节点 
			if (ls[i] == 0 && rs[i] == 0) {
				return 0;//当前节点被设置为0
			}
			else if (ls[i] != 0 && rs[i] == 0) {
				//左孩子接替自己
				return ls[i];
			}
			else if (ls[i] == 0 && rs[i] != 0) {
				return rs[i];
			}
			else {
				// 如果孩子双全的话 找到前驱节点 接替当前节点  
				// 难点就在于 要删除这个前驱节点的话  如何维持信息  size和diff等 -->平衡性
				// 找到前驱节点然后  借助递归
				int mostLeft = rs[i];
				while (ls[mostLeft] != 0) {
					mostLeft = ls[mostLeft];//找到前驱节点
				}
				// 找到前驱节点之后  
				// 从rs[i]节点 开始一路向左递归 删除  + 回溯回来 maintain
				rs[i] = removeMostLeft(rs[i], mostLeft);
				//调整好 孩子之后  i 已死 ，mostLeft 当立， 当前节点替换为 前驱节点就行了
				ls[mostLeft] = ls[i];
				rs[mostLeft] = rs[i];
				i = mostLeft;
				//后续一样 up + maintain
			}
		}
	}
	//汇总信息 返回父节点当前子树的新head
	up(i);
	return maintain(i);
}

void remove(int num) {
	if (getRank(num) != getRank(num + 1)) {
		head = remove(head, num);
	}
}

void clear() {
	//数组也可以清空
	head = 0;
	cnt = 0;
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