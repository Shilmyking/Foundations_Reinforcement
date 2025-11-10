
#include<string>
using namespace std;

class Solution {
    static const int N = 1e4 + 3;
    char Stack[N];
    int Size = 0;
public:
    bool isValid(string s) {
        for (auto& v:s) {
            //只要是左括号你可以进入
            if (Size == 0||v=='('||v=='['||v=='{') {
                Stack[Size++] = v;
            }
            else {//不为空
                if ((v == ')' && Stack[Size-1] == '(') ||
                    (v == ']' && Stack[Size-1] == '[') ||
                    (v == '}' && Stack[Size-1] == '{')) {
                    Size--;
                }
                else {
                    return false;
                }
            }
        }
        return Size != 0 ? false : true;
    }
};