#if 0
#include<random>
#include<cstring>
#include<string>
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;


// 进制设置  可以认为是非常大的进制 比如100、200
// 效果会取决于数据状况，
const int BASE = 10;
const int MAXN = 1e5 + 5;

int nums[MAXN];
int help[MAXN];//进行逆遍历数组 + 填表
int cnt[BASE];//统计当前BASE下，这一位有多少个

int n;

//num数字 在BASE进制下存在多少位 --->进行多少次排序
int bits(int number) {
	int ans = 0;
	while (number > 0) {
		ans++, number /= BASE;
	}
	return ans;
}

void radixSort(int bits) {
	// offset 记录当前的位权重 (1, 10, 100...)
	for (int offset = 1; bits > 0; offset *= BASE, bits--) {
		memset(cnt, 0, sizeof(cnt));
		// BASE进制下 词频统计
		for (int i = 0; i < n; i++) {
			//拿BASE=10，10进制来理解  就是提取出前面的那些内容 % 10 -->提取出这一位
			// 12478 / 100 ---> 124  + 124 % 10 -->4
			cnt[(nums[i] / offset) % BASE]++;
		}
		//统计在这一位下 小于等于当前 i 的存在多少个
		// 0相当于就自己 -->跳过了
		for (int i = 1; i < BASE; i++) {
			cnt[i] += cnt[i - 1];
		}
		// 填表的过程  图解拿例子讲一下就很好懂
		// 需要维持稳定性 必须逆序填表
		for (int i = n - 1; i >= 0; i--) {
			//前缀数量分区  数字提取出每一位
			help[--cnt[(nums[i] / offset) % BASE]] = nums[i];
		}
		for (int i = 0; i < n; i++) {
			nums[i] = help[i];
		}
	}
}

void Sort() {
	//先找出 最小值 进行一定偏移  防止负数   如果会溢出使用 long long
	int Min = nums[0];
	for (int i = 1; i < n; i++) {
		Min = std::min(Min, nums[i]);
	}
	int Max = 0;
	for (int i = 0; i < n; i++) {
		nums[i] -= Min;//偏移
		Max = std::max(Max, nums[i]);//找最大值 ---> 多少bits
	}
	//基数排序
	radixSort(bits(Max));
	//恢复原本的数据 +min
	for (int i = 0; i < n; i++) {
		nums[i] += Min;
	}
}

void print() {
	cout << nums[0];
	for (int i = 1; i < n; i++) {
		cout << " " << nums[i];
	}
	cout << endl;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> nums[i];
	}
	Sort();
	print();
}
#endif
