
//out 空了，才能倒数据
//如果要倒数据  in必须清空倒完
//满足上述条件 其实就是控制  queue的出顺序不乱

class MyQueue {
private:
    int* in;
    int inSize;
    int* out;
    int outSize;
    static const int N = 105;
public:
    MyQueue():inSize(0),outSize(0) {
        in = new int[N];
        out = new int[N];
    }

    //倒数据
    // 从in栈把数据倒入out栈
    // 1）out空了，才能倒数据
    // 2）如果倒数据，in栈必须倒空 
    void inToOut() {
        if (outSize == 0) {
            while (inSize != 0) {
                //全部导入 out栈
                out[outSize++] = in[--inSize];//前缀--
            }
        }
    }

    void push(int x) {
        in[inSize++] = x;
        inToOut();
    }

    int pop() {
        inToOut();
        return out[--outSize];
    }

    int peek() {
        inToOut();
        return out[outSize - 1];
    }

    bool empty() {
        inToOut();
        return outSize == 0&&inSize==0;
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */