


//相等也能进入 
//下一次更大的数值把这些相等的元素一起释放
#include<string>
#include<vector>
#include<iostream>
#include<algorithm>
#include<unordered_map>
#include<stack>

using namespace std;
#if 0
class Solution {
    static const int MAXN = 1e5 + 4;
    int Stack[MAXN];
    int Size = 0;
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int>ans(n);
        for (int i = 0; i < n; i++) {
            //现在需要求解 下一次温度更高的地方在几天之后？？
            //需要小的数字压住大的数字 
            //也就是下面的数字比当前位置的数字更小的时候就需要 结算答案了
            while (Size != 0 && temperatures[i] > temperatures[Stack[Size - 1]]) {
                int top = Stack[--Size];
                ans[top] = i - top;
            }
            Stack[Size++] = i;
        }
        //如果还存在数字没有弹栈  说明这个位置没有比他更大的了
        while (Size > 0) {
            int top = Stack[--Size];
            ans[top] = 0;
        }
        return ans;
    }
};
#endif 