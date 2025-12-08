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


class Solution {
public:
    //给定两个大小分别为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。请你找出并返回这两个正序数组的 中位数 。
    //算法的时间复杂度应该为 O(log(m + n)) 。


    double findMedian(vector<int>& nums1, int l1, int r1, vector<int>& nums2, int l2, int r2) {
        // num1长度是大于等于nums2的
        // 如果nums1的中点的值 大于 nums2的中点值  --->淘汰nums2前一半小的  nums1后一半大的

    }

    //合并之后数组的中位数  可能出现在nuns1  nums2  nums1+nums2
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), m = nums2.size();
        if (m > n) { std::swap(nums1, nums2); }
        //保证nums1 长度大于nums2
        return findMedian(nums1, 0, n - 1, nums2, 0, m - 1);
    }
};





//
//
//````markdown
//### 核心原理：寻找第 K 小的数(Divide and Conquer)
//
//针对这道题，** 递归（Recursion）** 确实是一个非常好的思路，完全符合你直觉中“根据中位数大小淘汰情况”的想法。但为了处理奇偶数长度和边界情况，我们将问题稍微转换一下：
//
//** 不要直接找中位数，而是去编写一个通用的函数：`findKth`（寻找两个有序数组中第 $k$ 小的数）。**
//
//#### 1. 为什么是 $O(\log(m + n))$？
//题目要求对数级时间复杂度，这意味着我们不能遍历数组。我们必须每次操作都 * *排除掉 * *一部分不可能成为答案的元素。这和二分查找（Binary Search）的逻辑是一致的。
//
//#### 2. “淘汰”算法图解
//假设我们要找第 $k$ 小的数。我们可以比较两个数组中第 $k / 2$ 个位置的元素。
//
//* *例子： * *
//我们需要找第 $k = 6$ 小的数。那么我们比较 $k / 2 = 3$（即两个数组的第3个元素）。
//
//* `nums1`:[1, 3, **4 * *, 9...](第3个元素是 4)
//* `nums2`:[1, 2, **5 * *, 8...](第3个元素是 5)
//
//* *分析： * *
//*因为 `nums1` 的第3个元素($4$) < `nums2` 的第3个元素($5$)。
//    * 这意味着：`nums1` 的前3个元素（1, 3, 4） * *绝对不可能 * *包含第6小的数。
//    * 即便 `nums2` 的前2个元素都比 `nums1` 的这3个小，加起来也才 $2 + 3 = 5$ 个元素。
//    * **结论： * *我们可以安全地 * *淘汰 * *（切除） `nums1` 的前 $k / 2$ 个元素。
//    * **下一步： * *既然排除了3个元素，接下来我们在剩下的数组中寻找第 $6 - 3 = 3$ 小的数。
//
//    这就是你提到的“根据中位数大小淘汰”，在算法中体现为 * *根据 $k / 2$ 位置的值进行淘汰 * *。
//
//    -- -
//
//    ### 代码逻辑修正
//
//    你提供的代码框架中，尝试直接用 `findMedian` 递归并在内部处理左右边界，这很容易写错（比如数组越界、索引计算复杂）。
//
//    * *更优的递归策略： * *
//    1.  定义 `getKth(nums1, start1, nums2, start2, k)`。
//    2. * *Base Case（递归终止条件）： * *
//    *如果某个数组已经全部被淘汰（起始位置越界），直接返回另一个数组的第 $k$ 个元素。
//    * 如果 $k = 1$，直接返回两个数组当前首元素中较小的那个。
//    3. * *Recursive Step（递归步骤）： * *
//    *取两个数组当前 $k / 2$ 位置的值（如果越界则设为无穷大，防止被选中）。
//    * 比较这两个值，小的那一方的前 $k / 2$ 个元素被淘汰。
//    * 递归调用，`k` 减去被淘汰的数量。
//
//    -- -
//
//    ### 修正后的 C++ 代码
//
//    我为你重写了基于递归的解法，逻辑清晰且无需复杂的边界检查。
//
//    ```cpp
//#include<vector>
//#include<iostream>
//#include<algorithm>
//#include<climits> // 用于 INT_MAX，不过double题型通常不用
//
//    using namespace std;
//
//class Solution {
//public:
//    // 辅助递归函数：在两个数组中寻找第 k 小的数
//    // nums1 从索引 i 开始，nums2 从索引 j 开始
//    double getKth(vector<int>& nums1, int i, vector<int>& nums2, int j, int k) {
//        // 1. 边界处理：确保 nums1 是剩余长度较短的那个数组，方便处理其中一个数组为空的情况
//        if (nums1.size() - i > nums2.size() - j) {
//            return getKth(nums2, j, nums1, i, k);
//        }
//
//        // 2. 终止条件
//        // 如果 nums1 已经为空（所有元素都被淘汰或遍历完），直接找 nums2 的第 k 个
//        if (nums1.size() == i) {
//            return nums2[j + k - 1];
//        }
//        // 如果 k 为 1，我们要找最小的那个，直接比较两个数组的当前首元素
//        if (k == 1) {
//            return min(nums1[i], nums2[j]);
//        }
//
//        // 3. 递归逻辑：尝试各取 k/2 个元素
//        // 注意：如果 nums1 剩余长度不足 k/2，则取其末尾，实际逻辑上我们赋予它无穷大，
//        // 这样它就不会被选中淘汰（因为我们总是淘汰小的）
//        int si = min((int)nums1.size(), i + k / 2);
//        int sj = j + k / 2; // nums2 由于是在上面 swap 过，这里长度肯定足够（或者配合上面逻辑）
//
//        // 这里需要注意：如果 nums2 索引越界了怎么办？
//        // 其实因为 k <= m+n，且我们保证了 nums1 短，只要处理好 nums1 越界赋值特殊值即可。
//        // 但为了严谨，我们直接取值比较。
//
//        int val1 = (si - 1 < nums1.size()) ? nums1[si - 1] : INT_MAX;
//        int val2 = (sj - 1 < nums2.size()) ? nums2[sj - 1] : INT_MAX;
//
//        if (val1 < val2) {
//            // nums1 的前半部分（i 到 si-1）都比 nums2 的第 k/2 个小
//            // 所以 nums1 的这部分（共 si - i 个元素）不可能是第 k 小
//            // 我们淘汰它们，k 减去淘汰的个数
//            return getKth(nums1, si, nums2, j, k - (si - i));
//        }
//        else {
//            // nums2 的前半部分较小，淘汰 nums2
//            return getKth(nums1, i, nums2, sj, k - (sj - j));
//        }
//    }
//
//    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
//        int m = nums1.size();
//        int n = nums2.size();
//        int total = m + n;
//
//        // 技巧：无论是奇数还是偶数长度，我们都算两次。
//        // 如果 total 是奇数，例如 5，left=3, right=3，算两次结果一样。
//        // 如果 total 是偶数，例如 4，left=2, right=3，求平均。
//        // 这样就统一了逻辑。
//        int left = (total + 1) / 2;
//        int right = (total + 2) / 2;
//
//        return (getKth(nums1, 0, nums2, 0, left) + getKth(nums1, 0, nums2, 0, right)) / 2.0;
//    }
//};
//````
//
//### 关键点解释：
//
//1. * *递归与 $k$ 的关系 * *：
//你的直觉是对的。这里的 $k$ 充当了“计数器”的角色。每次递归，我们都试图排除 $k / 2$ 个元素，所以 $k$ 会指数级减小，从而达到 $O(\log k)$ 即 $O(\log(m + n))$ 的复杂度。
//
//2. * *`min((int)nums1.size(), i + k / 2)` 是做什么的？**
//如果数组 `nums1` 剩下的元素少于 $k / 2$ 个，我们不能直接取 `nums1[i + k / 2 - 1]`，会越界。
//这时候我们取 `nums1` 剩下的所有元素参与比较。因为它的值（不管是实值还是逻辑上的无穷大）会决定到底是淘汰它还是淘汰 `nums2` 的部分。
//
//3. * *奇偶数统一处理 * *：
//`left = (total + 1) / 2` 和 `right = (total + 2) / 2` 这个写法非常经典。
//
//* 总数 3 (奇) : left = 2, right = 2。计算两次第2小，取平均（还是第2小）。
//* 总数 4 (偶) : left = 2, right = 3。计算第2小和第3小，取平均。
//
//### 下一步建议
//
//这道题用递归写是最符合直觉的。你可以把这段代码复制进去，试着手动模拟一下 `nums1=[1, 2]`, `nums2=[3, 4]` 的情况（total = 4, k分别找2和3），看看 `getKth` 是如何一步步切掉 `nums1` 或 `nums2` 的部分的。
//
//```
//```