
#include<string>
using namespace std;

class Solution {
    static const int N = 3e4 + 2;
    int dp[N];
public:
    //动态规划 ？   每个位置为结尾 你去计算最长有效括号
    int longestValidParentheses(string s) {

        int n = s.size();
        if (n == 0 || n == 1) { return 0; }
        dp[0] = 0;//0位置一定为0
        dp[1] = s[0] == '(' && s[1] == ')' ? 2 : 0;
        int Max = dp[1];
        for (int i = 2; i < n; i++) {
            dp[i] = 0;
            //默认 ( 就是0
            if (s[i] == ')') {
                int pre = i - 1 - dp[i - 1];
                //右括号  就是需要看左侧了
                // 不仅仅是  2+ dp[i-2]  因为可能连了一堆
                // 需要看 dp[i-1 -dp[i-1]] 的位置  因为  存在 ()(())这样嵌套的情况
                if (pre >= 0 && s[pre] == '(') {
                    // 可能 pre 前面完全没有字符了
                    // 如果你还有字符 就有配对上的可能性
                    dp[i] = 2 + dp[i - 1] + (pre > 0 ? dp[pre - 1] : 0);
                }
                Max = std::max(dp[i], Max);
            }
        }
        return Max;
    }
};

