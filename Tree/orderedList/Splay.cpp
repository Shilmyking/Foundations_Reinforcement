
// Splay树的实现，不用词频压缩
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
#include<string>
#include<climits>
using namespace std;

const int MAXN = 1e5 + 5;
const int INF = 0x3f3f3f3f;

int head = 0;
int cnt = 0;
int key[MAXN];
int ls[MAXN];
int rs[MAXN];
int fa[MAXN];
int sz[MAXN];

int init(int num) {
	key[++cnt] = num;
	sz[cnt] = 1;
	return cnt;
}

void up(int i) {
	sz[i] = sz[ls[i]] + sz[rs[i]] + 1;
}

//如果当前节点是father节点的哪个孩子 右孩子返回1 左孩子返回0
//会特判 是否为 head 节点
int leftOrRight(int i) {
	return rs[fa[i]] == i ? 1 : 0;
}

// 编号为i的节点 向上升一步   提一步  在结构上进行调整
void Rotate(int i) {
	int pr = fa[i], gr = fa[pr];
	int soni = leftOrRight(i), sonf = leftOrRight(pr);
	if (soni == 1) {//作为右孩子 进行左旋
		rs[pr] = ls[i];
		if (rs[pr] != 0) {
			//如果此前的 ls[i]就是空的 给到rs[pr]  
			// 不能设置父节点  --->否则破坏0号节点 没有父节点这个前提
			fa[rs[pr]] = pr;
		}
		ls[i] = pr;
	}
	else {
		//对偶操作
		ls[pr] = rs[i];
		if (ls[pr] != 0) {
			fa[ls[pr]] = pr;
		}
		rs[i] = pr;
	}
	//如果爷爷节点不为nullptr 设置好他的孩子
	if (gr != 0) {
		if (sonf == 1) {
			rs[gr] = i;
		}
		else {
			ls[gr] = i;
		}
	}
	//无论如何 都要做的  
	// i向上 替换 pr节点  pr作为i节点的孩子   
	fa[pr] = i;
	fa[i] = gr;
	up(pr);//先汇总孩子
	up(i);//最后汇总自己
}

// 提根操作
// 不能传入 i == 0 --->破坏head 找不到了
// 编号为i的节点提根，变成编号为goal节点的孩子
// 如果goal为0，表示编号为i的节点变为整棵树的头节点
void Splay(int i, int goal) {
	int pr = fa[i], gr = fa[pr];
	while (pr != goal) {
		// 一次看两个节点   如果gr就是goal  提一位即可
		// 如果 gr还不是goal  那考虑 现在是 一字型 还是 之字型
		if (gr != goal) {
			// 都是左孩子 or 右孩子 --->一字型
			// 一左一右  之字型
			if (leftOrRight(i) == leftOrRight(pr)) {
				//父节点先上一位
				Rotate(pr);
			}
			else {
				//当前节点上一位
				Rotate(i);
			}
		}
		//三种情况都要做的--->i节点上一位
		Rotate(i);
		//需要设置好 设置 pr gr 进行下一组Rotate
		pr = fa[i];
		gr = fa[pr];
	}//退出循环  i节点成功作为goal的孩子节点
	if (goal == 0) {//如果goal是0 -->新head
		head = i;
	}
}

//在整棵树上查找中序遍历排名为rank的节点，返回节点编号，不进行Splay
//这个方法作为内部方法调用  因为后续remove里面调用这个find方法 不能Splay
int find(int rank) {
	int i = head;
	//一路往底下 滑
	while (i != 0) {
		if (sz[ls[i]] + 1 < rank) {
			rank -= (sz[ls[i]] + 1);
			//继续去右树找 以rs[i]这颗子树为head的树 排名为rank-sz[ls[i]]-1的节点
			i = rs[i];
		}
		else if (sz[ls[i]] >= rank) {
			// 左树这颗树的节点个数完全够rank个
			i = ls[i];
		}
		else {//sz[ls[i]]+1 == rank 当前i就是了
			return i;
		}
	}
	//没找到？  不存在吧  rank太大了  或者太小了
	return 0;
}

void add(int num) {
	init(num);//新建节点  现在的cnt就指向这个节点
	if (head == 0) {
		head = cnt;
	}
	else {
		//去查找能插入的位置  
		// 因为最后 i == 0  
		// 还需要保存pr节点 + 自己是pr的左孩子还是右孩子 --->最后才能维护信息
		int i = head, pr = 0, soni = 0;
		while (i != 0) {
			pr = i;
			if (key[i] >= num) {
				i = ls[i];
				soni = 0;
			}
			else {// key[i] < num
				i = rs[i];
				soni = 1;
			}
		}//退出循环 i == 0 可以插入了
		if (soni == 0) {
			ls[pr] = cnt;
		}
		else {// soni == 1
			rs[pr] = cnt;
		}
		fa[cnt] = pr;//cnt的父节点为 pr
		//cnt当根节点  Splay
		Splay(cnt, 0);
	}
}

//查询小于 num的数字个数 + 1
//最后 Splay
int getRank(int num) {
	int ans = 0;
	//last 保存上一个访问的节点  
	// 初始化为head，不能为0 因为可能最后Splay(0,0) -->直接崩溃了
	int i = head,last = head;
	while (i != 0) {
		last = i;
		if (key[i] >= num) {
			i = ls[i];
		}
		else {
			ans += sz[ls[i]] + 1;
			i = rs[i];
		}
	}
	Splay(last, 0);//当根
	return ans + 1;
}

//查询x小的节点
int index(int x) {
	//int i = head;  下面好像有错
	////其实就是  i = find(x) --->就找到了那个节点 
	//while (i != 0) {
	//	if (x > sz[ls[i]] + 1) {
	//		//去右树
	//		x -= ls[i] - 1;
	//		i = rs[i];
	//	}
	//	else if (x <= sz[ls[i]]) {
	//		i = ls[i];
	//	}
	//	else if (x == sz[ls[i]] + 1) {
	//		break;
	//	}
	//}
	int i = find(x);
	Splay(i, 0);
	return key[i];
}

//查前驱
int pre(int num) {
	int i = head, last = head;
	int preNum = -INF+1;
	while (i != 0) {
		last = i;
		if (key[i] >= num) {
			i = ls[i];
		}
		else {
			preNum = std::max(preNum, key[i]);
			i = rs[i];
		}
	}
	Splay(last, 0);
	return preNum;
}

//查后继
int post(int num) {
	int i = head, last = head;
	int postNum = INF;
	while (i != 0) {
		last = i;
		if (key[i] <= num) {
			i = rs[i];
		}
		else {
			postNum = std::min(key[i], postNum);
			i = ls[i];
		}
	}
	Splay(last, 0);
	return postNum;
}

//删除num节点
void remove(int num) {
	int kth = getRank(num);//查出rank
	//先判断一下是否存在 num这个节点
	if (kth != getRank(num + 1)) {
		int i = find(kth);//查出 节点编号
		Splay(i, 0);//提根为head
		if (ls[head] == 0||rs[head]==0) {
			head = ls[head] + rs[head];//孩子替代自己
		}
		else {//既存在左孩子 又存在右孩子
			int r = find(kth + 1);//找到大kth一位的节点  旋转到head的右侧
			Splay(r, head);
			//这个时候 右孩子的左孩子肯定是nullptr的
			ls[r] = ls[head];//head的左孩子(不可能为空)给到 ls[r]
			fa[ls[r]] = r;//设置好father
			up(r);//孩子改变了 汇总信息
			head = r;//新head
		}
		fa[head] = 0;//换头了 整棵树的head的father为0
	}
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