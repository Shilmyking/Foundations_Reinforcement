
#include<iostream>
using namespace std;
const int INF = 0x3f3f3f3f;

//const int N = 1e5 + 4;
//int Stack[N];
//int Size = 0;//始终指向需要加入元素的位置
//
//void build() {
//	Size = 0;
//}
//
//bool isEmpty() {
//	return Size == 0;
//}
//
//void push(int val) {
//	Stack[Size++] = val;
//}
//
//void pop() {
//	Size--;
//}
//
//int top() {
//	return Stack[Size-1];
//}
//
//int size() {
//	return Size;
//}


//class Stack {
//private:
//	int size;//最大容量
//	int* stack;
//	int top;//指向栈顶下一元素
//public:
//	Stack(int s = 0) :size(0), top(0), stack(nullptr) {
//		stack = new int[s]();
//	}
//	
//	void push(int val) {
//		if (top < size) {
//			stack[top++] = val;
//		}
//	}
//
//	void pop() {
//		if (top == 0) {
//			throw "error";
//		}
//		top--;
//	}
//
//	int top() {
//		if (top == 0) {
//			return INF;
//		}
//		return stack[top-1];
//	}
//
//	bool empty()const {
//		return top == 0;
//	}
//	int Size() {
//		return size;
//	}
//};

class ArrayStack {
private:
    int* data;      // 数组指针
    int capacity;   // 最大容量 (对应你原来的 size)
    int topIndex;   // 当前栈顶索引/元素个数 (对应你原来的 top)

    void copyFrom(const ArrayStack& other) {
        capacity = other.capacity;
        topIndex = other.topIndex;
        // 分配新内存
        data = new int[capacity];
        // 复制数据 (比循环更快的内存拷贝)
        std::copy(other.data, other.data + capacity, data);
    }

public:
    // 构造函数
    explicit ArrayStack(int cap = 100) : capacity(cap), topIndex(0), data(nullptr) {
        if (cap <= 0) {
            throw std::invalid_argument("Capacity must be positive");
        }
        data = new int[capacity](); // 初始化为0
    }

    // 1. 析构函数：释放数组内存
    ~ArrayStack() {
        if (data != nullptr) {
            delete[] data;
            data = nullptr;
        }
    }

    // 2. 拷贝构造：深拷贝
    ArrayStack(const ArrayStack& other) {
        copyFrom(other);
    }

    // 3. 赋值重载：深拷贝
    ArrayStack& operator=(const ArrayStack& other) {
        if (this != &other) {
            // 释放旧资源
            delete[] data;
            // 拷贝新资源
            copyFrom(other);
        }
        return *this;
    }

    void push(int val) {
        if (topIndex >= capacity) {
            // 严谨的做法是扩容或者抛出异常，这里选择简单的抛异常
            throw std::overflow_error("Stack Overflow");
        }
        data[topIndex++] = val;
    }

    void pop() {
        if (empty()) {
            return; // 或者抛出异常
        }
        topIndex--;
    }

    // const 成员函数
    int top() const {
        if (empty()) {
            return INF; // 或者 throw std::underflow_error("Stack is empty");
        }
        return data[topIndex - 1];
    }

    bool empty() const {
        return topIndex == 0;
    }

    // 返回当前元素个数
    int size() const {
        return topIndex;
    }

    // 新增：返回最大容量
    int max_capacity() const {
        return capacity;
    }
};

//int main() {
//    try {
//        ArrayStack s(5);
//        s.push(10);
//        s.push(20);
//
//        cout << "Top: " << s.top() << endl; // 20
//        cout << "Size: " << s.size() << endl; // 2
//
//        ArrayStack s2 = s; // 测试拷贝构造
//        s.pop();
//
//        cout << "s2 Top (should be 20): " << s2.top() << endl; // 验证深拷贝
//    }
//    catch (const exception& e) {
//        cerr << e.what() << endl;
//    }
//    return 0;
//}