
// 测试链接 : https://leetcode.cn/problems/basic-calculator-iii/
// 测试链接 : https://www.nowcoder.com/practice/c215ba61c8b1443b996351df929dc4d4


#include<vector>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;

class Solution {
public:
    // "(2*(3-4))*5"  -->10
	static const int N = 1e2 + 2;
	int Where = 0;//标识当前递归函数处理到了哪个位置
	
	// 递归函数
	// 计算当前 ()内的所有值  or 完全没有遇到()  计算完了
	// 计算完递归函数返回前 更新Where数组 标识当前计算式运算到什么地方
	// 从i位置开始往后计算
	int f(const string&s,int i) {
		//每一个递归函数使用自己的 nums ops
		//这里用 vector 用静态数组  否则还要传入 n大小 参数多一位  挺烦
		int now = 0, n = s.size();
		vector<int> nums;
		vector<char> ops;
		
		while (i < n && s[i] != ')') {
			if (s[i] == ' ') {
				i++;
				continue;
			}
			// 计算now
			if (s[i] >= '0' && s[i] <= '9') {
				now = now * 10 + (s[i++] - '0');
			}
			//如果 不是（ or ）  是 + - * / 运算符
			else if (s[i] != '(') {
				push(nums, ops, now, s[i++]);
				now = 0;
			}
			else {
				now = f(s, i + 1);//遇到左括号 -->调用递归 计算出里面的值
				i = Where + 1;//接续递归计算下一位
			}
		}

		push(nums, ops, now, '+');
		Where = i;
		return compute(nums, ops);
	}

	void push(vector<int>& nums, vector<char>& ops, int now, char op) {
		int n = nums.size();
		//栈顶为空直接入栈  如果符号栈栈顶是* or / 需要计算完才能
		if (n == 0 || ops[n - 1] == '+' || ops[n - 1] == '-') {
			nums.emplace_back(now);
			ops.emplace_back(op);
		}
		else {
			int topNum = nums[n - 1];
			char topOp = ops[n - 1];
			// 计算 * or / 然后push
			nums[n - 1] = topOp == '*' ? topNum * now : topNum / now;
			ops[n - 1] = op;
		}
	}
	//只会传入 + or -  如果遇到 * or / 那你在直接弹出
	int compute(vector<int>&nums,vector<char>&ops) {
		int n = nums.size();
		int ans = nums[0];
		for (int i = 1; i < n; i++) {
			ans += ops[i - 1] == '+' ? nums[i] : -nums[i];
		}
		return ans;
	}

    int solve(string s) {
		Where = 0;
		return f(s, 0);
    }
};

