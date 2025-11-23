
// 笛卡尔树模版
// 给定一个长度为n的数组arr，下标从1开始
// 构建一棵二叉树，下标按照搜索二叉树组织，值按照小根堆组织
// 建树的过程要求时间复杂度O(n)
// 建树之后，为了验证
// 打印，i * (left[i] + 1)，所有信息异或起来的值
// 打印，i * (right[i] + 1)，所有信息异或起来的值
// 1 <= n <= 10^7
// 测试链接 : https://www.luogu.com.cn/problem/P5854

#if 0

#include<iostream>
#include<algorithm>
#include<cstring>
#include<climits>
using namespace std;

#define int long long 
#define endl "\n"
const int MAXN = 1e7 + 5;


int nums[MAXN];
int ls[MAXN];
int rs[MAXN];
int stk[MAXN];
int n;
// 注意我们规定0位置弃而不用
// 因为 0 作为哨兵 所以nums数组和stk都不使用0号位
void build() {
	// 整个建树的过程  我们需要直到当前单调栈的栈顶  
	// 还有pop的时候到底pop了多少数字 --->找到最后一个pop的数字 作为新栈顶的左孩子
	for (int i = 1, top = 0, pos = 0; i <= n; i++) {
		pos = top;
		// 单调栈  栈底到栈顶  从小到大组织
		// 当新加入的数字太小了 需要pop直到能加入为止
		// 这里不改变栈顶位置  最后设置
		while (pos > 0 && nums[stk[pos]] > nums[i]) {
			pos--;
		}
		//栈内还存在数字  意味着需要设置当前新加入的数字为栈顶的右孩子
		if (pos>0) {
			rs[stk[pos]] = i;
		}
		//如果真的pop过数字
		if (pos != top) {
			// 最后pop出去的节点作为 新加入的节点的左孩子
			ls[i] = stk[pos + 1];
		}
		stk[++pos] = i;
		top = pos;
	}
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> nums[i];
	}
	build();

	int ans1 = (ls[1] + 1), ans2 = (rs[1] + 1);
	for (int i = 2; i <= n; i++) {
		ans1 ^= i* (ls[i] + 1);
		ans2 ^= i * (rs[i] + 1);
	}
	cout << ans1 << " " << ans2 << endl;
}
#endif