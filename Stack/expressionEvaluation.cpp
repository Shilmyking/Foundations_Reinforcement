
#include<string>
#include<vector>
#include<iostream>
#include<algorithm>
#include<unordered_map>
#include<stack>
#include<stdexcept> 
#include<ctime>     

using namespace std;


#define int long long
#define endl "\n"

//要放到 牛客上测试的话 N调小  静态数组改为 vector
static const int N = 1e5+5;
int nums[N];
int Size = 0;
char ops[N];
int opSize = 0;

string s;
int n;

//也可以自己写一个函数  讨论情况返回即可
unordered_map<char, int>Map = {
    // 遇到 ( 你随便入栈   你绝对会遇到和你配对的 )
    // 遇到 ) 你一定得给我计算 直到遇到 (
    // 需要处理一元负号问题 --->  10 * -5 这样的计算式
    {')',1},{'+',2},{'-',2},{'*',3},{'/',3},{'_',4},{'(',5}
};

//根据运算符 计算答案
int cal(int left, int right, char op) {
    if (op == '+' || op == '-') {
        return op == '+' ? left + right : left - right;
    }
    if (op == '*' || op == '/') {
        return op == '*' ? left * right : left / right;
    }
    return -1;
}

// 弹栈 计算一次
void compute() {
    char op = ops[--opSize];
    int Left = 0;
    int Right = 0;
    //先右 后左  
    // 这里都需要判断 数字栈是否为空  
    // 因为可能存在-(-2   就需要 补0计算了  0-2
    if (Size > 0) {
        Right = nums[--Size];
    }
    //优先处理 一元符号问题
    if (op == '_') {
        nums[Size++] = cal(0, Right, '-');
        return;
    }

    if (Size > 0) {
        Left = nums[--Size];
    }
    nums[Size++] = cal(Left, Right, op);
}

/*

遇到一元负号时，自动在数字栈中补 0

我们只需要在 `evalRPN` 函数中添加一个逻辑，来判断当前遇到的 `-` 究竟是“减号”还是“负号”。

**判断规则：**
一个 `-` 是**负号**（一元运算符），当且仅当：

1.  它是表达式的第一个非空字符（例如 `"-5"`）。
2.  它的前面是一个 `(`（例如 `"10 - (-5)"`）。



在所有其他情况下（例如 `10 - 5` 或 `(5) - 3`），它都是**减号**（二元运算符）。

我们可以通过一个 `bool` 标志位 `lastWasOperand`（上一个标记是操作数）来轻松实现这一点：

* 如果上一个是非空字符是**数字**或 `)`，`lastWasOperand` 设为 `true`。
* 如果上一个是非空字符是**操作符**或 `(`，`lastWasOperand` 设为 `false`。
* 表达式开头时，`lastWasOperand` 默认为 `false`。

当 `s[i] == '-'` 并且 `lastWasOperand == false` 时，它就是一个一元负号，我们向 `nums` 栈中 `push` 一个 `0`。
*/
int evalRPN() {
    Size = 0;
    opSize = 0;

    //上一个非空字符是不是 数字 or )
    // 需要特别判断 "-" 是代表负号 还是减号
    bool lastOp = false;
    for (int i = 0; i < n; i++) {
        while (i<n&&s[i] == ' ') { i++; }
        if (i == n) { break; }

        // 计算数字
        if (s[i] >= '0' && s[i] <= '9') {
            int num = s[i] - '0';
            while (i + 1 < n && s[i+1] >= '0' && s[i+1] <= '9') {
                num = num * 10 + (s[++i ] - '0');
            }
            nums[Size++] = num;
            lastOp = true;
        }

        //遇到 运算符 or (  )
        // 如果当前运算符的优先级 小于 栈顶的优先级 那可以入栈  否则必须计算
        else if (Map.count(s[i])) {//包含这个
            char op = s[i];
            // op代替 s[i]
            
            //上一个不是操作数 所以这个负号在 开头 or （之后
            if (s[i] == '-' && lastOp == false) {
                //nums[Size++] = 0;
                op = '_';
            }

            // 栈顶不为(   栈顶的优先级高就得一直计算
            while (opSize > 0 && ops[opSize - 1] != '(' && Map[ops[opSize - 1]] >= Map[op]) {
                compute();
            }
            // 当前字符就是）  说明下一个就是(   因为）优先级足够低，已经把全部 +-*/都算完了 除非遇到（
            if (op == ')') {
                opSize--;
                lastOp = true;
            }
            else {
                ops[opSize++] = op;//把 比自己优先级高的 和相等的都计算完了
                lastOp = false;
            }
        }

    }
    // 遍历完了  可能还存在没有计算的
    while (opSize > 0) {
        compute();
    }

    return Size != 0 ? nums[0] : 0;
}

vector<string> expressions = {
    "10 - (-5)",
    "-5",
    "(-5)",
    "10 * -5",
    "-(-10)",
    "1 - -1", 
    "10 - 2 * 3",
    "(10 - 2) * 3",
    "(1+(4+5+2)-3)+(6+8)",
    "1 - (5 - 6)",
    "100 / ( 2 * ( 1 - 6 ) )",
    "(2*(3-4))*5",
    "3+2*3*4-1"
    // "10 / 0", // 除零异常
    //"10 / (5 - 5)", // 括号内的除零异常
    //"(10 / 0)"
};


signed main() {

    string s_input;

    // 3. 遍历 vector，对每个表达式进行计算
    for (const string& expr_str : expressions) {
        s = expr_str;
        n = s.length();

        int result = evalRPN();
        cout << "Input:  \"" << s << "\"" << endl;
        cout << "Result: " << result << endl;

    }
    return 0;
}



#if 0

class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 返回表达式的值
     * @param s string字符串 待计算的表达式
     * @return int整型
     */
private:
    // 静态常量 N
    static const int N = 100 + 5;

    // nums: 数字栈
    // 使用 C++11 的列表初始化，确保 vector 被正确初始化大小
    vector<int> nums{ vector<int>(N) };
    // Size: 数字栈的指针（栈顶索引）
    int Size = 0;

    // ops: 操作符栈
    vector<char> ops{ vector<char>(N) };
    // opSize: 操作符栈的指针（栈顶索引）
    int opSize = 0;

    // n: 字符串长度
    int n;

    // 运算符优先级 Map
    // '_' 代表一元负号，优先级设为4，高于乘除
    // ')' 优先级最低，保证它能触发括号内的所有计算
    // '(' 优先级最高，保证它不会被栈内操作符弹出，除非遇到 ')'
    unordered_map<char, int> Map = {
        {')', 1}, {'+', 2}, {'-', 2}, {'*', 3}, {'/', 3}, {'_', 4}, {'(', 5}
    };

    // public 成员（辅助函数）
public:
    /**
     * @brief 执行一次二元或一元运算
     * @param left 左操作数
     * @param right 右操作数
     * @param op 运算符
     * @return 计算结果
     */
    int cal(int left, int right, char op) {
        if (op == '+' || op == '-') {
            return op == '+' ? left + right : left - right;
        }
        if (op == '*' || op == '/') {
            // 注意：题目保证计算结果始终在整型范围内，但未提除零
            // 假设输入合法，不包含除以零
            return op == '*' ? left * right : left / right;
        }
        return -1; // 不应到达此处
    }

    /**
     * @brief 从栈顶弹出一个操作符和一/两个操作数，执行计算，并将结果压回数字栈
     */
    void compute() {
        char op = ops[--opSize]; // 弹出操作符
        int Left = 0;
        int Right = 0;

        // 先弹出的是右操作数
        if (Size > 0) {
            Right = nums[--Size];
        }

        // 优先处理一元负号
        if (op == '_') {
            nums[Size++] = cal(0, Right, '-'); // 相当于 0 - Right
            return;
        }

        // 二元操作符，再弹出左操作数
        if (Size > 0) {
            Left = nums[--Size];
        }

        // 计算结果压回数字栈
        nums[Size++] = cal(Left, Right, op);
    }

    /**
     * @brief 平台要求实现的主方法
     */
    int solve(string s) {
        n = s.size();
        Size = 0;       // 重置数字栈指针
        opSize = 0;     // 重置操作符栈指针

        // 标记上一个非空字符是否为 "操作数"（即 数字 或 ')'）
        // 这对于区分 "减号-" 和 "负号_" 至关重要
        bool lastIsOperand = false;

        for (int i = 0; i < n; i++) {
            // 1. 跳过空格
            while (i < n && s[i] == ' ') {
                i++;
            }
            if (i == n) {
                break;
            }

            // 2. 处理数字
            if (s[i] >= '0' && s[i] <= '9') {
                int num = s[i] - '0';
                while (i + 1 < n && s[i + 1] >= '0' && s[i + 1] <= '9') {
                    num = num * 10 + (s[++i] - '0');
                }
                nums[Size++] = num; // 数字入栈
                lastIsOperand = true; // 标记上一个是操作数
            }
            // 3. 处理操作符
            else if (Map.count(s[i])) {
                char op = s[i];

                // 关键：判断一元负号
                // (1) 当前是 '-'
                // (2) 上一个不是操作数 (即上一个是 '(', 或其他操作符, 或者是表达式开头)
                if (s[i] == '-' && lastIsOperand == false) {
                    op = '_'; // 替换为一元负号
                }

                // 核心调度逻辑：
                // 当栈不为空，栈顶不是'('，且栈顶操作符优先级 >= 当前操作符
                // 则持续计算，直到栈顶优先级低于当前操作符
                while (opSize > 0 && ops[opSize - 1] != '(' &&
                    Map[ops[opSize - 1]] >= Map[op]) {
                    compute();
                }

                // 计算完成后，处理当前操作符
                if (op == ')') {
                    // 遇到 ')'，说明一对括号已计算完毕
                    if (opSize > 0) { // 弹出 '('
                        opSize--;
                    }
                    lastIsOperand = true; // ')' 之后视为一个操作数
                }
                else {
                    // '(', '+', '-', '*', '/', '_' (一元负号) 正常入栈
                    ops[opSize++] = op;
                    lastIsOperand = false; // 标记上一个是操作符
                }
            }
        }

        // 4. 遍历字符串完毕，计算栈中剩余的所有操作
        while (opSize > 0) {
            compute();
        }

        // 5. 最终结果在数字栈底
        return Size > 0 ? nums[0] : 0;
    }
};

#endif
