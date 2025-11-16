

#include<vector>
#include<string>
#include<cstring>
#include<algorithm>
#include<unordered_map>
#include<stack>

using namespace std;

//https://leetcode.cn/problems/next-greater-element-i/

// 意思是 nums1数组内的数字一定会在nums2内出现，
// 现在就是需要找到 那个数字 然后在那个位置往后查找第一个比这个数字大的 值（下标）  如果不存在那就是-1

//所以单调栈处理 nums2数组 然后拿hashTable存储  key(数组的数值) value(下标)

class Solution {
public:
    static const int N = 1e3 + 2;
    int Stack[N];
    int Size = 0;
    unordered_map<int, int> hashMap;
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size();
        vector<int>ans(m);
        int n = nums2.size();
        // 从后往前查找 
        // 栈底到栈顶  大到小  如果大的来了就是结算
        for (int i = n - 1; i >= 0; i--) {
            //不存在相等的元素
            // 从大到小  一直pop到符合条件  
            // 拿栈顶就是你的第一个更大的  如果栈空就是不存在
            while (Size > 0 && nums2[Stack[Size - 1]] < nums2[i]) {
                int top = Stack[--Size];
            }
            //存在就是栈顶 不存在就是-1
            hashMap[nums2[i]] = Size > 0 ? nums2[Stack[Size - 1]] : -1;
            Stack[Size++] = i;
        }
        //栈内还存在元素 --> 都是-1 不存在比自己大的
        // 但是无需继续pop了  因为一开始进入的时候就能确认
        for (int i = 0; i < m; i++) {
            ans[i] = hashMap[nums1[i]];
        }
        return ans;
    }
};
