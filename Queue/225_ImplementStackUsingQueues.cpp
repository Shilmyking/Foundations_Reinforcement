
//头部弹出 尾部进入
//记录加入元素前 存在多少个元素 ---->执行多少次 头部弹出尾部进入

//每次进来 都需要倒一次
// O(N)时间复杂度 push  
#include<string>
#include<iostream>
using namespace std;
class MyStack {
    
    static const int N = 1e4;
    int queue[N];
    int Size;
    int Left, Right;
public:
    MyStack():Size(0),Right(0),Left(0) {
        memset(queue, 0, sizeof(queue));
    }

    void push(int x) {
        for (int i = 0; i < Size; i++) {
            queue[Right++] = queue[Left++];
        }
    }

    int pop() {
        return queue[Left++];
    }

    int top() {
        return queue[Left];
    }

    bool empty() {
        return Left == Right;
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */
