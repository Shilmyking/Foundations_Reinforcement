
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

    //递归
    int solve(string s) {
    
    }
};


//#if 0
//public class Code01_BasicCalculatorIII {
//
//	public static int calculate(String str) {
//		Where = 0;
//		return f(str.toCharArray(), 0);
//	}
//
//	//记录当前处理到的地方
//	public static int Where;
//
//	//每个递归函数如果存在自己的"("的话 一定会遇到自己的")"
//
//	// s[i....]开始计算，遇到字符串终止 或者 遇到)停止
//	// 返回 : 自己负责的这一段，计算的结果
//	// 返回之间，更新全局变量Where，为了上游函数知道从哪继续！
//	public static int f(char[] s, int i) {
//		int cur = 0;
//		ArrayList<Integer> numbers = new ArrayList<>();//数字栈
//		ArrayList<Character> ops = new ArrayList<>();//符号栈
//		//只要没有遇到右括号和到达末尾
//		while (i < s.length && s[i] != ')') {
//
//			if (s[i] >= '0' && s[i] <= '9') {
//				cur = cur * 10 + s[i++] - '0';//如果是数字 继续增加
//			}
//			else if (s[i] != '(') {
//				// 遇到了运算符 + - * /
//				push(numbers, ops, cur, s[i++]);
//				cur = 0;//刷新 置零
//
//			}
//			else {
//				// i (.....)
//				// 遇到了左括号！
//				cur = f(s, i + 1);
//
//				//子过程做完之后 同步更新了Where  我们这里接着子过程继续操作
//				i = Where + 1;
//			}
//		}
//		//1 + 1
//		//最后遇到终止符or遇到)   需要把那个数字放进去   
//		//这里面使用的 数组存储这些内容
//		push(numbers, ops, cur, '+');
//		Where = i;
//		return compute(numbers, ops);
//	}
//
//	//遇到符号  那就需要压栈了
//	public static void push(ArrayList<Integer> numbers, ArrayList<Character> ops, int cur, char op) {
//		int n = numbers.size();
//		if (n == 0 || ops.get(n - 1) == '+' || ops.get(n - 1) == '-') {
//			//数字栈啥也没有  符号栈栈顶不为 "*" or "/"
//			numbers.add(cur);
//			ops.add(op);
//		}
//		else {//乘或除 计算完放栈内
//			//拿出符号栈和数字栈的栈顶
//			int topNumber = numbers.get(n - 1);
//			char topOp = ops.get(n - 1);
//			//更新数字栈栈顶元素
//			if (topOp == '*') {
//				numbers.set(n - 1, topNumber * cur);
//			}
//			else {
//				numbers.set(n - 1, topNumber / cur);
//			}
//			//op为符号栈栈顶？？
//			ops.set(n - 1, op);
//		}
//	}
//
//	public static int compute(ArrayList<Integer> numbers, ArrayList<Character> ops) {
//		int n = numbers.size();
//		int ans = numbers.get(0);
//		for (int i = 1; i < n; i++) {
//			//只会遇到 +  和  -
//			ans += ops.get(i - 1) == '+' ? numbers.get(i) : -numbers.get(i);
//		}
//		return ans;
//	}
//
//}
//
//#endif