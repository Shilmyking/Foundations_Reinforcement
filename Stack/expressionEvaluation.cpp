
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

int evalRPN() {
    Size = 0;
    opSize = 0;

    // 上一个非空字符是 数字 or ） --- true
    // 上一个非空字符为操作符 （ 就是false
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
            // '-' 是 表达式的第一个非空字符（-5）
            // 前一个字符是 (  （-（-5））
            // 一元负号需要额外标识   -5    10 -（-5）
            if (s[i] == '-' && lastOp == false) {
                op = '_';//cal 部分补0计算
            }

            // 栈顶不为(   栈顶的优先级高就得一直计算
            while (opSize > 0 && ops[opSize - 1] != '(' && Map[ops[opSize - 1]] >= Map[op]) {
                compute();
            }
            // 当前字符就是）  说明下一个就是(   因为）优先级足够低，已经把全部 +-*/都算完了 除非遇到（
            if (op == ')') {
                opSize--;// （ 
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

#if 0
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
#endif