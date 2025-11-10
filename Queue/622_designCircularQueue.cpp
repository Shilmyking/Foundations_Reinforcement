
//循环队列的一个好处是我们可以利用这个队列之前用过的空间。
//在一个普通队列里，一旦一个队列满了，我们就不能插入下一个元素，即使在队列前面仍有空间。
//但是使用循环队列，我们能使用这些空间去存储新的值。

//MyCircularQueue(k) : 构造器，设置队列长度为 k 。
//Front : 从队首获取元素。如果队列为空，返回 - 1 。
//Rear : 获取队尾元素。如果队列为空，返回 - 1 。
//enQueue(value) : 向循环队列插入一个元素。如果成功插入则返回真。
//deQueue() : 从循环队列中删除一个元素。如果成功删除则返回真。
//isEmpty() : 检查循环队列是否为空。
//isFull() : 检查循环队列是否已满。
class MyCircularQueue {
private:
    int* queue;
    int Left, Right;
    int Size;
    int limit;
public:
    MyCircularQueue(int k) :Left(0), Right(0), Size(0),limit(k) {
        queue = new int[k]();
    }
    ~MyCircularQueue() {
        delete[] queue;
    }
    bool enQueue(int value) {
        if (Size == limit) {
            return false;
        }
        queue[Right] = value;
        Right = Right == limit - 1 ? 0 : Right + 1;
        Size++;
        return true;
    }

    bool deQueue() {
        //对头
        if (Size == 0) {
            return false;
        }
        Left = Left == limit - 1 ? 0 : Left + 1;
        Size--;
        return true;
    }

    int Front() {
        if (Size == 0) {
            return -1;
        }
        return queue[Left];
    }

    int Rear() {
        if (Size == 0) {
            return -1;
        }
        int lastIndex = Right == 0 ? (limit - 1) : Right - 1;
        return queue[lastIndex];
    }

    bool isEmpty() {
        return Size == 0;
        
    }

    bool isFull() {
        return Size == limit;
    }
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */