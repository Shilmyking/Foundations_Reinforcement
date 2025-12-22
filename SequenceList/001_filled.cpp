
#include<vector>
#include<algorithm>

#include<cstring>
using namespace std;

//翻转数组
void Reverse(vector<int>& nums) {
	int n = nums.size();
	int k = n / 2; // 3->1次 2->1次  4->2次
	for (int i = 0; i < k; i++) {
		swap(nums[i], nums[n - i - 1]);
	}
}
// 删除值为x的

int removeX(vector<int>& nums, int val) {
	int filled = 0;//填数组
	for (int i = 0; i < nums.size(); i++) {
		if (nums[i] != val) {
			nums[filled++] = nums[i];
		}
	}
}

void removeXY(vector<int>& nums, int X, int Y) {
	int filled = 0;
	for (int i = 0; i < nums.size(); i++) {
		if (!(nums[i] >= X && nums[i] <= Y)) {
			nums[filled++] = nums[i];
		}
	}
}

//有序数组
void removeDump(vector<int>& nums) {
	if (nums.size() == 0) { return; }
	//指针
	int filled = 0;

	// 快慢指针 
	// 第一个位置一定需要填入  如果后续出现和nums[filled]不同的数字 填到下一个位置
	// 一直这样比较下去
	for (int i = 1; i < nums.size(); i++) {
		if (nums[i] != nums[filled]) {
			nums[++filled] = nums[i];
		}
	}
	nums[filled] = nums[nums.size() - 1];
}

vector<int>mergeVector(vector<int>& nums1, vector<int>& nums2) {
	int n = nums1.size(), m = nums2.size();
	int i = 0, j = 0,filled=0;
	vector<int>ans(n + m);
	while (i < n && j < m) {
		ans[filled++] = nums1[i] <= nums2[j] ? nums1[i++] : nums2[j++];
	}
	while (i < n) {
		ans[filled++] = nums1[i++];
	}
	while (j < m) {
		ans[filled++] = nums2[j++];
	}
	return ans;
}