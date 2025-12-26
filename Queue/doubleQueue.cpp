#include <iostream>
using namespace std;

const int INF = 0x3f3f3f3f;
class DoubleLinkedListQueue {
private:
	struct Node {
		int data;
		Node* next;
		Node* pre;
		Node(int data=0,Node*next=nullptr,Node*pre=nullptr):data(data),next(next),pre(pre){}
	};
	Node* head;
	int size;

public:
	DoubleLinkedListQueue(int size = 0) :size(size), head(new Node()) {
		head->pre = head;
		head->next = head;
	}

	~DoubleLinkedListQueue(){
		while (!empty()) {
			pop();
		}
		delete head;
	}

	// 尾节点插入
	void push(int val) {
		Node* node = new Node(val);
		Node* tail = head->pre;//前驱  --->尾节点
		
		node->pre = tail;
		node->next = head;
		tail->next = node;
		head->pre = node;//head 指向尾节点
		size++;
	}

	// 头节点出
	void pop() {
		if(head->next==head){
			return;//没有节点
		}

		Node* p = head->next;//第一个节点 需要pop的
		head->next = p->next;
		p->next->pre = head;

		delete p;
		size--;
	}

	int front()const {
		if (head->next == head) {
			return INF;//空队列
		}
		return head->next->data;
	}

	int back()const {
		if (head->next == head) {
			return INF;//空队列
		}
		return head->pre->data;
	}

	bool empty()const {
		return head->next == head;
	}
};