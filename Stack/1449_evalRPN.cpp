#include<string>
#include<iostream>

#if 0
using namespace std;
#define int long long
#define endl "\n"

const int N = 105;
int nums[N];
int Size;
int now;
// 后缀表达式的话 只使用一个栈就行  一个nums  
//当遇到运算符 就弹出两个数字   运算完 再放栈内

//3*(5-2)+7 对应的后缀表达式为：3.5.2.-*7.+@。在该式中，@ 为表达式的结束符号。. 为操作数的结束符号
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	Size = 0;
	char op;
	int left, right;
	while ((op = getchar()) != '@') {
		if (op >= '0' && op <= '9')
		{
			now = 10 * now + (op - '0');
		}
		else if (op == '.') {
			//数字读取完
			nums[Size++] = now;
			now = 0;
		}

		//就这四个  不用偷懒
		if (op == '+'||op=='-'||op=='*'||op=='/') {
			//操作数 注意 是先弹出right  后弹出left
			right = nums[--Size];
			left = nums[--Size];
			int ans;
			if (op == '+') {
				ans = left + right;
			}
			else if (op == '-') {
				ans = left - right;
			}
			else if (op == '*') {
				ans = left * right;
			}
			else {
				ans = left / right;
			}
			nums[Size++] = ans;
		}
	}
	cout << nums[0] << endl;
	
}
#endif