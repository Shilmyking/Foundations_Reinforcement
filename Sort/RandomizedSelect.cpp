#include<vector>
#include<iostream>
#include<queue>
#include<algorithm>
#include<cstring>
#include<list>
#include<vector>
#include<string>

using namespace std;

// 无序数组中第K大的元素
// 测试链接 : https://leetcode.cn/problems/kth-largest-element-in-an-array/

class Solution1 {
    // 
    void partition(vector<int>& nums, int& first, int& last, int x) {
        int i = first;
        //必须取等  i<=last  这个位置也需要处理  可能还是和first 位置swap!
        while (i <= last) {
            if (nums[i] == x) {
                i++;
            }
            else if (nums[i] < x) {
                std::swap(nums[first++], nums[i++]);
            }
            else {
                std::swap(nums[i], nums[last--]);
            }
        }
    }

    int quickSort(vector<int>& nums, int k) {
        int ans = 0;
        for (int first = 0, last = nums.size() - 1; first <= last;) {
            int pivot = nums[first + rand() % (last - first + 1)];
            //还需要复用原本的 first 和 last
            int l = first, r = last;
            partition(nums, l, r, pivot);
            // 缩小范围继续查找
            // 其实这里该 这么想
            //  <first first - last >last
            // first~last 都是一种数字
            if (l > k) {
                last = l - 1;
            }

            else if (k > r) {
                first = r + 1;
            }
            else {
                ans = nums[k];
                break;
            }
        }
        return ans;
    }

public:
    int findKthLargest(vector<int>& nums, int k) {
        return quickSort(nums, nums.size() - k);
    }
};