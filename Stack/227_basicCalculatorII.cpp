
#include<string>
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


using namespace std;
#if 0
class Solution {
    static const int N = 2e5 + 2;
    int nums[N];
    int Size = 0;
    char ops[N];
    int opSize = 0;
    int now = 0;
public:
    void compute() {
        int right = nums[--Size];
        int left = nums[--Size];
        nums[Size++] = ops[--opSize] == '+' ? left + right : left - right;
    }
    int calculate(string s) {
        int n = s.size();
        for (int i = 0; i < n; i++) {
            char op = s[i];
            if (op == ' ') {
                continue;
            }
            if (op >= '0' && op <= '9') {
                now = (op - '0');
                while (i + 1 < n && s[i + 1] >= '0' && s[i + 1] <= '9') {
                    now = now * 10 + (s[++i] - '0');
                }
                //把 * / 优先计算了
                // 括号里有个优先级问题 就是后面ops判断需要加括号 满足一种即可
                if (opSize > 0 && (ops[opSize - 1] == '*' || ops[opSize - 1] == '/'))
                {
                    int left = nums[--Size];
                    now = ops[--opSize] == '*' ? now * left : left / now;
                }
                nums[Size++] = now;
            }
            else if (op == '*' || op == '/') {
                ops[opSize++] = op;
            }
            else if (op == '+' || op == '-') {
                // +  - 之间运算符优先级一致  需要从左往右计算
                //一样的加入 + or - 需要先计算完之前的才能加入 
                while (opSize > 0) {
                    compute();
                }
                ops[opSize++] = op;
            }
        }
        while (opSize > 0) {
            compute();
        }
        return nums[0];
    }
};
// 甚至只需要一个栈就行了   一个数字栈  遇到 * / 就计算  遇到 




#endif





//
//// 版本一
//class Solution {
//public:
//    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
//        stack<int> st;
//        vector<int> result(nums1.size(), -1);
//        if (nums1.size() == 0) return result;
//
//
//        unordered_map<int, int> umap; // key:下标元素，value：下标
//        for (int i = 0; i < nums1.size(); i++) {
//            umap[nums1[i]] = i;
//        }
//
//        st.push(0);
//        for (int i = 1; i < nums2.size(); i++) {
//            //小压大
//            if (nums2[i] < nums2[st.top()]) {          
//                st.push(i);
//            }
//            else if (nums2[i] == nums2[st.top()]) {  
//                st.push(i);
//            }
//
//            else {                                   
//                while (!st.empty() && nums2[i] > nums2[st.top()]) {
//                    if (umap.count(nums2[st.top()]) > 0) { // 看map里是否存在这个元素
//                        int index = umap[nums2[st.top()]]; // 根据map找到nums2[st.top()] 在 nums1中的下标
//                        result[index] = nums2[i];
//                    }
//                    st.pop();
//                }
//                st.push(i);
//            }
//        }
//        return result;
//    }
//};