
// KMP算法模版
// 测试链接 : https://leetcode.cn/problems/find-the-index-of-the-first-occurrence-in-a-string/

#include<vector>
#include<string>
#include<algorithm>
#include<cstring>

using namespace std;
#if 0
class Solution {
public:
    static const int N = 1e4 + 2;
    int next[N];

    void getNext(const string& s) {
        memset(next, 0, sizeof(next));
        next[0] = -1;
        next[1] = 0;
        int n = s.size();
        if (n <= 1) { return; }
        //cn初始化为什么？？什么时候更新cn??
        //初始化为前一位的next数组的位置
        int i = 2;
        int cn = next[1];//i从2开始  所以就是 cn = next[1] = 0
        while (i < n) {
            //遍历每个位置  我们希望尽可能大得匹配得到next数组
            //当前位置的前一位
            if (s[i - 1] == s[cn]) {
                //如果相等 next[i]等于  cn+1
                // 存在多次往前跳转的情况
                next[i++] = ++cn;
                //cn也到达下一个位置  继续next[i+1]位置的匹配
                //为什么cn+1就是就是下一个匹配的位置  可以理解为 cn = next[i+1 -1](cn+1)
            }
            // 不好意思 没匹配上  继续往前跳转 next  因为还是要利用前缀串匹配的结果 快速求解
            // 还没能匹配上的话 就是继续跳转
            else if (cn > 0) {
                cn = next[cn];
            }
            else {
                //真的无法再匹配了  cn也 == 0了   
                //不可能到-1 因为只能再next[0]取到-1  前面截断了
                next[i++] = 0;//next数组就是0了
            }
        }
    }

    int KMP(const string& s1, const string& s2) {

        getNext(s2);//求出next数组
        //剩下的就是 利用next数组快速匹配
        int n = s1.size(), m = s2.size();
        int i = 0, j = 0;
        //i指针不回退
        while (i < n && j < m) {
            if (s1[i] == s2[j]) {
                i++, j++;
            }
            // s2的第一个字符就没能和 i位置的字符匹配上
            // i++ s1往下去找第一个能配对上的
            else if (j == 0) {
                i++;
            }
            else {
                j = next[j];//跳转
            }
        }
        //第一个开始匹配的位置   or 无法匹配
        return j == m ? i - j : -1;
    }

    int strStr(string haystack, string needle) {
        return KMP(haystack, needle);
    }
};

#endif