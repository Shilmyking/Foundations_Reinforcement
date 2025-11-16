

//https://leetcode.cn/problems/next-greater-element-ii/

#include<vector>
#include<string>
#include<cstring>
#include<algorithm>
#include<unordered_map>
#include<stack>

using namespace std;


/*
给定一个循环数组 nums （ nums[nums.length - 1] 的下一个元素是 nums[0] ），
返回 nums 中每个元素的 下一个更大元素 。

数字 x 的 下一个更大的元素 是按数组遍历顺序，这个数字之后的第一个比它更大的数，
这意味着你应该循环地搜索它的下一个更大的数。如果不存在，则输出 -1 。

*/
class Solution {
public:
    static const int N = 2e4 + 2;
    int Stack[N];
    int Size = 0;

    vector<int> nextGreaterElements(vector<int>& nums) {
        // 从前往后遍历 还是从后往前其实都没关系  

        int n = nums.size();
        vector<int>ans(n,-1);//最开始认为都没有下一个

        for (int i = 0; i < 2*n-1; i++) {
            // 大 ----> 小
            while (Size > 0 && nums[Stack[(Size - 1)%n]] < nums[i%n]) {
               //记录答案
                int top = Stack[(--Size)%n];//下标
                ans[top] = nums[i % n];
            }
            Stack[Size++] = i%n;
        }
        //最后还存在 但是不用清算了
        //因为 初始化就是-1
        return ans;
    }

};