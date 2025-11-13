
/*
设计实现双端队列。

实现 MyCircularDeque 类:

MyCircularDeque(int k) ：构造函数,双端队列最大为 k 。
boolean insertFront()：将一个元素添加到双端队列头部。 如果操作成功返回 true ，否则返回 false 。
boolean insertLast() ：将一个元素添加到双端队列尾部。如果操作成功返回 true ，否则返回 false 。
boolean deleteFront() ：从双端队列头部删除一个元素。 如果操作成功返回 true ，否则返回 false 。
boolean deleteLast() ：从双端队列尾部删除一个元素。如果操作成功返回 true ，否则返回 false 。

int getFront() )：从双端队列头部获得一个元素。如果双端队列为空，返回 -1 。
int getRear() ：获得双端队列的最后一个元素。 如果双端队列为空，返回 -1 。
boolean isEmpty() ：若双端队列为空，则返回 true ，否则返回 false  。
boolean isFull() ：若双端队列满了，则返回 true ，否则返回 false 。

*/
#include<string>
#include<iostream>
using namespace std;

//循环双端队列
class MyCircularDeque {
private:
    int Limit;
    static const int MAXN = 1002;
    int queue[MAXN];
    //Right 指向下一个要加入数字的位置
    int Left, Right;
    int Size;
public:
    MyCircularDeque(int k):Limit(k),Left(0),Right(0),Size(0) {
        memset(queue, 0, sizeof(queue));
    }

    bool insertFront(int value) {
        //头部添加元素 ？？ 岂不是 非常麻烦  得用链表
        if (isFull()){
            return false;
        }

        Size++;
        return true;
    }

    bool insertLast(int value) {
        if (isFull()) {
            return false;
        }
        queue[Right] = value;
        Right = Right == Limit - 1 ? 0 : Right + 1;
        Size++;
        return true;
    }

    //从头删除
    bool deleteFront() {
        if (isEmpty()){
            return false;
        }
        Left = Left == Limit - 1 ? 0 : Left + 1;
        Size--;
        return true;
    }


    bool deleteLast() {
        if (isEmpty()) {
            return false;
        }
        int last = Right == 0 ? Limit - 1 : Right - 1;//上一个数字
        Right = last;
        Size--;
        return true;
    }

    int getFront() {
        if (isEmpty()) {
            return -1;
        }
        return queue[Left];
    }

    int getRear() {
        if (isEmpty()) {
            return -1;
        }
        int last = Right == 0 ? Limit - 1 : Right - 1;
        return queue[last];
    }

    bool isEmpty() {
        return Size == 0;
    }

    bool isFull() {
        ////Left 就是Right的下一个位置
        //return Left == (Right == Limit ? 0:Right + 1);
        return Size == Limit;
    }
};

/**
 * Your MyCircularDeque object will be instantiated and called as such:
 * MyCircularDeque* obj = new MyCircularDeque(k);
 * bool param_1 = obj->insertFront(value);
 * bool param_2 = obj->insertLast(value);
 * bool param_3 = obj->deleteFront();
 * bool param_4 = obj->deleteLast();
 * int param_5 = obj->getFront();
 * int param_6 = obj->getRear();
 * bool param_7 = obj->isEmpty();
 * bool param_8 = obj->isFull();
 */

//这个 版本实现的是 Tail指向的一直是最后一个位置

class MyCircularDeque {
    private final int[] elements;
    private int size = 0, head = 0, tail;
    public MyCircularDeque(int k) {
        elements = new int[k];
        tail = k - 1;
    }
    public boolean insertFront(int value) {
        if (isFull()) return false;
        elements[head] = value;// 头指针左移
        head = head == 0 ? elements.length - 1 : head - 1
        size++;
        return true;
    }
    public boolean insertLast(int value) {
        if (isFull()) return false;
        elements[tail] = value;// 尾指针右移
        tail = tail == elements.length - 1 ? 0 : tail + 1
        size++;
        return true;
    }
    public boolean deleteFront() {
        if (isEmpty()) return false;
        head = head == elements.length - 1 ? 0 : head + 1;// 头指针右移
        size--;
        return true;
    }
    public boolean deleteLast() {
        if (isEmpty()) return false;
        tail = tail == 0 ? elements.length - 1 : tail - 1;// 尾指针左移
        size--;
        return true;
    }
    public int getFront() {
        if (isEmpty()) return -1;
        return elements[head];
    }
    public int getRear() {
        if (isEmpty()) return -1;
        return elements[tail];
    }
    public boolean isEmpty() {
        return size == 0;
    }
    public boolean isFull() {
        return size == elements.length;
    }
}