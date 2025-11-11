#include<vector>
#include<string>
using namespace std;


class Solution {
//using ll = long long;
    static const int N = 1e4 + 5;
    int nums[N];
    int Size;
public:
    int evalRPN(vector<string>& tokens) {
        Size = 0;
        int Left, Right;
        for (auto& v : tokens) {
            if (v == "+") {
                Right = nums[--Size];
                Left = nums[--Size];
                nums[Size++] = Left + Right;
            }
            else if (v == "-") {
                Right = nums[--Size];
                Left = nums[--Size];
                nums[Size++] = Left - Right;
            }
            else if (v == "*") {
                Right = nums[--Size];
                Left = nums[--Size];
                nums[Size++] = Left * Right;
            }
            else if (v == "/") {
                Right = nums[--Size];
                Left = nums[--Size];
                nums[Size++] = Left / Right;
            }
            else {//数字
                nums[Size++] = atoi(v.c_str());
            }
        }
        return nums[0];
    }
};