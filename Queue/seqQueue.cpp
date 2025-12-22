

class SeqQueue {
private:
    int* pQue_;
    int cap_;   // 容量
    int front_; // 队头下标
    int rear_;  // 队尾下标
    int size_;  // 元素个数

    // 扩容函数
    void expand(int size) {
        int* p = new int[size];

        // 重点：不能直接 memcpy
        // 因为是循环队列，数据可能在数组末尾截断并绕回数组开头
        // 需要将数据重新对齐，搬运到新数组的 0 开始的位置
        int i = 0;
        int j = front_;
        for (; j != rear_; i++, j = (j + 1) % cap_) {
            p[i] = pQue_[j];
        }

        delete[] pQue_;
        pQue_ = p;
        cap_ = size;
        front_ = 0; // 重置队头
        rear_ = i;  // 重置队尾
    }

public:
    SeqQueue(int size = 10)
        : cap_(size), front_(0), rear_(0), size_(0) {
        pQue_ = new int[cap_];
    }

    ~SeqQueue() {
        delete[] pQue_;
        pQue_ = nullptr;
    }

    // 入队：队尾插入
    void push(int val) {
        // 判断已满：(rear + 1) % cap == front
        if ((rear_ + 1) % cap_ == front_) {
            expand(2 * cap_);
        }
        pQue_[rear_] = val;
        rear_ = (rear_ + 1) % cap_;
        size_++;
    }

    // 出队：队头删除
    void pop() {
        if (front_ == rear_)
            throw "queue is empty!";
        front_ = (front_ + 1) % cap_;
        size_--;
    }

    // 获取队头元素
    int front() const {
        if (front_ == rear_)
            throw "queue is empty!";
        return pQue_[front_];
    }

    // 获取队尾元素
    int back() const {
        if (front_ == rear_)
            throw "queue is empty!";
        // rear 指向的是下一个空位，所以有效元素是 (rear - 1)
        // 为了防止 rear - 1 变为 -1，需要加 cap_ 再取模
        return pQue_[(rear_ - 1 + cap_) % cap_];
    }

    bool empty() const {
        return front_ == rear_;
    }

    int size() const {
        return size_;
    }
};