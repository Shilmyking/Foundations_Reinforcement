// AVL树的实现
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
using namespace std;

//使用 int 足够 long long 稍微拖慢时间  ...  内存用的也多
#define int long long  
#define endl "\n"
const int MAXN = 1e5 + 5;
const int INF = 0x3f3f3f3f3f3f3f3f;

int head = 0;
int cnt = 0;
int key[MAXN];//键值
int height[MAXN];//高度
int lt[MAXN];//左孩子
int rt[MAXN];//右孩子

int Count[MAXN];//词频
int sz[MAXN];//这颗子树下节点的个数

int n;

//当前节点 汇总孩子的信息 更新 height sz
void up(int i) {
	sz[i] = sz[lt[i]] + sz[rt[i]] + Count[i];
	height[i] = std::max(height[lt[i]], height[rt[i]]) + 1;
}

//以i为head的节点 左旋
int leftRoate(int i) {
	int r = rt[i];

	rt[i] = lt[r];
	lt[r] = i;

	up(i);
	up(r);
	return r;
}

//以i为head的节点 右旋
int rightRoate(int i) {
	int l = lt[i];//左孩子

	lt[i] = rt[l];// 父节点的左孩子 变为 左孩子的右孩子
	rt[l] = i;//左孩子的右孩子变为 i节点

	up(i);//先汇总这个孩子
	up(l);//再汇总 新head
	return l;
}

// 负责旋转 信息正确更新 同时 维持平衡
int maintain(int i) {
	int hl = height[lt[i]], hr = height[rt[i]];
	if (hl - hr > 1) {
		int l = lt[i];
		// LL
		if (height[lt[l]] >= height[rt[l]]) {
			i = rightRoate(i);
		}
		else {//LR
			lt[i] = leftRoate(lt[i]);
			i = rightRoate(i);
		}
	}
	else if (hr - hl > 1) {
		int r = rt[i];
		if (height[rt[r]] >= height[lt[r]]) {
			i = leftRoate(i);
		}
		else {
			rt[i] = rightRoate(rt[i]);
			i = leftRoate(i);
		}
	}

	return i;//返回新head给父节点
}

//实现函数 递归 
// 当前节点为i 往下找加入num的位置
int add(int i, int num) {
	if (i == 0) {
		// cnt始终指向要添加节点的那个位置
		//nullptr节点  分配编号
		key[++cnt] = num;
		Count[cnt] = height[cnt] = sz[cnt] = 1;
		return cnt;// 向父节点返回当前节点的编号
	}

	if (key[i] == num) {
		Count[i]++;
	}
	else if (key[i] > num) {
		//存在换head的可能性
		lt[i] = add(lt[i], num);
	}
	else if (key[i] < num) {
		 rt[i] = add(rt[i], num);
	}
	// 回溯回来了
	up(i);//汇总当前节点的信息
	return maintain(i);//调整平衡然后返回给父节点
}


//主调接口 
void add(int num) {
	head = add(head, num);//从head号节点去...  也就是头节点  head随时可能会替换
}

// 当前在i节点  后续继续去查找 还有多少小于 num的
// return 位次
int getRank(int i, int num) {
	if (i == 0) { return 0;}
	if (key[i] >= num) {// > 直接去左侧
		// 因为是要收集小于当前num的总节点个数
		return getRank(lt[i], num);
	}
	else {//当前 key[i] < num  --->  说明当前位置也囊括 左树也囊括
		return sz[lt[i]] + Count[i] + getRank(rt[i], num);
	}
}

//获取 num数字的 rank
int getRank(int num) {
	return getRank(head, num) + 1;// 小于num的数目 + 1
}


// 查找、删除i节点为head的 mostLeft
// 然后 up收集信息 调整平衡
int removeMostLeft(int i, int mostLeft) {
	if (i == mostLeft) {
		//找到后继节点 ，删除
		return rt[i];// 返回后继的right 节点(替代后继节点的位置，找不到了，等效于删除)
	}
	else {
		//继续往左树走   直到找到 mostLeft 然后返回回来
		lt[i] = removeMostLeft(lt[i], mostLeft);
		//返回回来了 汇总子节点信息  然后maintain
		up(i);
		return maintain(i);//调整好的head   
	}
}

// 删除节点
int remove(int i, int num) {
	if (key[i] > num) {
		lt[i] = remove(lt[i], num);
	}
	else if (key[i] < num) {
		rt[i] = remove(rt[i], num);
	}
	else if (key[i] == num) {
		if (Count[i] > 1) {
			Count[i]--;
		}
		else {
			if (lt[i] == 0 && rt[i] == 0) {
				return 0;//叶子 直接返回0给父节点 设置为nullptr
			}
			else if (lt[i] == 0 && rt[i] != 0) {
				return rt[i];
			}
			else if (lt[i] != 0 && rt[i] == 0) {
				return lt[i];
			}
			else {
				int mostLeft = rt[i];
				//找前驱
				while (lt[mostLeft] != 0) {
					mostLeft = lt[mostLeft];
				}
				//删除前驱节点
				// 从 i 节点的右孩子开始往做走 一路删除 + maintain 
				// 回到这个位置的时候  可能换头了 
				rt[i] = removeMostLeft(rt[i], mostLeft);
				// 将 mostLeft这个 节点编号替代i的位置 就相当于建立新节点了
				lt[mostLeft] = lt[i];
				rt[mostLeft] = rt[i];
				i = mostLeft;
				// 最后还是会 up + maintain
			}
		}
	}
	up(i);
	return maintain(i);
}

//主调删除  先检查是否存在  然后再去调用删除
void remove(int num) {
	// 先check 是否存在这个key
	if (getRank(num) != getRank(num + 1)) {
		head = remove(head, num);
	}
}

// 思路其实就是和 getRank一样的  借助Size这个数组
int index(int i, int num) {
	if (sz[lt[i]] >= num) {//如果左树那些更小的数字都足够了  去左边找
		return index(lt[i], num);
	}
	else if(sz[lt[i]]+Count[i]<num) {//如果当前位置 加左树的 不够了  全部减去 去右树找
		return index(rt[i], num - sz[lt[i]] - Count[i]);
	}
	//左树不够  左树加上Count[i]有太多了 
	//那就是当前位置了
	return key[i];//key 就是第num小
}

// 求第num小的数字
int index(int num) {
	return index(head, num);
}

int pre(int i, int num) {
	if (i == 0) {
		return -INF;
	}//返回 -INF 非常小的值 尽可能取到遇到的大值
	if (key[i] >= num) {//i的键值大或者相等   那就往左
		return pre(lt[i], num);
	}
	else {//比key[i] 小的   可能不存在num值 继续往右
		//取当前键值和后续与遇到的键值 尽可能大的值
		return std::max(key[i], pre(rt[i], num));
	}
}

//查询前驱：小于num 同时尽可能大的
int pre(int num) {
	return pre(head, num);
}

//查询后继：大于num 同时尽可能小的
int post(int i, int num) {
	if (i == 0) {
		return INF;
	}
	if (key[i] > num) {
		//键值大  符合条件的同时  和后续遇到的键值相比
		// 取尽可能小的
		return std::min(key[i], post(lt[i], num));
	}
	else if (key[i] <= num) {
		return post(rt[i], num);//往右 找大的
	}
}

//查询后继
int post(int num) {
	return post(head, num);
}

// 清空 cnt部分
void clear() {
	memset(key + 1, 0, cnt * sizeof(int));
	memset(height + 1, 0, cnt * sizeof(int));
	memset(lt + 1, 0, cnt * sizeof(int));
	memset(rt + 1, 0, cnt * sizeof(int));
	memset(Count + 1, 0, cnt * sizeof(int));
	memset(sz + 1, 0, cnt * sizeof(int));
	cnt = 0;
	head = 0;
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	for (int i = 0,op,num; i < n; i++) {
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