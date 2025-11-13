

// 柱状图中最大的矩形
// 给定 n 个非负整数，用来表示柱状图中各个柱子的高度
// 每个柱子彼此相邻，且宽度为 1 。求在该柱状图中，能够勾勒出来的矩形的最大面积
// 测试链接：https://leetcode.cn/problems/largest-rectangle-in-histogram

#include<iostream>
#include<string>
#include<vector>

using namespace std;
#if 0
class Solution {
    static const int N = 1e5 + 5;
    int Stack[N];
    int Size = 0;
    int Max = 0;
public:
    // 需要枚举每个位置的情况
    //每个位置找到比当前位置 小的左侧位置  和小的右侧位置
    // i-left-1  *  height[i]就是矩形高度
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        for (int i = 0; i < n; i++) {
            // 大于等于的都 进行结算  这也相等的数字岂不是找不到正确的右边界
            // 没关系 因为当前进入的这个相等的数字其实会接管这些pop出去的数字的左边界
            // 右边界也会正确的找到 所以无伤大雅  最后还是能找到最大的矩阵

            // 栈顶元素 大于等于 新进入的元素 这个时候结算  pop栈顶    保证的是大压小
            // 这样就能保证  如果当前栈顶 和 下面的数字 存在i上的间隔没关系  因为间隔内的数字一定更大才结算了
            // 也就是范围为  i - left -1
            while (Size > 0 && heights[Stack[Size - 1]] >= heights[i]) {
                int top = Stack[--Size];
                // left 是 top 柱子左边第一个更矮的柱子索引
                int left = Size > 0 ? Stack[Size - 1] : -1;
                // 右边界是 i (当前导致 top 弹出的索引)
                // 左边界是 left
                //注意宽度 是 (i-left-1)  因为当前位置结算 
                // 可能top位置 距离 left 和 i都有大段距离  但是都是有heights[i]高
                Max = std::max(Max, (heights[top] * (i - left - 1)));
            }
            Stack[Size++] = i;
        }

        //清算剩余未计算的
        while (Size > 0) {
            int top = Stack[--Size];
            int left = Size > 0 ? Stack[Size - 1] : -1;
            // 这里就是 (n-left-1)
            Max = std::max(Max, heights[top] * (n - left - 1));
        }
        return Max;
    }
};

#endif