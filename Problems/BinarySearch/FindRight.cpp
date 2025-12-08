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


int bSearchRight(const vector<int>& nums, int target) {
	int  n = nums.size(), ans = -1;
	if (n == 0) { return ans; }
	int left = 0, right = n - 1, mid = (left + right) / 2;
	while (left <= right) {
		mid = (left + right) / 2;
		if (nums[mid] <= target) {
			ans = mid;
			left = mid + 1;
		}
		else {
			right = mid - 1;
		}
	}
	return ans;
}

