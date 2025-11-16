

//这题就是和括号四连问题的第二个问题很像
// 你要补多少个括号  几乎一致
#include<string>
using namespace std;

class Solution {
public:
    string minRemoveToMakeValid(string s) {
        int n = s.size();
        int left = 0, right = 0;//左右括号的个数
        for (auto& v : s) {
            if (v == ')') {
                right++;
            }
        }
        string ans = "";
        //遍历完了收集


        // 你知道了 右括号的总数目 
        // 还需要控制当前左括号的个数  不能说 是）就选择   还得有（和你配对

        // left -->当前需要的 ）数 拿来配对 （
        // right表示的是 当前还能选择的
        for (int i = 0; i < n; i++) {
            if (s[i] == '(') {
                if (right > 0) {
                    left++;
                    right--;
                    ans += '(';
                }
            }
            else if (s[i] == ')') {
                // 需要选择你就选
                if (left > 0) {
                    ans += ')';
                    left--;
                }
                // 这个时候不能选择 这个括号 否则ans无效
                // 后续的right减少
                else {
                    right--;
                }
            }
            else {
                ans += s[i];
            }
        }
        return ans;
    }
};