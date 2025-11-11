
// 给定一个长度为n的数组，打印每个位置的右侧，大于该位置数字的最近位置
// 测试链接 : https://www.luogu.com.cn/problem/P5788

#include<iostream>
#include<string>

using namespace std;
#if 0
#define int long long
#define endl "\n"

const int N = 3e6 + 5;
int nums[N];
int Stack[N];
int Size;
int ans[N];

int n;

//这里题目 是洛谷的  要求右侧 第一个比自己大的元素的下标  不存在的话拿0替代
//注意下标 从1开始 所以0位置弃而不用
void compute() {
	//遍历一次  需要找比当前位置大的 右侧的第一个数字的下标
	//重复的数字设置为可以重复进入
	for (int i = 1; i <= n; i++) {
		while (Size != 0 && nums[i] > nums[Stack[Size - 1]]) {
			//如果栈内存在元素  而且栈顶元素更小   可以结算栈顶元素了
			int top = Stack[--Size];
			//只看右侧
			ans[top] = i;
		}
		Stack[Size++] = i;
	}

	//清算
	//其实这一步都不用了   设置0在最初始的过程就做了
	//while (Size > 0) {

	//}

	//重复的 数字也无需处理  因为在循环内的流程是 相同数字可以重复进入  
	//遇到大的就重复结算
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> nums[i];
	}
	compute();
	cout << ans[1];
	for (int i = 2; i <= n; i++) {
		cout << " " << ans[i];
	}
	cout << endl;
}

#endif