
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





