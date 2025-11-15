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
#include<stack>
#include <limits>   // 用于 std::numeric_limits
#include <random>   // 用于 C++ 现代的随机数生成
#include <ctime>    // 用于 C-style 的 time() (如果使用 srand)


#if 0
using namespace std;
// 用递归函数排序栈
// 栈只提供push、pop、isEmpty三个方法
// 请完成无序栈的排序，要求排完序之后，从栈顶到栈底从小到大
// 只能使用栈提供的push、pop、isEmpty三个方法、以及递归函数
// 除此之外不能使用任何的容器，数组也不行
// 就是排序过程中只能用：
// 1) 栈提供的push、pop、isEmpty三个方法
// 2) 递归函数，并且返回值最多为单个整数

//当前栈的最大深度
int Deep(stack<int>&Stack) {
	//也就是实现到达最底层
	if (Stack.empty()) {
		return 0;
	}
	//拿到当前栈顶
	int top = Stack.top();
	Stack.pop();

	//寻找底下到底还有多少
	int deep = Deep(Stack) + 1;
	//底下已经处理好了  自己这里把当前栈顶放回去
	Stack.push(top);
	return deep;
}


//当前深度下最大值是谁
int maxNumQuery(stack<int>&Stack,int MaxDepth,int depth) {
	if (depth == MaxDepth) {
		return -0x3f3f3f3f;
	}

	//还能往下查询是否存在更多的数值
	int top = Stack.top();
	Stack.pop();

	//底下的最大值
	int underMax = maxNumQuery(Stack, MaxDepth, depth + 1);
	int max = std::max(underMax, top);

	Stack.push(top);//不管如何  当前的栈结构不要破坏

	return max;
}

//当前深度下 这个最大值存在多少个
int maxNumCount(stack<int>& Stack, int maxNum, int MaxDepth, int depth) {
	if (depth == MaxDepth) {
		return 0;//不存在了
	}
	int top = Stack.top();
	Stack.pop();

	//底下还存在多少个 
	int underNum = maxNumCount(Stack, maxNum, MaxDepth, depth + 1);
	Stack.push(top);
	return underNum + (top == maxNum ? 1 : 0);
}

//将最大的这几个数字下沉 
void Down(stack<int>& Stack, int maxNum, int MaxDepth, int maxNumCount,int depth) {
	if (depth == MaxDepth) {
		for (int i = 0; i < maxNumCount; i++) {
			Stack.push(maxNum);
		}
		return;
	}
	int top = Stack.top();
	Stack.pop();
	Down(Stack, maxNum, MaxDepth, maxNumCount, depth + 1);
	//如果不是最大的那个数字  维持原本的数值
	if (top != maxNum) {
		Stack.push(top);
	}
	return;
}

void sortStack(stack<int>& Stack) {
	//int Size = Stack.size();  不能调用size函数
	int Size = Deep(Stack);
	while (Size > 0) {
		int maxNum = maxNumQuery(Stack, Size, 0);
		int maxNumCNT = maxNumCount(Stack, maxNum, Size, 0);
		Down(Stack, maxNum, Size, maxNumCNT, 0);
		Size -= maxNumCNT;
	}
}


/**
 * @brief 生成一个包含 n 个随机整数的栈
 * * @param n 栈中元素的数量
 * @param v 随机数的最大值 (生成的数在 [0, v-1] 范围内)
 * @return 包含随机整数的栈
 */
stack<int> randomStack(int n, int v) {
    // C++ 推荐使用 <random> 库来生成高质量的伪随机数
    // 我们使用 static 确保随机数引擎和种子只被初始化一次
    static random_device rd;        // 硬件随机数生成器 (用于获取种子)
    static mt19937 gen(rd());       // Mersenne Twister 19937 引擎

    // Java的 (int)(Math.random() * v) 产生 [0, v-1] 范围内的整数
    uniform_int_distribution<> dis(0, v - 1);

    stack<int> ans;
    for (int i = 0; i < n; i++) {
        // Java 的 stack.add() 对应 C++ 的 stack.push()
        ans.push(dis(gen));
    }
    return ans;
}

/**
 * @brief 检测栈是不是从顶到底依次有序 (从小到大)
 * * @param stack 要检测的栈
 * @return 如果有序则返回 true，否则返回 false
 *
 * @note
 * Java 的参数传递是“值传递” (对于对象，是引用的值的拷贝)。
 * 这意味着在 Java 的 isSorted 方法中调用 .pop() 会修改 *原始* 栈。
 * * 为了在 C++ 中实现 *完全相同* 的行为 (即函数会清空传入的栈)，
 * 我们必须使用“引用传递” (stack<int>& stack)。
 * * 如果您不希望原始栈被修改，可以去掉 & (stack<int> stack)，
 * C++ 会自动按值传递 (拷贝一份栈)，但这与 Java 的行为不同。
 */
bool isSorted(stack<int>& stack) {
    // Java 的 Integer.MIN_VALUE 对应 C++ 的 numeric_limits<int>::min()
    int step = numeric_limits<int>::min();

    // Java 的 stack.isEmpty() 对应 C++ 的 stack.empty()
    while (!stack.empty()) {

        // Java 的 stack.peek() 对应 C++ 的 stack.top()
        if (step > stack.top()) {
            return false;
        }

        // C++ 的 stack.pop() 是 void 返回值，它只移除元素
        // 必须先用 .top() 获取值，再用 .pop() 移除
        step = stack.top();
        stack.pop();
    }
    return true;
}

/**
 * @brief C++ 的主函数
 */
int main() {
    // 为了测试
    stack<int> test;
    // Java 的 .add() 对应 C++ 的 .push()
    test.push(1);
    test.push(5);
    test.push(4);
    test.push(5);
    test.push(3);
    test.push(2);
    test.push(3);
    test.push(1);
    test.push(4);
    test.push(2);

    // 调用排序 (假设 sort 已实现)
    sortStack(test);

    // Java 的 System.out.println() 对应 C++ 的 cout << ... << endl
    while (!test.empty()) {
        cout << test.top() << endl;
        test.pop();
    }

    // --- 随机测试 ---

    int N = 20;
    int V = 20;
    int testTimes = 20000;

    // 为 main 函数中的 n 生成随机数 (同 randomStack 中的方法)
    static random_device rd;
    static mt19937 gen(rd());
    // Java的 (int)(Math.random() * N) 产生 [0, N-1] 范围内的整数
    uniform_int_distribution<> disN(0, N - 1);

    cout << "测试开始" << endl;
    for (int i = 0; i < testTimes; i++) {
        int n = disN(gen);
        stack<int> stack = randomStack(n, V);

        sortStack(stack); // 排序

        if (!isSorted(stack)) { // 检测 (并清空)
            cout << "出错了!" << endl;
            break;
        }
    }
    cout << "测试结束" << endl;

    return 0; // C++ main 函数的标准返回
}


#endif