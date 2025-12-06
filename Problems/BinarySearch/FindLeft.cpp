



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
// 有序数组中找>=num的最左位置


#if 0
int binarySearch(const std::vector<int>& nums, int num) {
	if (nums.empty()) { // 检查数组是否为空
		return false;
	}

	int l = 0;
	int r = nums.size() - 1; // 正确获取数组大小
	int ans = -1;//代表不存在 

	while (l <= r) {
		int mid = l + ((r - l) >> 1);
		if (nums[mid] >= num) {
			ans = mid;
			//再继续往左压缩
			r = mid - 1;
		}
		else {
			l = mid + 1;
		}
	}
	return ans;
}
#endif