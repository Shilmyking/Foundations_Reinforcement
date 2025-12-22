#include <iostream>
using namespace std;

class LinkQueue {
private:
    struct Node {
        int data_; // 修正拼写: date -> data
        Node* next_;
        Node* pre_;
        Node(int data = 0) : data_(data), next_(nullptr), pre_(nullptr) {}
    };

    int size_;
    Node* head_; // 指向头节点 (哨兵节点)

public:
    LinkQueue(int size = 0) : size_(size) {
        head_ = new Node();
        head_->next_ = head_;
        head_->pre_ = head_;
    }

    ~LinkQueue() {
        Node* p = head_->next_;
        while (p != head_) {
            Node* next = p->next_;
            delete p;
            p = next;
        }
        delete head_; // 修正: 单个节点不应使用 delete[]
        head_ = nullptr;
    }

    // 入队：在链表尾部插入
    void push(int val) {
        Node* node = new Node(val);
        Node* p = head_->pre_; // head的前驱就是尾节点

        node->next_ = head_;
        node->pre_ = p;
        p->next_ = node;
        head_->pre_ = node;

        size_++;
    }

    // 出队：删除链表头部元素
    void pop() {
        if (head_->next_ == head_) return; // 空队列保护

        Node* p = head_->next_;
        head_->next_ = p->next_;
        p->next_->pre_ = head_;

        delete p;
        size_--;
    }

    // 获取队头元素
    int front() const {
        if (head_->next_ == head_) // 修正: 原代码是赋值 = ，改为比较 ==
            throw "queue is empty!";
        return head_->next_->data_;
    }

    // 获取队尾元素
    int back() const {
        if (head_->next_ == head_)
            throw "queue is empty!";
        return head_->pre_->data_;
    }

    bool empty() const {
        return head_->next_ == head_;
    }
};