#include<vector>
using namespace std;

/*
给你一个 非严格递增排列 的数组 nums ，请你 原地 删除重复出现的元素，使每个元素 只出现一次 ，返回删除后数组的新长度。
元素的 相对顺序 应该保持 一致 。然后返回 nums 中唯一元素的个数。

考虑 nums 的唯一元素的数量为 k。去重后，返回唯一元素的数量 k。
nums 的前 k 个元素应包含 排序后 的唯一数字。下标 k - 1 之后的剩余元素可以忽略。
*/
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int left = 0, right = 0;
        int n = nums.size();
        if (n == 1) { return 1; }
        while (right < n) {
            //什么时候更新left指针？？   当且仅当 right+1 和 right位置数值不一样的时候
            while (right + 1 < n && nums[right + 1] == nums[right]) {
                right++;
            }
            nums[left++] = nums[right++];//填好你的数字  然后指针都右移
        }
        return left;//返回的是数量  刚好left指针就是指向那个需要填好的下一个位置 符合
    }
};