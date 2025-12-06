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
#include <ctime>     

using namespace std;
// 有序数组中找<=num的最右位置
#if 0
int binarySearch(const vector<int>& nums, int target) {
	if (nums.size() == 0) { return -1; }
	int ans = -1, l = 0, r = nums.size() - 1;
	while (l <= r) {
		int mid = l + (r - l) / 2;
		if (nums[mid] <= target) {
			ans = mid;
			l = mid + 1;//往右压缩
		}
		else {//太大了
			r = mid - 1;
		}
	}
	return ans;
}
#endif