#include<iostream>

const int N = 1e5 + 5;
int Queue[N];
int Left, Right;

void build() {
	Left = Right = 0;
}

bool isEmpty() {
	return Left == Right;
}

bool isFull() {
	return (Right + 1) % N == Left;//下一个可以添加数字的位置
}

void push(int val) {
	if (isFull()) {
		return;
	}
	Queue[Right] = val;
	Right = (Right + 1) % N;//指针 循环
}

void pop() {
	if (isEmpty()) {
		return;
	}
	Left = (Left + 1) % N;
}

int head() {
	if (isEmpty()) {
		throw "head:Empty\n";
	}
	return Queue[Left];
}

int back() {
	if (isEmpty()) {
		throw "back:Empty\n";
	}
	// Right指向待插入的位置
	return Queue[(Right - 1 + N) % N];//循环
}

int size() {
	return (Right - Left + N) % N;//同余原理
}

class CircularQueue {
	const int INF = 0x3f3f3f3f;
private:
	struct Node {
		Node* next;
		int data;
		Node(int data = -1, Node* next = nullptr) :data(data), next(next) {}
	};
	Node* front;//始终指向头节点 dummy node
	Node* rear;//尾指针 指向最后一个有效节点 为空则指向头节点
	int size;
public:
	CircularQueue():size(0){
		front = new Node();
		rear = front;
		front->next = front;
	}
	
	~CircularQueue() {
		Node* cur = front->next;
		while (cur != front) {
			Node* tmp = cur;
			cur = cur->next;
			delete tmp;
		}
		delete front;
	}

	// front ---> xxx ---> xxxx -> xxx -> rear（尾节点） ---> front（头结点 无效元素）
	void push(int val) {
		Node* node = new Node(val);
		
		node->next = front;
		rear->next = node;
		rear = node;
		size++;
	}

	void pop() {
		if (empty()) {
			return;
		}
		//
		Node* firstNode = front->next;
		if (rear == firstNode) {//pop
			rear = front;
		}
		// 删除first这个节点
		// 如果正好是要删除的 也是指向了 front
		front->next = firstNode->next;
		delete firstNode;
		size--;
	}

	bool empty() {
		return size == 0;
	}

	int front() {
		if (empty()) {
			return INF;
		}
		return front->next->data;
	}

	int back() {
		if (empty()) {
			return INF;
		}
		return rear->data;
	}
};