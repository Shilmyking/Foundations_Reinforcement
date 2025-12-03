
// 翻转对数量
// 测试链接 : https://leetcode.cn/problems/reverse-pairs/

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
#define endl "\n"

static const int MAXN = 1e5 + 2;
int help[MAXN];

class Solution {
public:
    void build(const vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            help[i] = nums[i];
        }
    }

    // 统计 + 排序
    // 如果
    int merge(vector<int>& nums, int l, int mid, int r) {
        int ans = 0;
        //此时左部分有序  右部分有序
        int left = l, right = mid + 1;
        //如果 i < j 且 nums[i] > 2*nums[j] 将 (i, j) 称作一个翻转对
        int sum = 0;//计算当前 i位置能和右侧构成多少个翻转对
        while (left <= mid) {
            while (right <= r && (long)nums[left] > (long)2 * nums[right]) {
                right++;
                sum++;
            }
            ans += sum;
            left++;
        }
        int i = l;
        left = l, right = mid + 1;
        while (left <= mid && right <= r) {
            help[i++] = nums[left] > nums[right] ? nums[right++] : nums[left++];
        }
        while (left <= mid) {
            help[i++] = nums[left++];
        }
        while (right <= r) {
            help[i++] = nums[right++];
        }
        i = l;
        while (i <= r) {
            nums[i] = help[i];
            i++;
        }
        return ans;
    }

    int MergeSort(vector<int>& nums, int l, int r) {
        if (l >= r) {
            return 0;
        }
        int mid = (l + r) / 2;
        return MergeSort(nums, l, mid) + MergeSort(nums, mid + 1, r) + merge(nums, l, mid, r);
    }

    int reversePairs(vector<int>& nums) {
        //build(nums); 本来就没有清除脏数据的必要
        // 注意 nums.size()-1
        return MergeSort(nums, 0, nums.size() - 1);
    }
};
#endif