
// 单调栈求每个位置左右两侧，离当前位置最近、且值严格小于的位置
// 给定一个可能含有重复值的数组 arr
// 找到每一个 i 位置左边和右边离 i 位置最近且值比 arr[i] 小的位置
// 返回所有位置相应的信息。
// 输入描述：
// 第一行输入一个数字 n，表示数组 arr 的长度。
// 以下一行输入 n 个数字，表示数组的值
// 输出描述：
// 输出n行，每行两个数字 L 和 R，如果不存在，则值为 -1，下标从 0 开始。
// 测试链接 : https://www.nowcoder.com/practice/2a2c00e7a88a498693568cef63a4b7bb

#include<iostream>
#include<string>

using namespace std;
#if 0
#define int long long
#define endl "\n"

const int N = 1e6 + 5;
int nums[N];
int Stack[N];
int Size;
int ans[N][2];

int n;

void compute() {
	//从左往右遍历一次
	for (int i = 0; i < n; i++) {//for循环里面的逻辑还可以简化  这里写的很直白
		// 栈内没有元素 or 栈顶元素比当前元素要小  (大压小)直接入栈
		if (Size == 0 || nums[Stack[Size - 1]] < nums[i]) {
			Stack[Size++] = i;//加入下标
		}
		else {//有元素  而且栈顶元素大
			//栈顶一直pop 直到下面的元素比当前元素要小
			//这个过程还需要记录 ans  
			// 出栈元素可以确认左侧/右侧 第一个比自己小的元素的index了
			while (Size != 0 && nums[Stack[Size - 1]] >= nums[i]) {
				int top = Stack[--Size];
				//左侧 只要你不是栈底元素 那你一定存在左侧比你小的那个index
				ans[top][0] = Size != 0 ? Stack[Size - 1] : -1;
				ans[top][1] = i;//右侧就是现在要加入的元素 比你还小/相等(后续修正答案)
			}
			Stack[Size++] = i;//符合加入的条件了 你直接加入
		}
	}
	//清算阶段   已经遍历一遍了 那还在栈内的元素需要额外处理
	while (Size != 0) {
		int top = Stack[--Size];
		ans[top][0] = Size != 0 ? Stack[Size - 1] : -1;
		ans[top][1] = -1;//右侧没有比你小的
	}

	//对于重复出现的数字 还需要额外修正处理
	//最后一个数字肯定没有右边界嘛
	for (int i = n - 2; i >= 0; i--) {
		//重复数字的出现的时候，我们把右边界设置成了右侧最近的那个相等的重复数字
		//所以右边界存在的情况下，数值和当前位置相等，就需要修正
		if (ans[i][1] != -1 && nums[i] == nums[ans[i][1]]) {
			ans[i][1] = ans[ans[i][1]][1];
		}
	}
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> nums[i];
	}
	compute();
	for (int i = 0; i < n; i++) {
		cout << ans[i][0] << " " << ans[i][1] << endl;
	}
}

#endif