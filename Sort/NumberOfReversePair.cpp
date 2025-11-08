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

#if 0
using namespace std;
#define int long long 
#define endl "\n"

/*
逆序对数量
给定一个长度为n的数组arr
如果 i < j 且 arr[i] > arr[j]
那么(i, j)就是一个逆序对
求arr中逆序对的数量
1 <= n <= 5 * 10 ^ 5
1 <= arr[i] <= 10 ^ 9
测试链接： https ://www.luogu.com.cn/problem/P1908
*/


const int N = 5e5 + 5;
int nums[N];
int help[N];
int n;

//如何统计 间隔两组之间的逆序对数
#if 0
int Merge(int left, int mid, int right) {

	int l = left, r = mid + 1;
	//先统计逆序对数，再去合并整个大区间
	int ans = 0;
	//从left的最右侧 往前统计 
	for (int i=mid,j=right; i >=l;i--) {
		//利用有序这个非常好的特征
		//从后往前
		while (j >= mid + 1 && nums[i] <= nums[j]) {//右侧的大就一直j--  因为不符合逆序对的定义
			j--;
		}
		// j-m就是有多少逆序对  右侧存在多少数字比nums[i]小
		ans += j - mid;//(j -(mid+1) +1)

		//下面是区间从左往右统计 容易出错
		//统计left这边 这一位数字能够组合出多少对逆序对
		//但是可能left这个数字还能大过 r+1 ...位置的数字  所以你r++去
		//直到大不过了  那就是正确的逆序对数
		//r++;

		//比 r位置的小  所以前面一共  r -(mid+1)位
		//ans += (r - mid + 1);
		//l++;//当前位置统计完了 换下一位
	}

	//归并
	l = left, r = mid + 1;//上面用过这个变量
	int i = left;
	while (l <= mid && r <= right) {
		help[i++] = nums[l] < nums[r] ? nums[l++] : nums[r++];
	}
	while (l <= mid) {
		help[i++] = nums[l++];
	}
	while (r <= right) {
		help[i++] = nums[r++];
	}
	for (int i = left; i <= right; i++) {
		nums[i] = help[i];
	}
	
	return ans;
}
#endif 
//上面的统计没毛病但是 可以在merge的时候进行统计逆序对   快挺多
int Merge(int left, int mid, int right) {
	int ans = 0;
	int l = left, r = mid + 1;//上面用过这个变量
	int i = left;

	while (l <= mid && r <= right) {
		if (nums[l] <= nums[r]) {//不构成逆序对
			help[i++] = nums[l++];
		}
		else {//逆序对 来了
			//nums[r]和左区间 l到mid的所有元素都构成逆序对  arr[l...]>nums[r]
			ans += (mid - l + 1);
			help[i++] = nums[r++];
		}
	}
	while (l <= mid) {
		help[i++] = nums[l++];
	}
	while (r <= right) {
		help[i++] = nums[r++];
	}
	for (int i = left; i <= right; i++) {
		nums[i] = help[i];
	}

	return ans;
}

int MergeSort(int left,int right) {
	if (left == right) { return 0; }
	int mid = (right - left) / 2 + left;

	return MergeSort(left, mid) + MergeSort(mid + 1, right) + Merge(left, mid, right);
}
signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> nums[i];
	}
	cout << MergeSort(0, n - 1) << endl;
}

#endif