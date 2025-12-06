
// 最接近目标值的子序列和
// 给你一个整数数组 nums 和一个目标值 goal
// 你需要从 nums 中选出一个子序列，使子序列元素总和最接近 goal
// 也就是说，如果子序列元素和为 sum ，你需要 最小化绝对差 abs(sum - goal)
// 返回 abs(sum - goal) 可能的 最小值
// 注意，数组的子序列是通过移除原始数组中的某些元素（可能全部或无）而形成的数组。
// 数据量描述:
// 1 <= nums.length <= 40
// -10^7 <= nums[i] <= 10^7
// -10^9 <= goal <= 10^9
// 测试链接 : https://leetcode.cn/problems/closest-subsequence-sum/
#if 0
#include<iostream>
#include<vector>
#include<queue>
#include<functional>
#include<list>
#include<map>
#include<unordered_map>
#include<set>
#include<unordered_set>
#include<algorithm>

using namespace std;

const int MAXN = 41;
const int MAXM = (1 << 20) + 5;

int lsum[MAXM],lsize=0;
int rsum[MAXM],rsize=0;
int filled = 0;
void build() {
    filled = lsize = rsize = 0;
}

class Solution {
public:

    //sum是距今为止的累和..
    void f(const vector<int>& nums,int i, int start, int end,int sum,int ans[],int goal) {
        //basecase
        if (i >= end) {
            ans[filled++] = sum;
        }
        else {
            int j = i + 1;//i~j范围存在多少重复的值
            while (j < end && nums[i] == nums[j]) {
                j++;
            }
            // 最后 j指向和i为止不相等的地方
            //这个时候 i~j-1都是重复的值  j -1 -i + 1个
            //这个时候 k==0就是啥也不选
            for (int k = 0; k <= j - i ; k++) {
                // j  j是下一个不和i为止相等的位置
                f(nums, j, start, end, sum + k * nums[i], ans, goal);
            }
        }
    }

    int compute(int goal) {
        int ans = std::abs(goal);
        int i = 0, j = rsize - 1;
        //只要不会增大距离差就继续 j--
        for (; i < lsize; i++) {
            // j>0??
            // j>=1
            while (j - 1 >= 0 && std::abs(goal - (lsum[i] + rsum[j])) >= std::abs(goal - (lsum[i] + rsum[j-1]))) {
                j--;//只要往左不会加大差值 就往左
            }
            ans = std::min(ans, std::abs(goal - (lsum[i] + rsum[j])));
        }
        return ans;
    }

    int minAbsDifference(vector<int>& nums, int goal) {
        build();
        int n = nums.size();
        //一个剪枝
        int maxSum = 0, minSum = 0;
        for (auto& v : nums) {
            maxSum += v >= 0 ? v : 0;
            minSum += v < 0 ? v : 0;
        }
        if (goal > maxSum) {
            return goal - maxSum;
        }
        else if (goal < minSum) {
            return minSum - goal;
        }
        //排序 nums --->简化 重复值下 递归展开
        std::sort(nums.begin(), nums.end());

        f(nums, 0, 0, n >> 1, 0, lsum, goal);
        lsize = filled;
        filled = 0;
        f(nums, n >> 1, n >> 1, n, 0, rsum, goal);
        rsize = filled;
        std::sort(lsum, lsum + lsize);
        std::sort(rsum, rsum + rsize);

        return compute(goal);
    }

};

#endif