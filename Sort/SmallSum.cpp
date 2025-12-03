
// 小和问题
// 测试链接 : https://www.nowcoder.com/practice/edfe05a1d45c4ea89101d936cac32469

#if 0
#include<vector>
#include<iostream>
#include<queue>
#include<algorithm>
#include<cstring>
#include<list>
#include<vector>
#include<string>
#include<map>
#include<unordered_map>
#include<set>
#include<unordered_set>

using namespace std;
#define endl "\n"
using ll = long long;

const int MAXN = 1e5 + 3;
int nums[MAXN];
int help[MAXN];
int n;

// 统计跨区间小和个数 + 本组内的小和个数 
ll Merge(int l, int r) {
	ll ans = 0;
	// 这个时候  l~mid-1 和 mid~r都是有序的
	// 可以统计小和  需要求出右侧部分每一位数字在左侧的小和
	int l0 = l, mid = (l + r) / 2;
	int r0 = mid + 1;
	ll sum = 0;
	while (r0 <= r) {
		for (; l0 <= mid; l0++) {
			if (l0 > mid || nums[l0] > nums[r0]) {
				break;
			}
			else {
				sum += nums[l0];
			}
		}
		r0++;//细节
		ans += sum;
	}

	int i = l;
	l0 = l, r0 = mid + 1;
	while (l0 <= mid && r0 <= r) {
		if (nums[l0] > nums[r0]) {
			help[i++] = nums[r0++];
		}
		else {
			help[i++] = nums[l0++];
		}
	}
	while (l0 <= mid) {
		help[i++] = nums[l0++];
	}
	while (r0 <= r) {
		help[i++] = nums[r0++];
	}
	for (int i = l; i <= r; i++) {
		nums[i] = help[i];
	}
	return ans;
}

//在 区间l~r内统计小和的个数
//数组小和的定义如下：第 i 个数的左侧小于等于si的个数

ll MergeSort(int l, int r) {
	//一个数字 视作0
	if (l >= r) {
		return 0;
	}
	int mid = (l + r) / 2;
	//左侧递归 右侧递归 + 整段计算小和
	//  小细节
	//假设 `l=0, r=1`，则 `mid=0`。 --->无限递归！！！
	// 左侧不能传入 mid-1!!!
	return MergeSort(l, mid) + MergeSort(mid + 1, r) + Merge(l, r);
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> nums[i];
		help[i] = nums[i];
	}
	cout << MergeSort(0, n - 1) << endl;
}

#endif