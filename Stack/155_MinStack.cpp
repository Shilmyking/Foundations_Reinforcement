
/*
设计一个支持 push ，pop ，top 操作，并能在常数时间内检索到最小元素的栈。
实现 MinStack 类:

MinStack() 初始化堆栈对象。
void push(int val) 将元素val推入堆栈。
void pop() 删除堆栈顶部的元素。
int top() 获取堆栈顶部的元素。
int getMin() 获取堆栈中的最小元素。
*/
#include<iostream>

#include<string>

#if 0
using namespace std;
class MinStack {
private:
    static const int N = 3e4 + 5;
    int Stack[N];
    int Min[N];
    int stackSize;
    int minSize;
public:
    // O(1)拿到栈内的最小值
    MinStack() :stackSize(0), minSize(0) {
        memset(Stack, 0, sizeof(Stack));
        memset(Min, 0, sizeof(Min));
    }
    ~MinStack() {

    }
    void push(int val) {
        Stack[stackSize++] = val;
        Min[minSize++] = minSize >= 1 && val > Min[minSize - 1] ? Min[minSize - 1] : val;
    }

    void pop() {
        stackSize--;
        minSize--;
    }

    int top() {
        return Stack[stackSize - 1];
    }

    int getMin() {
        return Min[stackSize - 1];
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */

#endif