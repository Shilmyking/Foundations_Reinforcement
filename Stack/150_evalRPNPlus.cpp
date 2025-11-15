
#include<string>
#include<vector>
#include<iostream>
#include<algorithm>
#include<unordered_map>
#include<stack>
#include<stdexcept> // 引入异常
#include<ctime>     // 引入 time

using namespace std;
#if 0
#define int long long
#define endl "\n"

const int N = 1e6+5;

int nums[N];
int Size = 0;
char ops[N];
int opSize = 0;

string s;
int n;
unordered_map<char, int>Map = {
    // 遇到 ( 你随便入栈   你绝对会遇到和你配对的 )
    // 遇到 ) 你一定得给我计算 直到遇到 (
    {')',1},{'+',2},{'-',2},{'*',3},{'/',3},{'(',4}
};

//根据运算符 计算答案
int cal(int left, int right, char op) {
    if (op == '+' || op == '-') {
        return op == '+' ? left + right : left - right;
    }
    if (op == '*' || op == '/') {
        if (right == 0) {
            // 抛出标准异常，这样 main 中的 catch 才能捕获
            throw std::runtime_error("right==0\n");
            return -1;
        }
        return op == '*' ? left * right : left / right;
    }
    throw "invaild op\n";
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
    if (Size > 0) {
        Left = nums[--Size];
    }
    nums[Size++] = cal(Left, Right, op);
}

int evalRPN() {
    Size = 0;
    opSize = 0;

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
        }
        //遇到 运算符 or (  )
        // 如果当前运算符的优先级 小于 栈顶的优先级 那可以入栈  否则必须计算
        else if (Map.count(s[i])) {//包含这个
            // 栈顶不为(   栈顶的优先级高就得一直计算
            while (opSize > 0 && ops[opSize - 1] != '(' && Map[ops[opSize - 1]] >= Map[s[i]]) {
                compute();
            }
            // 当前字符就是）  说明下一个就是(   因为）优先级足够低，已经把全部 +-*/都算完了 除非遇到（
            if (s[i] == ')') {
                opSize--;
            }
            else {
                ops[opSize++] = s[i];//把 比自己优先级高的 和相等的都计算完了
            }
        }
    }
    // 遍历完了  可能还存在没有计算的
    while (opSize > 0) {
        compute();
    }
    return Size != 0 ? nums[0] : 0;
}
//逆波兰表达式

#endif