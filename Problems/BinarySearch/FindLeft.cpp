
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



// 二分答案法基础
// 有序数组中找>=num的最左位置
int bSearchLeft(const vector<int>& nums, int val) {
	int n = nums.size(), ans = -1;
	if (n == 0) {
		return ans;
	}
	int left = 0, right = n-1,mid = (left+right)/2;
	while (left <= right) {
		mid = (left + right) / 2;
		if (nums[mid] >= val) {
			ans = mid;
			right = mid - 1;//往左压缩 只要还存在>=val的位置
		}
		else {
			left = mid + 1;
		}
	}
	return ans;//return ans最左位置
}


