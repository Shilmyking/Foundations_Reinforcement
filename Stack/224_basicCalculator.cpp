
#include<string>

using namespace std;

/*
1 <= s.length <= 3 * 105
s 由数字、'+'、'-'、'('、')'、和 ' ' 组成
s 表示一个有效的表达式
'+' 不能用作一元运算(例如， "+1" 和 "+(2 + 3)" 无效)
'-' 可以用作一元运算(即 "-1" 和 "-(2 + 3)" 是有效的)
输入中不存在两个连续的操作符
每个数字和运行的计算将适合于一个有符号的 32位 整数
*/

//"(1+(4+5+2)-3)+(6+8)"


class Solution {
    static const int N = 2e5;
    int Stack[N];
    int Size = 0;
    char ops[N];
    int opSize = 0;
public:
    //一次计算过程  Stack取两个数字  ops一个  计算完放回Stack栈
    void cal() {
        int right = Stack[--Size];
        int left = Stack[--Size];
        Stack[Size++] = ops[--opSize] == '+' ? left + right : left - right;
    }
    int calculate(string s) {
        int n = s.size();
        int now = 0;

        for (int i = 0; i < n; i++) {
            //遇到括号特殊处理
            int op = s[i];
            if (op == ' ') {
                continue;
            }

            //处理遇到一个数字字符  然后解析为整个数字的逻辑
            if (op >= '0' && op <= '9') {
                now = op - '0';
                while (i + 1 < n && s[i + 1] >= '0' && s[i + 1] <= '9') {
                    now = now * 10 + (s[++i] - '0');
                }
                Stack[Size++] = now;//now无需置0  后续初始处理
            }
            else if (op == '+' || op == '-') {
                //1） 需要检查一元负号问题

                int j = i - 1;
                while (j >= 0 && s[j] == ' ') j--;//往前找第一个非''字符
                // 作为开头 or 前一个有效字符为(
                //  1- ( -2 ) 这种情况就必须额外加一个左操作数
                // -2 这样也是
                if (op == '-' && (j < 0 || s[j] == '(')) {
                    Stack[Size++] = 0;
                }
                //2) 需要计算完再去加入新的 op
                // 如果累计到最后 计算 会出现顺序错误 
                // 比如 2-1+2  最后计算出  2-3这样的错误

                //完全计算完 or 遇到 (
                while (opSize > 0 && ops[opSize - 1] != '(') {
                    cal();
                }
                ops[opSize++] = op;
            }

            if (op == '(') {
                //直接加入就行  等到下次 ) 来了计算就行了
                ops[opSize++] = '(';
            }
            if (op == ')') {
                while (ops[opSize - 1] != '(') {
                    cal();
                }
                --opSize;//pop '('
            }
        }
        while (opSize > 0 ) {
            cal();
        }
        return Stack[0];
    }
};

